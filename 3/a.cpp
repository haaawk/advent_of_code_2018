#include "../commons.h"

struct claim {
    int id;
    int x;
    int y;
    int w;
    int h;
};

int main() {
    map<pair<int, int>, int> count;
    auto claims = read_lines<claim>("#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)",
        CONVERT(m, (claim{stoi(m[1]), stoi(m[2]), stoi(m[3]), stoi(m[4]), stoi(m[5])})));
    for (auto& c : claims)
        FOR(i, c.x, c.x + c.w)
            FOR(j, c.y, c.y + c.h)
                count[make_pair(i, j)]++;

    cout << COUNT(count, e, e.second > 1) << endl;
    return 0;
}
