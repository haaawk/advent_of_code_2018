#include "../commons.h"

int main() {
    Vec nums = read_lines_signed_nums();
    Set seen;
    seen.insert(0);
    Num res = 0;
    while(true) {
        for(Num x : nums) {
            res += x;
            if (!seen.insert(res).second) {
                cout << res << endl;
                return 0;
            }
        }
    }
    return 0;
}
