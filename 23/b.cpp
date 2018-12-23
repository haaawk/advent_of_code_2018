#include "../commons.h"

struct bot {
    int x, y, z, r;
};

int main() {

    auto bots = read_lines<bot>("pos=<(-?\\d+),(-?\\d+),(-?\\d+)>, r=(\\d+)", [&] (auto s) {
        return bot{stoi(s[1]), stoi(s[2]), stoi(s[3]), stoi(s[4])};
    });

    auto dist = [] (int x, int y, int z) { return abs(x) + abs(y) + abs(z); };

    auto [minx, maxx] = minmax_element(ALL(bots), [] (auto& a, auto&b) { return a.x < b.x; });
    auto [miny, maxy] = minmax_element(ALL(bots), [] (auto& a, auto&b) { return a.y < b.y; });
    auto [minz, maxz] = minmax_element(ALL(bots), [] (auto& a, auto&b) { return a.z < b.z; });

    int precision = 1;
    int limit = max(maxx->x, max(maxy->y, maxz->z));
    while (precision < limit) precision *= 10;

    auto scale = [&] (int x) { return x / precision; };

    int startx = scale(minx->x);
    int endx = scale(maxx->x);
    int starty = scale(miny->y);
    int endy = scale(maxy->y);
    int startz = scale(minz->z);
    int endz = scale(maxz->z);

    int max_x = 0, max_y = 0, max_z = 0, max = 0;
    while (precision > 1) {
        precision /= 10;

        max_x = max_y = max_z = max = 0;

        FOR(x, startx, endx + 1) FOR(y, starty, endy + 1) FOR(z, startz, endz + 1) {
            int count = count_if(ALL(bots), [&] (auto& b) { return abs(scale(b.x) - x) + abs(scale(b.y) - y) + abs(scale(b.z) - z) <= scale(b.r); });
            if (count == max) {
                if (dist(max_x, max_y, max_z) > dist(x, y, z)) {
                    max_x = x;
                    max_y = y;
                    max_z = z;
                }
            } else if (count > max) {
                max = count;
                max_x = x;
                max_y = y;
                max_z = z;
            }
        }

        startx = (max_x - 1) * 10;
        endx = (max_x + 1) * 10;
        starty = (max_y - 1) * 10;
        endy = (max_y + 1) * 10;
        startz = (max_z - 1) * 10;
        endz = (max_z + 1) * 10;
    }

    cout << dist(max_x, max_y, max_z) << endl;

    return 0;
}
