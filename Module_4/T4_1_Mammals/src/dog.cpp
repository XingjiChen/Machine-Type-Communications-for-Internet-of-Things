#include "dog.hpp"

// Dog 类的构造函数
Dog::Dog(std::string name, double weight) : Mammal(weight), name_(name) {}

// GetName 成员函数返回狗的名字
std::string Dog::GetName() {
    return name_;
}

// MakeSound 静态函数返回狗的叫声
std::string Dog::MakeSound() {
    return "Wuff!";
}

