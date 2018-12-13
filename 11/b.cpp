#include "../commons.h"

int main() {
    int S = 6042;
    int GS = 300;

    int max = -1000000;
    int bx = -1;
    int by = -1;
    int bs = -1;

    vector<vector<vector<int>>> g(GS, vector<vector<int>>(GS, vector<int>(GS, 0)));
    auto for_each_rect = [&] (int size, auto&& fn) {
        FOR(i, 0, GS - size)
            FOR(j, 0, GS - size) {
                int val = g[size][i][j] = fn(i, j);
                if (val > max) {
                    max = val;
                    bx = i + 1;
                    by = j + 1;
                    bs = size + 1;
                }
            }
    };

    for_each_rect(0, [&] (int i, int j) {
        int id = i + 11;
        return ((((id * (j + 1) + S) * id) / 100) % 10) - 5;
    });
    for_each_rect(1, [&] (int i, int j) {
        return g[0][i][j] + g[0][i + 1][j] + g[0][i][j + 1] + g[0][i + 1][j + 1];
    });
    FOR(size, 2, GS - 1)
        for_each_rect(size, [&] (int i, int j) {
            return g[size - 1][i + 1][j] + g[size - 1][i][j + 1]
                - g[size - 2][i + 1][j + 1] + g[0][i][j] + g[0][i + size][j + size];
        });

    cout << bx << "," << by << "," << bs << endl;

    return 0;
}
