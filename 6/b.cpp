#include "../commons.h"

using point = pair<int, int>;

int main() {
    const int limit = 10000;
    vector<point> points;
    int minx = 1000, miny = 1000, maxx = 0, maxy = 0;
    {
        char c;
        int x, y;
        while (cin >> x >> c >> y) {
            minx = min(minx, x);
            miny = min(miny, y);
            maxx = max(maxx, x);
            maxy = max(maxy, y);
            point p{x, y};
            points.push_back(p);
        }
    }

    assert(minx >= 0);
    assert(miny >= 0);

    vector<int> x_summary(maxx + 1);
    vector<int> y_summary(maxy + 1);

    FOR(x, minx, maxx + 1)
        for (auto& p : points)
            x_summary[x] += abs(p.first - x);

    FOR(y, miny, maxy + 1)
        for (auto& p : points)
            y_summary[y] += abs(p.second - y);

    auto total_axis_distance = [&] (vector<int>& s, int x, int min, int max) -> Num {
        if (x < min) return s[min] + points.size() * (min - x);
        if (x > max) return s[max] + points.size() * (x - max);
        return s[x];
    };

    auto total_distance = [&] (int x, int y) {
        return total_axis_distance(x_summary, x, minx, maxx) + total_axis_distance(y_summary, y, miny, maxy);
    };

    int count = 0;
    FOR(x, minx - limit, maxx + limit)
        FOR(y, miny - limit, maxy + limit)
            count += total_distance(x, y) < limit ? 1 : 0;

    cout << count << endl;

    return 0;
}
