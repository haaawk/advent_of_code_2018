#include "../commons.h"
#include "../board.h"

using position = board<char>::position;

int main() {

    auto b = read_char_board();

    map<board<char>, int> cache;
    FOR(x, 0, 1000000000) {
        cache[b] = x;
        b.transform('.', [&] (position p) { return p.count_neighbours('|') > 2 ? '|' : '.'; },
                    '|', [&] (position p) { return p.count_neighbours('#') > 2 ? '#' : '|'; },
                    '#', [&] (position p) {
                        return (p.count_neighbours('#') > 0 && p.count_neighbours('|') > 0) ? '#' : '.';
                     });
        auto it = cache.find(b);
        if (it != end(cache)) {
            int cycle = x - it->second - 1;
            x += ((1000000000 - x) / cycle) * cycle;
        }
    }

    cout << b.count('|') * b.count('#') << endl;

    return 0;
}
