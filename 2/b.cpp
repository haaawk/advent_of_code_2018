#include "../commons.h"
#include "../for_each.h"

int main() {
    vector<string> lines = read_lines();
    for_each_pair(lines, [] (auto& a, auto& b) {
        Num diff = 0;
        int diff_pos = 0;
        for (int p = 0; diff < 2 && p < a.size(); ++p) {
            if (a[p] != b[p]) {
                ++diff;
                diff_pos = p;
            }
        }
        if (diff == 1) {
            a.erase(a.begin() + diff_pos, a.begin() + diff_pos + 1);
            cout << a << endl;
            return true;
        }
        return false;
    });
    return 0;
}
