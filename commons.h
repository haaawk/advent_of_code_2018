#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<functional>
#include<algorithm>
#include<numeric>
#include<regex>
#include<variant>
#include<cassert>
#include<list>
#include<queue>
#include <iterator>

using namespace std;

using Num = int64_t;
using Vec = vector<Num>;
using Set = set<Num>;
template<typename T> using Map = map<Num, T>;
template<typename T> using Grid = vector<vector<T>>;

#define ALL(container) begin(container), end(container)
#define CHECK(name, condition) [&](auto& name) { return (condition); }
#define CONVERT(name, expression) [&] (auto& name) { return expression; }
#define RUN(name, statement) [&] (auto& name) { (statement); }
#define FIND(container, name, condition) find_if(ALL(container), CHECK(name, condition))
#define CONTAINS(container, name, condition) (FIND(container, name, condition) != end(container))
#define COUNT(container, name, condition) count_if(ALL(container), CHECK(name, condition))
#define VGET(var, field) visit([] (auto&& long_unique_name) { return long_unique_name.field; }, var)
#define FOR(var, start, end) for (Num var = (start), finish = (end); var < finish; ++var)
#define FORA(var, container) FOR(var, 0, container.size())

vector<string> read_lines() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    return lines;
}

template<typename T, typename Parser>
vector<T> read_lines(Parser&& parser) {
    vector<T> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(parser(line));
    }
    return lines;
}

template<typename T, typename Parser>
T parse_line(const string& line, const string& line_pattern, Parser&& parser) {
    string pattern = "^" + line_pattern + "$";
    regex regex(pattern);
    smatch m;
    if (!regex_match(line, m, regex)) {
        cerr << "Line [" << line << "] does not match any pattern." << endl;
        exit(-1);
    }
    return parser(m);
}

template<typename T, typename Parser, typename... Args>
T parse_line(const string& line, const string& line_pattern, Parser&& parser, Args... args) {
    string pattern = "^" + line_pattern + "$";
    try {
        regex regex(pattern);
        smatch m;
        if (!regex_match(line, m, regex)) {
            return parse_line<T>(line, std::forward<Args>(args)...);
        } else {
            return parser(m);
        }
    } catch (...) {
        cerr << "Error for pattern " << pattern << " and line " << line << endl;
        throw;
    }
}

template<typename T, typename Parser, typename... Args>
vector<T> read_lines(const string& pattern, Parser&& parser, Args... args) {
    return read_lines<T>([args..., &pattern, parser = std::forward<Parser>(parser)] (const string& line) mutable {
        return parse_line<T>(line, pattern, std::forward<Parser>(parser), std::forward<Args>(args)...);
    });
}

template<typename T, typename Parser>
vector<T> read_lines(string line_pattern, Parser&& parser) {
    return read_lines<T>([line_pattern = std::move(line_pattern), parser = std::forward<Parser>(parser)] (string& line) {
        string pattern = "^" + line_pattern + "$";
        regex regex(pattern);
        smatch m;
        if (!regex_match(line, m, regex)) {
            cerr << "Line [" << line << "] does not match pattern [" << pattern << "]" << endl;
            exit(-1);
        }
        return parser(m);
    });
}

Vec read_nums() {
    Vec nums;
    Num num;
    while (cin >> num) {
        nums.push_back(num);
    }
    return nums;
}

Vec read_nums_with_len() {
    Num len;
    cin >> len;
    Vec nums(len);
    for (Num i = 0; i < len; ++i) {
        cin >> nums[i];
    }
    return nums;
}

Vec read_lines_signed_nums() {
    return read_lines<Num>([] (string& line) {
        stringstream line_stream(line);
        char sign;
        line_stream >> sign;
        Num multiplier = sign == '-' ? -1 : 1;
        Num num;
        line_stream >> num;
        return multiplier * num;
    });
}

template<typename T>
Grid<T> read_grid() {
    return read_lines<vector<T>>([] (string& line) {
        stringstream ss(line);
        vector<T> row;
        T elem;
        while (ss >> elem) {
            row.push_back(elem);
        }
        return row;
    });
}

template<typename T>
void print(const vector<T>& v) {
    for (const T& e : v) {
        cout << e << " ";
    }
    cout << endl;
}

template<typename T>
void print(Grid<T>& g) {
    for (vector<T>& r : g) {
        print(r);
    }
}
