#include "list.hpp"

#include <iostream>

// Implement the functions here

std::istream& GetLines(std::istream& is, std::list<std::string>& list) {
    list.clear(); // Ensure the list is empty before reading lines
    std::string line;
    while (std::getline(is, line)) {
        list.push_back(line);
    }
    return is;
}


void Print(const std::list<std::string>& list) {
    for (const auto& line : list) {
        std::cout << line << "\n";
    }
}


void SortAndUnique(std::list<std::string>& list) {
    list.sort();   // Sort the list alphabetically
    list.unique(); // Remove duplicate elements
}
