#include "../commons.h"

struct start {
    string date;
    int hour;
    int time;
    int id;
};

struct up {
    string date;
    int hour;
    int time;
};

struct down {
    string date;
    int hour;
    int time;
};

using line_type = variant<start, up, down>;

int main() {

    auto events = read_lines<line_type>("\\[([-\\d]+) (\\d+):(\\d+)\\] Guard #(\\d+) begins shift",
                                        CONVERT(m, line_type(start{m[1], stoi(m[2]), stoi(m[3]), stoi(m[4])})),
                                        "\\[([-\\d]+) (\\d+):(\\d+)\\] falls asleep",
                                        CONVERT(m, line_type(down{m[1], stoi(m[2]), stoi(m[3])})),
                                        "\\[([-\\d]+) (\\d+):(\\d+)\\] wakes up",
                                        CONVERT(m, line_type(up{m[1], stoi(m[2]), stoi(m[3])})));
    sort(ALL(events), [] (const line_type& a, const line_type& b) {
        string date_a = VGET(a, date);
        string date_b = VGET(b, date);
        if (date_a < date_b) {
            return true;
        }
        if (date_b < date_a) {
            return false;
        }
        int hour_a = VGET(a, hour);
        int hour_b = VGET(b, hour);
        if (hour_a < hour_b) return true;
        if (hour_b < hour_a) return false;
        int time_a = VGET(a, time);
        int time_b = VGET(b, time);
        return time_a < time_b;
    });

    map<pair<int, int>, int> count;
    for (int i = 0; i < events.size();) {
        int id = get<start>(events[i]).id;
        int sleep_start = -1;
        ++i;
        while (i < events.size() && events[i].index() != 0) {
            if (events[i].index() == 2) {
                sleep_start = VGET(events[i], time);
            } else {
                FOR(j, sleep_start, VGET(events[i], time)) count[make_pair(id, j)]++;
                sleep_start = -1;
            }
            ++i;
        }
    }

    auto max = max_element(ALL(count), [] (auto& a, auto& b) { return a.second < b.second; });
    cout << max->first.first * max->first.second << endl;
    return 0;
}
