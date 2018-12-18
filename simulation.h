#include <map>

using std::map;

template <typename Func>
void execute(int64_t loop_count, Func&& step) {
    for (int64_t loop_no = 0; loop_no < loop_count; ++loop_no)
        step();
}

template <typename T, typename Func>
void execute_with_caching(int64_t loop_count, T& state, Func&& step) {
    map<T, int64_t> cache;
    for (int64_t loop_no = 0; loop_no < loop_count; ++loop_no) {
        cache[state] = loop_no;
        step();
        auto it = cache.find(state);
        if (it != end(cache)) {
            int cycle = loop_no - it->second - 1;
            loop_no += ((loop_count - loop_no) / cycle) * cycle;
        }
    }
}
