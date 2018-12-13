#include "../commons.h"

int main() {

    int M = 6042;

    auto count = [&] (int x, int y) {
        int id = x + 10;
        return ((((id * y + M) * id) / 100) % 10) - 5;
    };

    int max = -1000000;
    int bx = -1;
    int by = -1;
    FOR(i, 1, 299)
        FOR(j, 1, 299) {
            int sum = 0;
            FOR(a, 0, 3)
                FOR(b, 0, 3)
                    sum += count(i + a, j + b);
            if (sum > max) {
                max = sum;
                bx = i;
                by = j;
            }
        }

    cout << bx << "," << by << endl;

    return 0;
}
