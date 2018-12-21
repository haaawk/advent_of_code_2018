#include "../commons.h"

pair<int, set<pair<int, int>>> paths(const string& P, int p, const set<pair<int, int>>& points, vector<string>& b) {
    ++p;
    set<pair<int, int>> res(ALL(points));
    while (true) {
        while (P[p] != '(' && P[p] != '|' && P[p] != ')' && P[p] != '$') {
            set<pair<int, int>> new_res;
            for (auto point : res) {
                int x = point.first;
                int y = point.second;
                switch(P[p]) {
                    case 'N':
                        --x;
                        assert(x > -1);
                        b[x][y] = '-';
                        --x;
                        assert(x > -1);
                        if (b[x][y] != 'X')
                        b[x][y] = '.';
                        break;
                    case 'E':
                        ++y;
                        assert(y < b[0].size());
                        b[x][y] = '|';
                        ++y;
                        assert(y < b[0].size());
                        if (b[x][y] != 'X')
                        b[x][y] = '.';
                        break;
                    case 'S':
                        ++x;
                        assert(x < b.size());
                        b[x][y] = '-';
                        ++x;
                        assert(x < b.size());
                        if (b[x][y] != 'X')
                        b[x][y] = '.';
                        break;
                    case 'W':
                        --y;
                        assert(y > -1);
                        b[x][y] = '|';
                        --y;
                        assert(y > -1);
                        if (b[x][y] != 'X')
                        b[x][y] = '.';
                        break;
                }
                new_res.insert({x,y});
            }
            res = std::move(new_res);
            ++p;
        }
        if (P[p] == '(') {
            auto op = paths(P, p, res, b);
            p = op.first;
            res = std::move(op.second);
            ++p;
        } else {
            while (P[p] == '|') {
                auto op = paths(P, p, points, b);
                p = op.first;
                res.insert(ALL(op.second));
            }
            return {p, std::move(res)};
        }
    };
}

int main() {

    auto lines = read_lines();
    assert(lines.size() == 1);

    int size = 2000;
    vector<string> B(size, string(size, '#'));
    int x = 1000;
    int y = 1000;
    B[x][y] = 'X';
    paths(lines[0], 0, {make_pair(x,y)}, B);

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

    for (int i = 0; i < d.size(); ++i)
        for (int j = 0; j < d[0].size(); ++j)
            if (d[i][j] < inf) res = max(res, d[i][j]);

    cout << res << endl;
    return 0;
}
