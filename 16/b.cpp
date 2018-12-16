#include "../commons.h"

int main() {

    auto lines = read_lines();

    set<int> candidates[16];
    FOR(i, 0, 16) FOR(j, 0, 16) candidates[i].insert(j);

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

    auto read_instruction = [&] (int line_no) {
        stringstream str(lines[line_no]);
        str >> op >> a >> b >> c;
    };

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
        read_instruction(line_no + 1);
        auto regs_after = read_regs(line_no + 2);
        line_no += 4;

        auto check = [&] (auto&& fn) {
            regs = regs_before;
            fn();
            return regs == regs_after;
        };

        FORA(i, instructions) if (!check(instructions[i])) candidates[op].erase(i);
    }

    line_no += 2;

    vector<int> op_codes(16, -1);

    int found = 0;
    while (found < 16) {
        FOR(i, 0, 16) {
            if (candidates[i].size() == 1) {
                ++found;
                op_codes[i] = *candidates[i].begin();
                FOR(j, 0, 16) candidates[j].erase(op_codes[i]);
            }
        }
    }

    regs = vector(4, 0);
    for (; line_no < lines.size(); ++line_no) {
        read_instruction(line_no);
        instructions[op_codes[op]]();
    }

    cout << regs[0] << endl;

    return 0;
}
