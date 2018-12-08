#include "../commons.h"

int sum() {
    int child_count, metadata_count;
    cin >> child_count >> metadata_count;
    int res = 0;
    for (int i = 0; i < child_count; ++i)
        res += sum();
    for (int i = 0; i < metadata_count; ++i) {
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
