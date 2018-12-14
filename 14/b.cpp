#include "../commons.h"

int main() {
    vector<int> P = {0, 8, 4, 6, 0, 1};
    vector<int> s = {3, 7};

    auto check = [&] {
        if (s.size() >= P.size() && equal(rbegin(P), rend(P), rbegin(s))) {
            cout << s.size() - P.size() << endl;
            exit(0);
        }
    };

    int a = 0;
    int b = 1;
    while (true) {
        int n = s[a] + s[b];
        if (n > 9) {
            s.push_back(1);
            n %= 10;
            check();
        }
        s.push_back(n);
        check();

        a = (a + s[a] + 1) % s.size();
        b = (b + s[b] + 1) % s.size();
    }

    return -1;
}
