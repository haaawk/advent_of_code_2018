#pragma once

#include <cmath>
#include <array>
#include <string>

template <typename T, int D>
class point {
    std::array<T, D> _coordinates;
public:
    template <typename... Args>
    point(Args... args) {
        if (sizeof...(args) != D) {
            throw std::invalid_argument("Wrong number of arguments. Got "s + std::to_string(sizeof...(args)) + ", Expected "s + std::to_string(D));
        }
        _coordinates = { args... };
    }
    T distance(const point<T, D>& o) const {
        T result{};
        for (int i = 0; i < D; ++i) {
            result += std::abs(_coordinates[i] - o._coordinates[i]);
        }
        return result;
    }
};
