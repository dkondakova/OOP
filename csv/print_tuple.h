#pragma once

#include <iostream>

template<typename Tuple>
constexpr auto pop_front(Tuple tuple) {
    return std::apply([](auto, auto... rest) { return std::make_tuple(rest...); }, tuple);
}

void print_tuple(std::ostream& strm, std::tuple<> const&, bool isFirst = true) {
    strm << (isFirst ? '(' : ')');
}

template<typename Tuple>
void print_tuple(std::ostream& strm, Tuple const& t, bool isFirst = true) {
    strm << ( isFirst ? "(" : ", " );
    strm << std::get<0>(t);
    print_tuple(strm, pop_front(t), false);
}

template<typename... Types>
std::ostream& operator<<(std::ostream& strm, std::tuple<Types...> const& t) {
   print_tuple(strm, t);
   return strm;
 }
