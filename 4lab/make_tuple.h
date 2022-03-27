#pragma once

#include <tuple>
#include <vector>
#include <sstream>

template <std::size_t idx, class... fields>
typename std::enable_if<idx >= std::tuple_size<std::tuple<fields...>>::value - 1>::type
read_elem(std::tuple<fields...>& tuple, const std::vector<std::string>& items) {
    std::stringstream ss(items[idx]);
    ss >> std::get<idx>(tuple);
}

template <std::size_t idx, typename... fields>
typename std::enable_if<idx < std::tuple_size<std::tuple<fields...>>::value - 1>::type
read_elem(std::tuple<fields...>& tuple, const std::vector<std::string>& items) {
    std::stringstream ss(items[idx]);
    ss >> std::get<idx>(tuple);
    read_elem<idx + 1>(tuple, items);
}

template <typename... fields>
void make_tuple(std::tuple<fields...>& tuple, std::vector<std::string>& items) {
    read_elem<0>(tuple, items);
}
