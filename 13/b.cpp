#include "../commons.h"

struct cart {
    Num x;
    Num y;
    int d;
    int t;
    bool removed;
    cart(Num x, Num y, int d) : x(x), y(y), d(d), t(0), removed(false) {}
};

int main() {

    auto lines = read_lines();

    vector<cart> carts;
    map<char, char> replacements = {{'<', '-'}, {'^', '|'}, {'>', '-'}, {'v', '|'}};
    map<char, int> directions = {{'<', 0}, {'^', 1}, {'>', 2}, {'v', 3}};
    FORA(i, lines) {
        FORA(j, lines[0]) {
            char& cell = lines[i][j];
            char replacement = replacements[cell];
            if (replacement != '\0') {
                carts.push_back({i, j, directions[cell]});
                cell = replacement;
            }
        }
    }

    auto remove_crash = [&] (auto& c) {
        c.removed = true;
        for (auto& cc : carts)
            if (!cc.removed && cc.x == c.x && cc.y == c.y) {
                cc.removed = true;
                return true;
            }
        c.removed = false;
        return false;
    };

    pair<int, int> steps[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    pair<int, int> turns[4] = {{3, 1}, {2, 0}, {1, 3}, {0, 2}};
    while (carts.size() > 1) {
        sort(ALL(carts), [] (auto& a, auto& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });
        for(auto& c : carts) {
            if (c.removed) continue;
            auto step = steps[c.d];
            c.x += step.first;
            c.y += step.second;
            if (remove_crash(c)) continue;
            switch (lines[c.x][c.y]) {
                case '/': c.d = turns[c.d].first; break;
                case '\\': c.d = turns[c.d].second; break;
                case '+':
                    switch (c.t) {
                        case 0: c.d = (c.d + 3) % 4; break;
                        case 2: c.d = (c.d + 1) % 4; break;
                    }
                    c.t = (c.t + 1) % 3;
                    break;
            }
        }
        vector<cart> new_carts;
        copy_if(ALL(carts),back_inserter(new_carts), CHECK(c, !c.removed));
        carts = std::move(new_carts);
    }

    cout << carts[0].y << ',' << carts[0].x << endl;

    return 0;
}
