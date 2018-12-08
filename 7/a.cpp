#include "../commons.h"

using dep = pair<char, char>;

int main() {

    vector<dep> d = read_lines<dep>("Step ([A-Z]) must be finished before step ([A-Z]) can begin.",
                                    CONVERT(m, dep(m[1].str()[0], m[2].str()[0])));

    map<char, int> in;
    for (auto p : d) in[p.second]++;

    set<char> ready_to_start;
    for (auto p : d) {
        if (in[p.first] == 0) {
            ready_to_start.insert(p.first);
        }
    }

    auto finish = [&] (char job) {
        for (auto& e : d) {
            if (e.first == job && --in[e.second] == 0) {
                ready_to_start.insert(e.second);
            }
        }
    };

    string result;
    while (!ready_to_start.empty()) {
        char next_job = *begin(ready_to_start);
        ready_to_start.erase(begin(ready_to_start), next(begin(ready_to_start)));
        result += next_job;
        finish(next_job);
    }

    cout << result << endl;

    return 0;
}
