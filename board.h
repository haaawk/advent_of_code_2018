#include <string>
#include <cassert>
#include <iostream>
#include <type_traits>

using std::vector;
using std::string;

template <typename T>
class board {
    template <typename U>
    friend bool operator<(const board<U>& a, const board<U>& b);
public:
    class position {
        friend class board;
        board* _b;
        int _x;
        int _y;
        position(board* b, int x, int y) : _b(b), _x(x), _y(y) {}
    public:
        void set(T val) { _b->_cells[_x][_y] = val; }
        T& get() { return _b->_cells[_x][_y]; }
        const T& get() const { return _b->_cells[_x][_y]; }

        template <typename Func>
        void for_each_neighbour(Func&& fn) {
            auto call = [&] (int x, int y) {
                if constexpr (std::is_invocable_v<Func, T&, position>) {
                    fn(_b->_cells[x][y], position(_b, x, y));
                } else if constexpr (std::is_invocable_v<Func, T&>) {
                    fn(_b->_cells[x][y]);
                } else if constexpr (std::is_invocable_v<Func, position>) {
                    fn(position(_b, x, y));
                }
            };
            bool not_left_edge = _y > 0;
            bool not_right_edge = _y + 1 < _b->_width;
            if (_x > 0) {
                if (not_left_edge) call(_x - 1, _y - 1);
                call(_x - 1, _y);
                if (not_right_edge) call(_x - 1, _y + 1);
            }
            if (not_left_edge) call(_x, _y - 1);
            if (not_right_edge) call(_x, _y + 1);
            if (_x + 1 < _b->_height) {
                if (not_left_edge) call(_x + 1, _y - 1);
                call(_x + 1, _y);
                if (not_right_edge) call(_x + 1, _y + 1);
            }
        }

        template <typename Func>
        void for_each_direct_neighbour(Func&& fn) {
            auto call = [&] (int x, int y) {
                if constexpr (std::is_invocable_v<Func, T&, position>) {
                    fn(_b->_cells[x][y], position(_b, x, y));
                } else if constexpr (std::is_invocable_v<Func, T&>) {
                    fn(_b->_cells[x][y]);
                } else if constexpr (std::is_invocable_v<Func, position>) {
                    fn(position(_b, x, y));
                }
            };
            if (_x > 0) call(_x - 1, _y);
            if (_y > 0) call(_x, _y - 1);
            if (_y + 1 < _b->_width) call(_x, _y + 1);
            if (_x + 1 < _b->_height) call(_x + 1, _y);
        }

        int count_neighbours(const T& c) {
            int res = 0;
            for_each_neighbour([&] (const T& n) { res += n == c ? 1 : 0; });
            return res;
        }

        int count_direct_neighbours(const T& c) {
            int res = 0;
            for_each_direct_neighbour([&] (const T& n) { res += n == c ? 1 : 0; });
            return res;
        }

        template <typename Func>
        T transform(const T& c, Func&& fn) {
            if (get() == c) return fn(*this);
            throw std::runtime_error("No transformation found for " + get());
        }

        template <typename Func, typename... Args>
        T transform(const T& c, Func&& fn, Args... args) {
            if (get() == c) return fn(*this);
            return transform(args...);
        }
    };
private:
    int _height;
    int _width;
    vector<vector<T>> _cells;
public:
    board(vector<vector<T>>&& cells)
        : _height(cells.size()), _width(cells[0].size()), _cells(std::move(cells)) {}

