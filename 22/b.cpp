#include "../commons.h"

struct state {
    int x;
    int y;
    int m;
    int64_t d;
    bool operator<(const state& o) const { return d > o.d; }
};

int main() {
    int D = 4848;
    int M = 20183;
    int tx = 15;
    int ty = 700;
    int lx = 8 * tx;
    int ly = 8 * ty;
    int64_t inf = 10 * lx * ly;
    vector<vector<vector<int64_t>>> d(3, vector<vector<int64_t>>(lx, vector<int64_t>(ly, inf)));

    vector<vector<int64_t>> index(lx, vector<int64_t>(ly));
    index[0][0] = D % M;
    index[tx][ty] = D % M;

    FOR(i, 1, lx) index[i][0] = (i * 16807 + D) % M;
    FOR(j, 1, ly) index[0][j] = (j * 48271 + D) % M;
    FOR(i, 1, lx) FOR(j, 1, ly)
        if (i != tx || j != ty)
            index[i][j] = (index[i - 1][j] * index[i][j - 1] + D) % M;

    vector<vector<bool>> allowed = {
        {true, true, false},
        {false, true, true},
        {true, false, true}
    };

    d[0][0][0] = 0;
    priority_queue<state> q;
    q.push({0, 0, 0, 0});
    vector<vector<vector<bool>>> done(3, vector<vector<bool>>(lx, vector<bool>(ly, false)));
    while (!q.empty() && !done[0][tx][ty]) {
        state c = q.top();
        q.pop();
        if (!done[c.m][c.x][c.y]) {
            done[c.m][c.x][c.y] = true;
            auto relax = [&] (int x, int y, int m, int t) {
                if (allowed[index[x][y] % 3][m] && d[m][x][y] > d[c.m][c.x][c.y] + t) {
                    d[m][x][y] = d[c.m][c.x][c.y] + t;
                    q.push({x, y, m, d[m][x][y]});
                }
            };
            auto tool_change = [&] (int s) {
                relax(c.x, c.y, (c.m + s) % 3, 7);
            };
            tool_change(1);
            tool_change(2);
            auto move = [&] (int a, int b) {
                int x = c.x + a;
                int y = c.y + b;
                if (x > -1 && y > -1 && x < lx && y < ly) {
                    relax(x, y, c.m, 1);
                }
            };
            move(1, 0);
            move(-1, 0);
            move(0, 1);
            move(0, -1);
        }
    }

    cout << d[0][tx][ty] << endl;

    return 0;
}
