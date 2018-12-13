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

    FOR(g, 0, 20) {
        char prev = '.';
        char prev2 = '.';
        FOR(i, 0, s.size() - 2) {
            char next_prev = s[i];
            s[i] = get(s, i, prev2, prev);
            prev2 = prev;
            prev = next_prev;
        }
        if (s[s.size() - 1] == '#' || s[s.size() - 2] == '#' || s[s.size() - 3] == '#') s += "..";
    }

    int64_t sum = 0;
    FORA(i, s) sum += s[i] == '.' ? 0 : i - 5;
    cout << sum << endl;

    return 0;
}
