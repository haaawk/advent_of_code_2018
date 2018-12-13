#include "../commons.h"

int main() {
    vector<string> lines = read_lines();
    Num a = 0;
    Num b = 0;
    FORA(i, lines) {
        string& line = lines[i];
        map<char, Num> count;
        for (char c : line) {
            count[c]++;
        }
        a += CONTAINS(count, it, it.second == 2) ? 1 : 0;
        b += CONTAINS(count, it, it.second == 3) ? 1 : 0;
    }
    cout << a * b << endl;
    return 0;
}
