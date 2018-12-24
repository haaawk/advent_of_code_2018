#include "../commons.h"

struct group {
    int size, hp, damage, initiative;
    string damage_type;
    set<string> weaknesses, immunities;
    bool infection, selected = false;
    group* target = nullptr;
};

int main() {
    const string pattern =
        "^(\\d+) units each with (\\d+) hit points"
        "( \\((\\w+) to ([\\w, ]+)(; (\\w+) to ([\\w, ]+))?\\))?"
        " with an attack that does (\\d+) (\\w+) damage at initiative (\\d+)$";
    const regex r(pattern);

    vector<group> groups;
    auto read = [&] (bool infection) {
        string line;
        getline(cin, line);
        while (getline(cin, line) && !line.empty()) {
            smatch m;
            if (!regex_match(line, m, r)) {
                cerr << "Line [" << line << "] does not match pattern [" << pattern << "]" << endl;
                exit(-1);
            }
            auto parse_set = [&] (string m) {
                set<string> res;
                const regex word_regex("(\\w+)");
                transform(sregex_iterator(begin(m), end(m), word_regex),
                          sregex_iterator(),
                          inserter(res, res.end()),
                          [] (auto& sm) { return sm.str(); });
                return res;
            };
            auto parse = [&] (const string& name) {
                return m[4] == name ? parse_set(m[5]) : (m[7] == name ? parse_set(m[8]) : set<string>());
            };
            groups.push_back(
                {stoi(m[1]), stoi(m[2]), stoi(m[9]), stoi(m[11]), m[10], parse("weak"), parse("immune"), infection});
        }
    };

    read(false);
    read(true);

    sort(ALL(groups), [] (auto& a, auto& b) { return a.initiative > b.initiative; });

    auto power = [&] (auto& g) {
        return g.size * g.damage;
    };
    auto damage = [&] (auto& g, auto& t) {
        int d = power(g);
        if (t.weaknesses.count(g.damage_type) > 0) {
            return d * 2;
        }
        if (t.immunities.count(g.damage_type) > 0) {
            return 0;
        }
        return d;
    };
    auto count = [&] (bool infection) {
        return accumulate(ALL(groups), 0, [&] (int sum, auto& g) { return sum + (g.infection == infection ? g.size : 0); });
    };
    while (count(true) > 0 && count(false) > 0) {
        vector<group*> target_phase_order;
        for (auto& g : groups) target_phase_order.push_back(&g);
        sort(ALL(target_phase_order), [&] (auto& a, auto& b) {
            return power(*a) > power(*b) || (power(*a) == power(*b) && a->initiative > b->initiative);
        });
        for (auto& g : groups) {
            g.selected = false;
            g.target = nullptr;
        }
        for (auto& gg : target_phase_order) {
            group& g = *gg;
            if (g.size == 0) continue;
            auto qualify = [&] (const auto& x) {
                return (x.size > 0 && x.infection != g.infection && !x.selected) ? 1 : 0;
            };
            auto cmp = [] (const auto& a, const auto& b, auto&& fn) { return a < b || (a == b && fn()); };
            auto it = max_element(ALL(groups), [&] (const auto& a, const auto& b) {
                return cmp(qualify(a), qualify(b), [&] {
                    return cmp(damage(g, a), damage(g, b), [&] {
                        return cmp(power(a), power(b), [&] { return a.initiative < b.initiative; });
                    });
                });
            });
            if (it != end(groups) && qualify(*it) == 1 && damage(g, *it) > 0) {
                it->selected = true;
                g.target = &*it;
            }
        }

        for (auto& g : groups)
            if (g.target)
                g.target->size -= min(g.target->size, damage(g, *g.target) / g.target->hp);
    }
    cout << max(count(true), count(false)) << endl;
    return 0;
}
