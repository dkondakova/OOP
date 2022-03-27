#include <iostream>
#include <string>

#include "csv_parser.h"
#include "print_tuple.h"

int main() {
    CSVParser<float, std::string> parser("text.csv");
    for (auto rs : parser){
        std::cout << rs << std::endl;
    }
    return 0;
}
