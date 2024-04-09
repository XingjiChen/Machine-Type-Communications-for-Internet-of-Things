#include "vector_it.hpp"

#include <iostream>
#include <vector>

// Implement the functions here

std::vector<int> ReadVector() {
    std::vector<int> v;
    int num_input;
    while(1){
        std::cin >> num_input;
        if(std::cin.fail()){
            std::cin.clear();
            return v;
        }
        else {
            v.push_back(num_input);
        }
    }
    return v;
}

void PrintSum1(const std::vector<int>& v) {
    int sum;
    for(auto it = v.begin(); it != (v.end() -1); it++){
        //sum = 0;
        sum = *it + *(it+1);
        std::cout << sum << " ";
    }
    std::cout << std::endl;
}

void PrintSum2(const std::vector<int>& v) {
    int sum;
    auto front = v.begin();
    auto back = v.end()-1;
    while(front < back){
        //sum = 0;
        sum = *front + *back;
        std::cout << sum << " ";
        ++front;
        if (front <= back) {
            --back;
        }
    }
    std::cout << std::endl;
}
