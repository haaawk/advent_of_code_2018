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
    for (int i = 1; i < 299; ++i)
        for (int j = 1; j < 299; ++j) {
            int sum = 0;
            for (int a = 0; a < 3; ++a)
                for (int b = 0; b < 3; ++b)
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
