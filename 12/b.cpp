#include "../commons.h"

int main() {

    string s;
    cin >> s >> s >> s;

    s = string(5, '.') + s + string(5, '.');

    char t[2][2][2][2][2] = { '.' };

    auto c = [&] (char x) {
        return x == '.' ? 0 : 1;
    };

    auto get = [&] (string& x, int p, char ll, char l) -> char& {
        return t[c(ll)][c(l)][c(x[p])][c(x[p + 1])][c(x[p + 2])];
    };

    string p, a, r;
    while (cin >> p >> a >> r) {
        get(p, 2, p[0], p[1]) = r[0];
    }

    string last_pattern = "";
    int shift = 0;
    for (int64_t g = 0; g < 50000000000; ++g) {
        char prev = '.';
        char prev2 = '.';
        for (int i = 0; i < s.size() - 2; ++i) {
            char next_prev = s[i];
            s[i] = get(s, i, prev2, prev);
            prev2 = prev;
            prev = next_prev;
        }
        int first = s.find("#");
        int last = s.rfind("#");
        s = "....." + s.substr(first, last - first + 1) + ".....";
        shift += first - 5;
        if (s == last_pattern) {
            int64_t sum = 0;
            for (int i = 0; i < s.size(); ++i) {
                sum += s[i] == '.' ? 0 : (i + shift + 50000000000 - g - 6);
            }
            cout << sum << endl;
            return 0;
        }
        last_pattern = s;
    }

    return -1;
}
