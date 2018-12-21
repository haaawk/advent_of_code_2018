#include "../commons.h"

struct instruction {
    int op;
    int a;
    int b;
    int c;

    instruction(int a) : op(-1), a(a), b(-1), c(-1) {}
    instruction(int op, int a, int b, int c) : op(op), a(a), b(b), c(c) {}
};

int main() {
    auto lines = read_lines<instruction>("#ip (\\d+)", [] (auto& s) { return instruction(stoi(s[1])); },
                                         "addr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(0, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "addi (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(1, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "mulr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(2, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "muli (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(3, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "banr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(4, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "bani (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(5, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "borr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(6, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "bori (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(7, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "setr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(8, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "seti (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(9, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "gtir (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(10, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "gtri (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(11, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "gtrr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(12, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "eqir (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(13, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "eqri (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(14, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         },
                                         "eqrr (\\d+) (\\d+) (\\d+)", [] (auto& s) {
                                             return instruction(15, stoi(s[1]), stoi(s[2]), stoi(s[3]));
                                         });

    vector<int64_t> regs(6);
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

    int ip_reg = lines[0].a;
    lines.erase(begin(lines));
    int ip = 0;
    set<int64_t> cache;
    int64_t last = -1;
    while (ip > -1 && ip < lines.size()) {
        regs[ip_reg] = ip;
        a = lines[ip].a;
        b = lines[ip].b;
        c = lines[ip].c;
        instructions[lines[ip].op]();
        ip = regs[ip_reg];
        ++ip;
        if (ip == 28) {
            if (!cache.insert(regs[1]).second) {
                cout << last << endl;
                break;
            }
            last = regs[1];
        }
    }

    return 0;
}
