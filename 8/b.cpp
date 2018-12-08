#include "../commons.h"

int sum() {
    int child_count, metadata_count;
    cin >> child_count >> metadata_count;
    int res = 0;
    vector<int> c(child_count);
    for (int i = 0; i < child_count; ++i)
        c[i] = sum();
    for (int i = 0; i < metadata_count; ++i) {
        int m;
        cin >> m;
        if (child_count == 0) {
            res += m;
        } else {
            --m;
            res += (m < child_count) ? c[m] : 0;
        }
    }
    return res;
}

int main() {

    cout << sum() << endl;

    return 0;
}
