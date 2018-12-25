#pragma once

#include <iterator>
#include <type_traits>

template <typename Container, typename Func>
void for_each_pair(Container& c, Func&& fn) {
    using element_reference = typename Container::reference;
    static_assert(std::is_invocable_v<Func, int, int, element_reference, element_reference>
                  || std::is_invocable_v<Func, element_reference, element_reference>
                  || std::is_invocable_v<Func, int, int>,
                  "Wrong parameter types in function passed as argument");
    auto it1 = std::begin(c);
    for(int i = 0, size = c.size(); i < size; ++i, it1 = std::next(it1)) {
        auto it2 = std::next(it1);
        for (int j = i + 1; j < size; ++j, it2 = std::next(it2)) {
            if constexpr (std::is_invocable_v<Func, int, int, element_reference, element_reference>) {
                if constexpr (std::is_same_v<std::invoke_result_t<Func, int, int, element_reference, element_reference>, bool>) {
                    if (fn(i, j, *it1, *it2)) return;
                } else {
                    fn(i, j, *it1, *it2);
                }
            } else if constexpr (std::is_invocable_v<Func, element_reference, element_reference>) {
                if constexpr (std::is_same_v<std::invoke_result_t<Func, element_reference, element_reference>, bool>) {
                    if (fn(*it1, *it2)) return;
                } else {
                    fn(*it1, *it2);
                }
            } else if constexpr (std::is_invocable_v<Func, int, int>) {
                if constexpr (std::is_same_v<std::invoke_result_t<Func, int, int>, bool>) {
                    if (fn(i, j)) return;
                } else {
                    fn(i, j);
                }
            }
        }
    }
}
