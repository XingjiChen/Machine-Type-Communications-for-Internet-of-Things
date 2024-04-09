#include "geomvector.hpp"

int main() {
    GeomVector vecA(2,3,4), vecB(1,1,1), vecC(0.1,0,0);
    GeomVector vecD(0,0,0);

    vecD = vecB / 3;  // uses operator/
    bool aLarger = vecA > vecB; // uses operator>, should be true
    bool bSmaller = vecB < vecD; // uses operator<, should be false
    bool aEqual = vecA == vecB; // uses operator ==, should be false
    bool cNotEqual = vecB != vecC; // uses operator !=, should be true
    bool dEqual = (3 * vecD) == vecB; // uses operator ==, should be true

    // uses operator<<
    std::cout << "vecD: " << vecD << std::endl
            << "vecA > vecB: " << ((aLarger == 1) ? "true" : "false") << std::endl
            << "vecB < vecD: " << ((bSmaller == 1) ? "true" : "false") << std::endl
            << "vecA == vecB: " << ((aEqual == 1) ? "true" : "false") << std::endl
            << "vecB != vecC: " << ((cNotEqual == 1) ? "true" : "false") << std::endl
            << "(3 * vecD) == vecB: " << ((dEqual == 1) ? "true" : "false") << std::endl;
}