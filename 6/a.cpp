#include "../commons.h"

using point = pair<int, int>;

int main() {
    queue<point> points;
    map<point, int> d;
    map<point, int> o;
    map<int, int> count;
    char c;
    int x, y;
    int minx = 1000, miny = 1000, maxx = 0, maxy = 0;
    while (cin >> x >> c >> y) {
        minx = min(minx, x);
        miny = min(miny, y);
        maxx = max(maxx, x);
        maxy = max(maxy, y);
        point p{x, y};
        points.push(p);
        d[p] = 0;
        o[p] = points.size();
        count[points.size()] = 1;
    }

    auto check_next = [&] (int owner, int dist, point next) {
        auto it = d.find(next);
        if (it == end(d)) {
            d[next] = dist;
            o[next] = owner;
            count[owner]++;
            points.push(next);
        } else {
            int& next_owner = o[next];
            if (it->second == dist && next_owner != -1 && next_owner != owner) {
                count[next_owner]--;
                next_owner = -1;
            }
        }
    };

    set<int> inf;

    while (!points.empty()) {
        point p = points.front();
        points.pop();
        int owner = o[p];
        int dist = d[p] + 1;
        if (owner == -1) continue;
        if (p.first > minx) {
            check_next(owner, dist, {p.first - 1, p.second});
        } else {
            inf.insert(owner);
        }

        if (p.first < maxx) {
            check_next(owner, dist, {p.first + 1, p.second});
        } else {
            inf.insert(owner);
        }
        if (p.second > miny) {
            check_next(owner, dist, {p.first, p.second - 1});
        } else {
            inf.insert(owner);
        }
        if (p.second < maxy) {
            check_next(owner, dist, {p.first, p.second + 1});
        } else {
            inf.insert(owner);
        }
    }

    for (int x : inf) count[x] = 0;

    cout << max_element(ALL(count), [] (auto&& a, auto&& b) { return a.second < b.second; })->second << endl;

    return 0;
}
