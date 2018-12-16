#include "../commons.h"

int id_count = 0;

enum class unit_type {
    ELF, GOBLIN
};

using position = pair<int, int>;

struct unit {
    int id;
    position p;
    unit_type type;
    int hp;
    int power;
    unit(position p, unit_type type) : id(id_count++), p(p), type(type), hp(200), power(3) {}
};

struct step {
    position first_step;
    position target;
    int d;
};

struct queue_entry {
    position current;
    position first_step;
};

int main() {
    int elf_power = 4;

    auto lines = read_lines();
    vector<unit> units;
    vector<vector<int>> ids(lines.size(), vector<int>(lines[0].size(), -1));

    const int max_d = lines.size() * lines.size();

    auto set_lines = [&] (position p, char c) { lines[p.first][p.second] = c; };
    auto set_ids = [&] (position p, int id) { ids[p.first][p.second] = id; };

    auto is_unit = [&] (position p) { return ids[p.first][p.second] != -1; };

    auto unit_for = [&] (position p) -> unit& { return units[ids[p.first][p.second]]; };

    auto for_adjacent_positions_in_order = [&] (position p, auto&& fn) {
        if (p.first > 0 && fn({p.first - 1, p.second})) return true;
        if (p.second > 0 && fn({p.first, p.second - 1})) return true;
        if (p.second + 1 < lines[0].size() && fn({p.first, p.second + 1})) return true;
        if (p.first + 1 < lines.size() && fn({p.first + 1, p.second})) return true;
        return false;
    };

    auto for_each_position = [&] (auto&& fn) {
        FORA(ui, lines) FORA(uj, lines[0]) fn(position{ui, uj});
    };

    auto for_each_live_unit_in_reading_order = [&] (auto&& fn) {
        vector<unit*> turns;
        for_each_position([&] (position p) { if (is_unit(p)) turns.push_back(&unit_for(p)); });
        for (auto u : turns) if (u->hp > 0) fn(*u);
    };

    auto maybe_attack = [&] (unit& u) {
        int min_hp = 201;
        unit* target = nullptr;
        for_adjacent_positions_in_order(u.p, [&] (position p) {
            if (is_unit(p)) {
                unit& o = unit_for(p);
                if (o.type != u.type) {
                    if (o.hp < min_hp) {
                        min_hp = o.hp;
                        target = &o;
                    }
                }
            }
            return false;
        });
        if (!target) return false;
        target->hp -= u.type == unit_type::ELF ? elf_power : u.power;
        if (target->hp <= 0) {
            set_lines(target->p, '.');
            set_ids(target->p, -1);
        }
        return true;
    };

    auto maybe_move = [&] (unit& u) {
        vector<vector<int>> d(lines.size(), vector<int>(lines[0].size(), max_d));
        auto setd = [&] (position p, int val) { d[p.first][p.second] = val; };
        queue<queue_entry> q;
        setd(u.p, 0);
        for_adjacent_positions_in_order(u.p, [&] (position p) {
            if (lines[p.first][p.second] == '.') {
                setd(p, 1);
                q.push({p, p});
            }
            return false;
        });
        vector<step> moves;
        while (!q.empty()) {
            auto e = q.front();
            q.pop();
            int nd = d[e.current.first][e.current.second] + 1;
            for_adjacent_positions_in_order(e.current, [&] (position p) {
                if (lines[p.first][p.second] == '.') {
                    if (d[p.first][p.second] > nd) {
                        q.push({p, e.first_step});
                        setd(p, nd);
                    }
                } else if (is_unit(p) && unit_for(p).type != u.type) {
                    moves.push_back({e.first_step, e.current, nd - 1});
                }
                return false;
            });
        }
        sort(ALL(moves), [] (auto& a, auto& b) {
            return a.d < b.d || (a.d == b.d && a.target < b.target);
        });
        if (!moves.empty()) {
            set_ids(u.p, -1);
            set_lines(u.p, '.');
            u.p = moves[0].first_step;
            set_ids(u.p, u.id);
            set_lines(u.p, u.type == unit_type::ELF ? 'E' : 'G');
            return true;
        }
        return false;
    };

    auto battle_finished = [&] {
        auto count_live_units_for_type = [&] (unit_type t) {
            return count_if(ALL(units), [&] (unit& u) { return u.type == t && u.hp > 0; });
        };
        return count_live_units_for_type(unit_type::ELF) == 0 || count_live_units_for_type(unit_type::GOBLIN) == 0;
    };

    auto hp_sum_of_survivers = [&] {
        return accumulate(ALL(units), 0, [] (int s, unit& u) { return u.hp > 0 ? s + u.hp : s; });
    };

    for_each_position([&] (position p) {
        if (lines[p.first][p.second] == 'E' || lines[p.first][p.second] == 'G') {
            units.push_back({p, lines[p.first][p.second] == 'E' ? unit_type::ELF : unit_type::GOBLIN});
            set_ids(p, units.back().id);
        }
    });

    auto lines_backup = lines;
    auto ids_backup = ids;
    auto units_backup = units;
    while (true) {
        int round_no = 0;
        while (true) {
            for_each_live_unit_in_reading_order([&] (unit& u) {
                if (!maybe_attack(u) && maybe_move(u)) maybe_attack(u);
            });
            if (battle_finished()) {
                if (count_if(ALL(units), [&] (unit& u) { return u.type == unit_type::ELF && u.hp <= 0; }) == 0) {
                    cout << round_no * hp_sum_of_survivers() << endl;
                    return 0;
                }
                break;
            }
            ++round_no;
        }
        ++elf_power;
        lines = lines_backup;
        ids = ids_backup;
        units = units_backup;
    }

    return -1;
}
