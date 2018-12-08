#include "../commons.h"

bool react(char a, char b) {
    return toupper(a) == toupper(b) && a != b;
}

int main() {
    string line;
    cin >> line;

    list<char> p(ALL(line));
    auto it = begin(p);
    while (true) {
        it = adjacent_find(it, end(p), react);
        if (it == end(p))
            break;
        it = p.erase(it, next(it, 2));
        if (it != begin(p))
            --it;
    }

    cout << p.size() << endl;

    return 0;
}
