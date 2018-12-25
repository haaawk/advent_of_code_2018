#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <string>

class find_and_union {
    mutable std::vector<int> _parent;
    void range_check(int x) const {
        if (x < 0) {
            throw std::out_of_range(std::to_string(x) + " too low. Minimum is 0"s);
        }
        if (x >= _parent.size()) {
            throw std::out_of_range(std::to_string(x) + " too high. Maximum is "s + std::to_string(_parent.size() - 1));
        }
    }
public:
    find_and_union(int size) : _parent(size, -1) {
        if (size < 1) {
            throw std::invalid_argument(std::to_string(size) + " is not positive"s);
        }
    }
    int find(int x) const {
        range_check(x);
        int p = x;
        while (_parent[p] > -1) {
            p = _parent[p];
        }
        while (_parent[x] > -1) {
            x = std::exchange(_parent[x], p);
        }
        return x;
    }
    int merge(int x, int y) {
        range_check(x);
        range_check(y);
        x = find(x);
        y = find(y);
        if (x == y) return -_parent[x];
        if (_parent[x] > _parent[y]) {
            swap(x, y);
        }
        _parent[x] += _parent[y];
        _parent[y] = x;
        return -_parent[x];
    }
    int size(int x) const {
        range_check(x);
        return -_parent[find(x)];
    }
    int count() const {
        return std::count_if(std::begin(_parent), std::end(_parent), [] (int x) { return x < 0; });
    }
};
