#include "../commons.h"

struct claim {
    int id;
    int x;
    int y;
    int w;
    int h;

    int startx() const { return x; }
    int endx() const { return x + w; }
    int starty() const { return y; }
    int endy() const { return y + h; }
    bool intersects(const claim& o) {
        return startx() < o.endx() && o.startx() < endx() && starty() < o.endy() && o.starty() < endy();
    }
};

int main() {
    auto claims = read_lines<claim>("#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)",
        CONVERT(m, (claim{stoi(m[1]), stoi(m[2]), stoi(m[3]), stoi(m[4]), stoi(m[5])})));
    cout << FIND(claims, c, !CONTAINS(claims, o, o.id != c.id && c.intersects(o)))->id << endl;
    return 0;
}
