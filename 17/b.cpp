#include "../commons.h"

struct h_line {
    int x;
    int a;
    int b;
};

struct v_line {
    int x;
    int a;
    int b;
};

using lines_type = variant<h_line, v_line>;

void flow(vector<vector<char>>& B, int x, int y, int max_x, int max_y) {
    while (x < max_x && B[x][y] == '.') {
        B[x][y] = '|';
        ++x;
    }

    if (x < max_x && (B[x][y] == '#' || B[x][y] == '~')) {
        while (true) {
            int r = y + 1;
            while (r < max_y && B[x][r] != '.' && B[x - 1][r] == '.') ++r;
            int l = y - 1;
            while (l >= 0 && B[x][l] != '.' && B[x - 1][l] == '.') --l;

            if ((B[x][l] == '.') || (B[x][r] == '.')) {
                FOR(i, l + 1, r) B[x - 1][i] = '|';
                bool finish = true;
                if (B[x][l] == '.') {
                    B[x - 1][l] = '|';
                    flow(B, x, l, max_x, max_y);
                    finish &= B[x][l] != '~';
                }
                if (B[x][r] == '.') {
                    B[x - 1][r] = '|';
                    flow(B, x, r, max_x, max_y);
                    finish &= B[x][r] != '~';
                }
                if (finish)
                    break;
                --x;
            } else {
                FOR(i, l + 1, r) B[x - 1][i] = '~';
                while (l >= 0 && B[x - 1][l] == '|') { B[x - 1][l] = '~'; --l; }
                while (l >= 0 && B[x][l] != '.' && B[x - 1][l] == '.') --l;
                while (r < max_y && B[x - 1][r] == '|') { B[x - 1][r] = '~'; ++r; }
                while (r < max_y && B[x][r] != '.' && B[x - 1][r] == '.') ++r;
                if ((B[x][l] == '.') || (B[x][r] == '.')) {
                    FOR(i, l + 1, r) B[x - 1][i] = '|';
                    if (B[x][l] == '.') {
                        //B[x - 1][l] = '|';
                        flow(B, x, l + 1, max_x, max_y);
                    }
                    if (B[x][r] == '.') {
                        //B[x - 1][r] = '|';
                        flow(B, x, r - 1, max_x, max_y);
                    }
                    break;
                }
                FOR(i, l + 1, r) B[x - 1][i] = '~';
                --x;
            }
        }
    }
}

int main() {

    auto lines = read_lines<lines_type>("x=(\\d+), y=(\\d+)..(\\d+)",
                            [] (auto& s) { return v_line{stoi(s[1]), stoi(s[2]), stoi(s[3])}; },
                            "y=(\\d+), x=(\\d+)..(\\d+)",
                            [] (auto& s) { return h_line{stoi(s[1]), stoi(s[2]), stoi(s[3])}; });

    vector<h_line> H;
    vector<v_line> V;

    int min_x = 1000000;
    int max_x = 0;
    int min_y = 1000000;
    int max_y = 0;
    for (auto& line : lines) {
        if (line.index() == 0) {
            H.push_back(get<h_line>(line));
            max_y = max(max_y, H.back().b);
            min_y = min(min_y, H.back().a);
            max_x = max(max_x, H.back().x);
            min_x = min(min_x, H.back().x);
        } else {
            V.push_back(get<v_line>(line));
            max_y = max(max_y, V.back().x);
            min_y = min(min_y, V.back().x);
            max_x = max(max_x, V.back().b);
            min_x = min(min_x, V.back().a);
        }
    }

    max_x++;
    max_y += 2;

    vector<vector<char>> B(max_x, vector<char>(max_y, '.'));
    for (auto& h : H) FOR(i, h.a, h.b + 1) B[h.x][i] = '#';
    for (auto& v : V) FOR(i, v.a, v.b + 1) B[i][v.x] = '#';


    flow(B, 1, 500, max_x, max_y);

    int res = 0;
    FOR(i, min_x, max_x) FOR(j, 0, max_y) if (B[i][j] == '~') ++res;
    cout << res << endl;

    return 0;
}
