#include "../commons.h"

int main() {
    Vec nums = read_lines_signed_nums();
    cout << accumulate(ALL(nums), 0) << endl;
    return 0;
}
