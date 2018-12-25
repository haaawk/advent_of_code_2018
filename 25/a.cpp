#include "../commons.h"

struct point {
    int id, a, b, c, d;
};

int main() {
    vector<point> points;
    int id = 0, a, b, c, d;
    char sep;
    while (cin >> a) {
        cin >> sep >> b >> sep >> c >> sep >> d;
        points.push_back({id++, a, b, c, d});
    }

    vector<int> FU(points.size(), -1);

    auto find = [&] (int x) {
        int p = x;
        while (FU[p] > 0) p = FU[p];
        while (FU[x] > 0) x = exchange(FU[x], p);
        return x;
    };

    auto merge = [&] (int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (FU[a] > FU[b]) swap(a, b);
        FU[a] += FU[b];
        FU[b] = a;
    };

    for (auto& p : points)
        for(auto& pp : points)
            if (abs(p.a - pp.a) + abs(p.b - pp.b) + abs(p.c - pp.c) + abs(p.d - pp.d) <= 3)
                merge(p.id, pp.id);

    cout << count_if(ALL(FU), [] (int x) { return x < 0; }) << endl;

    return 0;
}
