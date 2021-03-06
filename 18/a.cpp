#include "../commons.h"
#include "../board.h"
#include "../simulation.h"

using position = board<char>::position;

int main() {

    auto b = read_char_board();

    execute(10, [&] {
        b.transform('.', [&] (position p) { return p.count_neighbours('|') > 2 ? '|' : '.'; },
                    '|', [&] (position p) { return p.count_neighbours('#') > 2 ? '#' : '|'; },
                    '#', [&] (position p) {
                        return (p.count_neighbours('#') > 0 && p.count_neighbours('|') > 0) ? '#' : '.';
                     });
    });

    cout << b.count('|') * b.count('#') << endl;

    return 0;
}
