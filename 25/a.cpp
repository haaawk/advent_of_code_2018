#include "../commons.h"
#include <find_and_union.h>
#include <for_each.h>
#include "../points.h"

int main() {
    using point = point<int, 4>;
    vector<point> points;
    int a, b, c, d;
    char sep;
    while (cin >> a) {
        cin >> sep >> b >> sep >> c >> sep >> d;
        points.push_back({a, b, c, d});
    }

    find_and_union fu(points.size());
    for_each_pair(points, [&] (int ix, int iy, auto& x, auto& y) {
        if (x.distance(y) <= 3) fu.merge(ix, iy);
    });

    cout << fu.count() << endl;

    return 0;
}
