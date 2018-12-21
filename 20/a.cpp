#include "../commons.h"

set<pair<int, int>> paths(const string& P, int& p, const set<pair<int, int>>& points, vector<string>& b) {
    ++p;
    set<pair<int, int>> res(ALL(points));
    auto move = [&] (int xx, int yy, char door) mutable {
        set<pair<int, int>> new_res;
        for (auto point : res) {
            int x = point.first;
            int y = point.second;
            auto step = [&] {
                x += xx;
                y += yy;
                assert(x > -1);
                assert(y > -1);
                assert(x < b.size());
                assert(y < b[0].size());
            };
            step();
            b[x][y] = door;
            step();
            b[x][y] = b[x][y] == 'X' ? 'X' : '.';
            new_res.insert({x,y});
        }
        res = std::move(new_res);
    };
    while (P[p] != ')' && P[p] != '$') {
        switch(P[p]) {
            case 'N': move(-1, 0, '-'); break;
            case 'E': move(0, 1, '|'); break;
            case 'S': move(1, 0, '-'); break;
            case 'W': move(0, -1, '|'); break;
            case '(': res = paths(P, p, res, b); break;
            case '|':
                auto op = paths(P, p, points, b);
                res.insert(ALL(op));
                --p;
                break;
        }
        ++p;
    }
    return res;
}

int main() {

    auto lines = read_lines();
    assert(lines.size() == 1);

    int size = 2000;
    vector<string> B(size, string(size, '#'));
    int x = 1000;
    int y = 1000;
    B[x][y] = 'X';
    int p = 0;
    paths(lines[0], p, {make_pair(x,y)}, B);

    int inf = 2000000000;
    vector<vector<int>> d(size, vector<int>(size, inf));

    d[x][y] = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        auto c = q.front();
        q.pop();

        int a = c.first;
        int b = c.second;

        auto check = [&] (int aa, int bb) {
            if (B[a + aa][b + bb] != '#' && d[a + aa + aa][b + bb + bb] > d[a][b] + 1) {
                d[a + aa + aa][b + bb + bb] = d[a][b] + 1;
                q.push({a + aa + aa, b + bb + bb});
            }
        };
        check(-1, 0);
        check(1, 0);
        check(0, -1);
        check(0, 1);
    }

    int res = 0;
    FORA(i, d) FORA(j, d[0]) if (d[i][j] < inf) res = max(res, d[i][j]);

    cout << res << endl;
    return 0;
}