    template <typename Func>
    void for_each(Func&& fn) {
        static_assert(std::is_invocable_v<Func, T&, position>
                      || std::is_invocable_v<Func, T&>
                      || std::is_invocable_v<Func, position>,
                      "Wrong parameter types in function passed to board::for_each");
        for (int x = 0; x < _height; ++x) {
            for (int y = 0; y < _width; ++y) {
                if constexpr (std::is_invocable_v<Func, T&, position>) {
                    static_assert(std::is_same_v<std::invoke_result_t<Func, T&, position>, void>
                                  || std::is_same_v<std::invoke_result_t<Func, T&, position>, bool>,
                                  "Wrong return type in function passed to board::for_each");
                    if constexpr (std::is_same_v<std::invoke_result_t<Func, T&, position>, bool>) {
                        if (fn(_cells[x][y], position(this, x, y))) return;
                    } else {
                        fn(_cells[x][y], position(this, x, y));
                    }
                } else if constexpr (std::is_invocable_v<Func, T&>) {
                    static_assert(std::is_same_v<std::invoke_result_t<Func, T&>, void>
                                  || std::is_same_v<std::invoke_result_t<Func, T&>, bool>,
                                  "Wrong return type in function passed to board::for_each");
                    if constexpr (std::is_same_v<std::invoke_result_t<Func, T&>, bool>) {
                        if (fn(_cells[x][y])) return;
                    } else {
                        fn(_cells[x][y]);
                    }
                } else if constexpr (std::is_invocable_v<Func, position>) {
                    static_assert(std::is_same_v<std::invoke_result_t<Func, position>, void>
                                  || std::is_same_v<std::invoke_result_t<Func, position>, bool>,
                                  "Wrong return type in function passed to board::for_each");
                    if constexpr (std::is_same_v<std::invoke_result_t<Func, position>, bool>) {
                        if (fn(position(this, x, y))) return;
                    } else {
                        fn(position(this, x, y));
                    }
                }
            }
        }
    }

    bool contains(const T& v) {
        bool res = false;
        for_each([&] (const T& c) {
            if (c == v) {
               res = true;
               return true;
            }
            return false;
        });
        return res;
    }

    std::optional<position> find_first(const T& v) {
        std::optional<position> res;
        for_each([&] (const T& c, position p) {
            if (c == v) {
                res = p;
                return true;
            }
        });
        return res;
    }

    std::optional<position> find_next(position p, const T& c) {
        for (int x = p._x; x < _height; ++x) {
            for (int y = p._y + 1; y < _width; ++y) {
                if (_cells[x][y] == c) return position(this, x, y);
            }
        }
        return {};
    }

    std::vector<position> find_all(const T& v) {
        std::vector<position> res;
        for_each([&] (const T& c, position p) { if (c == v) res.push_back(p); });
        return res;
    }

    int count(const T& v) {
        int res = 0;
        for_each([&] (const T& c) { res += v == c ? 1 : 0; });
        return res;
    }

    void replace(const T& from, const T& to) {
        for_each([&] (T& c) { c = (c == from) ? to : c; });
    }

    void print() {
        for (int x = 0; x < _height; ++x) {
            for (int y = 0; y < _width; ++y) {
                std::cout << _cells[x][y];
            }
            std::cout << std::endl;
        }
    }

    board empty_copy() {
        return {vector<vector<T>>(_height, vector<T>(_width))};
    }

    template <typename... Args>
    void transform(Args... args) {
        board res = empty_copy();
        for_each([&] (position p) mutable {
            res._cells[p._x][p._y] = p.transform(args...);
        });
        *this = std::move(res);
    }
};

template <typename T>
inline bool operator<(const board<T>& a, const board<T>& b) {
    assert(a._height == b._height && "Comparing two boards with different height");
    assert(a._width == b._width && "Comparing two boards with different width");
    return a._cells < b._cells;
}

template <typename T, typename Parser>
board<T> read_board(Parser&& p) {
    vector<vector<T>> lines;
    string line;
    while (std::getline(std::cin, line)) {
        lines.push_back(p(line));
    }
    assert(lines.size() > 0 && "Board of height 0");
    assert(lines[0].size() > 0 && "Board of width 0");
    // All rows have to have the same lenght
    for (auto& line : lines) {
        assert(line.size() == lines[0].size() && "Board with rows of different length");
    }
    return {std::move(lines)};
}

board<char> read_char_board() {
    return read_board<char>([] (string& line) { return vector<char>(begin(line), end(line)); });
}
