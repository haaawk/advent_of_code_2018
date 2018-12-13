#include "../commons.h"

int sum() {
    int child_count, metadata_count;
    cin >> child_count >> metadata_count;
    int res = 0;
    FOR(i, 0, child_count) res += sum();
    FOR(i, 0, metadata_count) {
        int m;
        cin >> m;
        res += m;
    }
    return res;
}

int main() {

    cout << sum() << endl;

    return 0;
}
