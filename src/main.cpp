#include <iostream>
#include "config_reader.hpp"


int main(int argc, char *argv[]) {
    
    ConfigReader::readConfig("/home/sielu/Projects/CPP/sielu_formatter/.dom_format");

    for (auto &it : ConfigReader::getConfiguration()) {
        std::cout << it.second << std::endl;
    }
}