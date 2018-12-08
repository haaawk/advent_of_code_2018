#include "../commons.h"

bool react(char a, char b) {
    return toupper(a) == toupper(b) && isupper(a) != isupper(b);
}

void compress(list<char>& p) {
    auto it = begin(p);
    while (true) {
        it = adjacent_find(it, end(p), react);
        if (it == end(p))
            break;
        it = p.erase(it, next(it, 2));
        if (it != begin(p))
            --it;
    }
}

int main() {
    string line;
    cin >> line;
    list<char> p(ALL(line));

    compress(p);

    set<char> chars;
    for (char c : p) {
        chars.insert(toupper(c));
    }

    auto res = p.size();
    for (char c : chars) {
        list pp(ALL(p));
        pp.remove_if(CHECK(e, toupper(e) == c));
        compress(pp);
        res = min(res, pp.size());
    }
    cout << res << endl;
    return 0;
}
