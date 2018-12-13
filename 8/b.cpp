#include "../commons.h"

int sum() {
    int child_count, metadata_count;
    cin >> child_count >> metadata_count;
    int res = 0;
    vector<int> c(child_count);
    FOR(i, 0, child_count) c[i] = sum();
    FOR(i, 0, metadata_count) {
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
