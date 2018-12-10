#include "../commons.h"

struct point {
    int x;
    int y;
    int vx;
    int vy;
};

int main() {
    vector<point> p;
    int x, y, vx, vy;
    while (scanf("position=< %d,  %d> velocity=< %d,  %d>\n", &x, &y, &vx, &vy) != EOF) {
        p.push_back({x, y, vx, vy});
    }

    for (int t = 0; ; ++t) {
        set<pair<int, int>> image;
        for (auto& pp : p) {
            pp.x += pp.vx;
            pp.y += pp.vy;
            image.insert(make_pair(pp.x, pp.y));
        }
        cout << t << endl;
        /*
        bool found = false;
        for (auto& pp: p) {
            if (image.count(make_pair(pp.x + 1, pp.y - 1)) > 0) continue;
            if (image.count(make_pair(pp.x - 1, pp.y - 1)) > 0) continue;
            if (image.count(make_pair(pp.x + 1, pp.y + 1)) > 0) continue;
            if (image.count(make_pair(pp.x - 1, pp.y + 1)) > 0) continue;
            if (image.count(make_pair(pp.x + 1, pp.y)) > 0 && image.count(make_pair(pp.x - 1, pp.y)) > 0
                && image.count(make_pair(pp.x, pp.y + 1)) > 0 && image.count(make_pair(pp.x, pp.y - 1)) == 0) {
                cout << pp.x << " " << pp.y << endl;
                for (int i = -1; i < 2; ++i) {
                    for (int j = -1; j < 2; ++j)
                        cout << image.count(make_pair(pp.x + i, pp.y + j));
                    cout << endl;
                }
                found = true;
                break;
            }
            if (image.count(make_pair(pp.x + 1, pp.y)) > 0 && image.count(make_pair(pp.x - 1, pp.y)) > 0
                && image.count(make_pair(pp.x, pp.y - 1)) > 0 && image.count(make_pair(pp.x, pp.y + 1)) == 0) {
                cout << pp.x << " " << pp.y << endl;
                for (int i = -1; i < 2; ++i) {
                    for (int j = -1; j < 2; ++j)
                        cout << image.count(make_pair(pp.x + i, pp.y + j));
                    cout << endl;
                }
                found = true;
                break;
            }
            if (image.count(make_pair(pp.x, pp.y + 1)) > 0 && image.count(make_pair(pp.x, pp.y - 1)) > 0
                && image.count(make_pair(pp.x + 1, pp.y)) > 0 && image.count(make_pair(pp.x - 1, pp.y)) == 0) {
                cout << pp.x << " " << pp.y << endl;
                for (int i = -1; i < 2; ++i) {
                    for (int j = -1; j < 2; ++j)
                        cout << image.count(make_pair(pp.x + i, pp.y + j));
                    cout << endl;
                }
                found = true;
                break;
            }
            if (image.count(make_pair(pp.x, pp.y + 1)) > 0 && image.count(make_pair(pp.x, pp.y - 1)) > 0
                && image.count(make_pair(pp.x - 1, pp.y)) > 0 && image.count(make_pair(pp.x + 1, pp.y)) == 0) {
                cout << pp.x << " " << pp.y << endl;
                for (int i = -1; i < 2; ++i) {
                    for (int j = -1; j < 2; ++j)
                        cout << image.count(make_pair(pp.x + i, pp.y + j));
                    cout << endl;
                }
                found = true;
                break;
            }
        }
        if (found) break;
        */
        if (t > 10299 - 10 && t < 10299 + 10) {
            int minr = 500, maxr = 0, minc = 500, maxc = 0;
            for (auto& pp : p) {
                minr = min(minr, pp.x);
                maxr = max(maxr, pp.x);
                minc = min(minc, pp.y);
                maxc = max(maxc, pp.y);
            }
            for (int i = minr; i <= maxr; ++i) {
                for (int j = minc; j <= maxc; ++j) {
                    bool f = false;
                    for (auto& pp : p) {
                        if (pp.x == i && pp.y ==j) {
                            cout << '#';
                            f = true;
                            break;
                        }
                    }
                    if (!f) cout << ' ';
                }
                cout << endl;
            }
        }
        if (t == 10299 + 10) break;
    }

    return 0;
}
