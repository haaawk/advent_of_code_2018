#include "../commons.h"

using dep = pair<char, char>;

int main() {

    vector<dep> d = read_lines<dep>("Step ([A-Z]) must be finished before step ([A-Z]) can begin.",
                                    CONVERT(m, dep(m[1].str()[0], m[2].str()[0])));

    map<char, int> in;
    for (auto p : d) in[p.second]++;

    set<char> ready_to_start;
    for (auto p : d) {
        if (in[p.first] == 0) {
            ready_to_start.insert(p.first);
        }
    }

    auto finish = [&] (char job) {
        for (auto& e : d) {
            if (e.first == job && --in[e.second] == 0) {
                ready_to_start.insert(e.second);
            }
        }
    };

    int time = 0;
    list<pair<char, int>> w;
    do {
        int min = min_element(ALL(w), [] (auto& a, auto& b) { return a.second < b.second; })->second;
        time += min;
        for (auto it = begin(w); it != end(w);) {
            it->second -= min;
            if (it->second > 0) {
                ++it;
            } else {
                finish(it->first);
                it = w.erase(it, next(it));
            }
        }
        while (w.size() < 5 && !ready_to_start.empty()) {
            char next_job = *begin(ready_to_start);
            w.push_back({next_job, next_job - 'A' + 61});
            ready_to_start.erase(begin(ready_to_start), next(begin(ready_to_start)));
        }
    } while (!w.empty());

    cout << time << endl;

    return 0;
}
