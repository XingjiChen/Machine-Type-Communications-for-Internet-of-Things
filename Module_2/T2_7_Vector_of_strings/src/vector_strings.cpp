#include "vector_strings.hpp"

#include <iostream>
#include <vector>
#include <string>

void Adder(std::vector<std::string>& names) {
    std::string name;
    std::cout << "Enter a name:\n";
    std::getline(std::cin, name);
    names.push_back(name);
    std::cout << "Number of names in the vector:\n" << names.size() << "\n";
}

void Remover(std::vector<std::string>& names) {
    if (!names.empty()) {
        std::cout << "Removing the last element:\n" << names.back() << "\n";
        names.pop_back();
    }
}

void Printer(std::vector<std::string>& names) {
    for (const std::string& name : names) {
        std::cout << name << "\n";
    }
}

void CMDReader() {
    std::vector<std::string> names;
    std::string command;

    std::cout << "Commands: ADD, PRINT, REMOVE, QUIT\n";

    while (true) {
        std::cout << "Enter a command:\n";
        std::getline(std::cin, command);

        if (command == "ADD") {
            Adder(names);
        } else if (command == "REMOVE") {
            Remover(names);
        } else if (command == "PRINT") {
            Printer(names);
        } else if (command == "QUIT") {
            break;
        }
    }
}
