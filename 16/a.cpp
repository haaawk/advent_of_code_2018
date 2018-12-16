#include "../commons.h"

int main() {

    auto lines = read_lines();

    vector<int> regs(4);
    int op, a, b, c;
    vector<function<void()>> instructions = {
        [&] { regs[c] = regs[a] + regs[b]; },
        [&] { regs[c] = regs[a] + b; },
        [&] { regs[c] = regs[a] * regs[b]; },
        [&] { regs[c] = regs[a] * b; },
        [&] { regs[c] = regs[a] & regs[b]; },
        [&] { regs[c] = regs[a] & b; },
        [&] { regs[c] = regs[a] | regs[b]; },
        [&] { regs[c] = regs[a] | b; },
        [&] { regs[c] = regs[a]; },
        [&] { regs[c] = a; },
        [&] { regs[c] = a > regs[b] ? 1 : 0; },
        [&] { regs[c] = regs[a] > b ? 1 : 0; },
        [&] { regs[c] = regs[a] > regs[b] ? 1 : 0; },
        [&] { regs[c] = a == regs[b] ? 1 : 0; },
        [&] { regs[c] = regs[a] == b ? 1 : 0; },
        [&] { regs[c] = regs[a] == regs[b] ? 1 : 0; }
    };

    int res = 0;

    int line_no = 0;
    while (!lines[line_no + 1].empty()) {
        auto read_regs = [&] (int line_no) {
            vector<int> regs(4);
            stringstream str(lines[line_no]);
            string prefix;
            str >> prefix;
            char sep;
            FOR(i, 0, 4) str >> sep >> regs[i];
            return regs;
        };
        auto regs_before = read_regs(line_no);
        stringstream str(lines[line_no + 1]);
        str >> op >> a >> b >> c;
        auto regs_after = read_regs(line_no + 2);
        line_no += 4;

        auto check = [&] (auto&& fn) {
            regs = regs_before;
            fn();
            return regs == regs_after;
        };

        if (count_if(ALL(instructions), CHECK(ins, check(ins))) > 2) ++res;
    }

    cout << res << endl;

    return 0;
}
