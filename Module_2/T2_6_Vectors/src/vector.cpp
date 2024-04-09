#include "vector.hpp"
#include <vector>
#include <numeric>  // For std::accumulate

// GetMin
int GetMin(std::vector<int> v) {
    if (v.empty()) return 0; // Or throw an exception

    int min_val = v[0];
    for (int num : v) {
        if (num < min_val) {
            min_val = num;
        }
    }
    return min_val;
}

// GetMax
int GetMax(std::vector<int> v) {
    if (v.empty()) return 0; // Or throw an exception

    int max_val = v[0];
    for (int num : v) {
        if (num > max_val) {
            max_val = num;
        }
    }
    return max_val;
}

// GetAvg
double GetAvg(std::vector<int> v) {
    if (v.empty()) return 0.0; // Or throw an exception

    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    return sum / v.size();
}
