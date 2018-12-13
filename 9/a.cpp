#include "../commons.h"

struct game {
    int p;
    int m;
};

int main() {

    auto lines = read_lines<game>("(\\d+) players; last marble is worth (\\d+) points",
                              [] (auto&& m) {return game{stoi(m[1]), stoi(m[2])}; });

    int p = lines[0].p;
    int m = lines[0].m;

    vector<uint64_t> s(p);
    list<uint64_t> ch;
    ch.push_back(0);
    int cp = 0;
    auto it = begin(ch);
    auto move = [&] {
        ++it;
        if (it == end(ch)) it = begin(ch);
    };
    auto back = [&] {
        if (it == begin(ch)) it = end(ch);
        --it;
    };
    for (uint64_t i = 1; i < m; ++i, cp = (cp + 1) % p) {
        if (i % 23 == 0) {
            FOR(j, 0, 7)  back();
            s[cp] += i + *it;
            it = ch.erase(it);
        } else {
            move();
            move();
            it = ch.insert(it, i);
        }
    }

    cout << *max_element(ALL(s)) << endl;

    return 0;
}
