#include "../commons.h"

int main() {
    int D = 4848;
    int tx = 15;
    int ty = 700;
    int M = 20183;

    vector<vector<int64_t>> index(tx + 1, vector<int64_t>(ty + 1));
    index[0][0] = D % M;
    index[tx][ty] = D % M;

    FOR(i, 1, tx + 1) index[i][0] = (i * 16807 + D) % M;
    FOR(j, 1, ty + 1) index[0][j] = (j * 48271 + D) % M;
    FOR(i, 1, tx + 1) FOR(j, 1, ty + 1)
        if (i != tx || j != ty)
            index[i][j] = (index[i - 1][j] * index[i][j - 1] + D) % M;

    int64_t res = 0;
    FOR(i, 0, tx + 1) FOR(j, 0, ty + 1) res += index[i][j] % 3;
    cout << res << endl;

    return 0;
}
