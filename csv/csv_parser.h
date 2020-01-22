#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "make_tuple.h"

template <typename Container>
void split(const std::string& str, Container& cont) {
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ',')) {
        cont.push_back(token);
    }
}

template <typename ... Args>
class CSVParser {
private:
    const std::string fname;
public:
    CSVParser(std::string f):
        fname(f)
    {}

    class iterator {
    private:
        std::ifstream ifs;
        size_t index;
        std::tuple<Args...> tuple;
    public:
        iterator(const std::string f, size_t ind):
            index(ind)
        {
            ifs.open(f);
            if (!ifs) {
                throw std::runtime_error("Unable to open file: " + f);
            }

            int row = -1;
            std::string str;
            while (std::getline(ifs, str)) {
                row++;
                if (row == index) {
                    std::vector<std::string> items;
                    split(str, items);
                    make_tuple(tuple, items);
                    break;
                 }
            }
            if (row == -1) {
                index = -1;
            }
        }

        iterator &operator++() {
            index++;
            std::string str;
            std::vector<std::string> items;
            if (std::getline(ifs, str)) {
                split(str, items);
                make_tuple<Args...>(tuple, items);
            } else {
                index = -1;
                ifs.close();
            }

            return *this;
        }

        std::tuple<Args...> operator*() const {
            return tuple;
        }

        std::tuple<Args...>* operator->() const {
            return &tuple;
        }

        friend bool operator==(const iterator & first, const iterator& second) {
            return (first.index == second.index);
        }

        friend bool operator!=(const iterator &first, const iterator &second) {
            return !(first == second);
        }
    };

    iterator begin() const {
        return iterator(fname, 0);
    }

    iterator end() const {
        return iterator(fname, -1);
    }
};
