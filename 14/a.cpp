#include "../commons.h"

int main() {
    int N = 84601;
    vector<int> s = {3, 7};

    int a = 0;
    int b = 1;
    while (s.size() < N + 10) {
        int n = s[a] + s[b];
        if (n > 9) {
            s.push_back(1);
            n %= 10;
        }
        s.push_back(n);

        a = (a + s[a] + 1) % s.size();
        b = (b + s[b] + 1) % s.size();
    }

    FOR(i, 0, 10) cout << s[N + i];
    cout << endl;

    return 0;
}
