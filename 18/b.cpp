#include "../commons.h"

#define FORC(container, var1, var2) FORA(var1, container) FORA(var2, container[0])

template <typename T, typename C>
int64_t count(const C& board, const T& elem) {
    int64_t res = 0;
    FORC(board, i, j) res += (board[i][j] == elem) ? 1 : 0;
    return res;
}

int main() {

    auto lines = read_lines();

    map<vector<string>, int> cache;
    FOR(x, 0, 1000000000) {
        cache[lines] = x;
        decltype(lines) next(lines.size(), string(lines[0].size(), ' '));
        FORC(lines, i, j) {
            auto has = [&] (char c, int count) {
                auto check = [&] (int a, int b) {
                    if (a < 0 || b < 0 || a == lines.size() || b == lines[0].size()) return 0;
                    return lines[a][b] == c ? 1 : 0;
                };
                int res = 0;
                FOR(ii, i - 1, i + 2) FOR(jj, j - 1, j + 2)
                    if (!(ii == i && jj == j)) res += check(ii, jj);
                return res >= count;
            };

            switch (lines[i][j]) {
                case '.':
                    next[i][j] = has('|', 3) ? '|' : '.';
                    break;
                case '|':
                    next[i][j] = has('#', 3) ? '#' : '|';
                    break;
                case '#':
                    next[i][j] = (has('#', 1) && has('|', 1)) ? '#' : '.';
                    break;
            }
        }
        auto it = cache.find(next);
        if (it != end(cache)) {
            int cycle = x - it->second - 1;
            x += ((1000000000 - x) / cycle) * cycle;
        }
        lines = std::move(next);
    }

    cout << count(lines, '|') * count(lines, '#') << endl;

    return 0;
}
