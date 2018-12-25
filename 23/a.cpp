#include "../commons.h"
#include "../points.h"

struct bot {
    point<int, 3> p;
    int r;
};

int main() {

    auto bots = read_lines<bot>("pos=<(-?\\d+),(-?\\d+),(-?\\d+)>, r=(\\d+)", [&] (auto s) {
        return bot{{ stoi(s[1]), stoi(s[2]), stoi(s[3]) }, stoi(s[4])};
    });

    auto it = max_element(ALL(bots), [] (auto& a, auto& b) { return a.r < b.r; });

    cout << count_if(ALL(bots), [&] (auto& b) { return b.p.distance(it->p) <= it->r; }) << endl;

    return 0;
}
