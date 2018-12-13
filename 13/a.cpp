#include "../commons.h"

struct cart {
    Num x;
    Num y;
    int d;
    int t;
    cart(Num x, Num y, int d) : x(x), y(y), d(d), t(0) {}
};

int main() {

    auto lines = read_lines();

    set<pair<Num, Num>> taken;
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
                taken.insert(make_pair(i, j));
            }
        }
    }

    pair<int, int> steps[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    pair<int, int> turns[4] = {{3, 1}, {2, 0}, {1, 3}, {0, 2}};
    while (true) {
        sort(ALL(carts), [] (auto& a, auto& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });
        for(auto& c : carts) {
            auto step = steps[c.d];
            auto cur = make_pair(c.x, c.y);
            c.x += step.first;
            c.y += step.second;
            auto next = make_pair(c.x, c.y);
            if (!taken.insert(next).second) {
                cout << c.y << ',' << c.x << endl;
                return 0;
            }
            taken.erase(cur);

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
    }

    return -1;
}
