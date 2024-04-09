#include "matrix.hpp"
#include <iostream>
#include <vector>

// ReadMatrix implementation
Matrix ReadMatrix(int n) {
    Matrix matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    return matrix;
}

// Rotate90Deg implementation
Matrix Rotate90Deg(const Matrix &m) {
    int n = m.size();
    Matrix matrix(n, std::vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[j][n - 1 - i] = m[i][j];
        }
    }
    return matrix;
}

// Print implementation
// Print implementation
void Print(const Matrix &m) {
    int n = m.size();
    std::cout << "Printing out a " << n << " x " << n << " matrix:" << std::endl;
    for(const auto& row:m){
        for(auto val:row){
            std::cout << val << " ";
        }
        std::cout<<std::endl;
    }
}
