#include "cat.hpp"

// Cat 类的构造函数
Cat::Cat(std::string name, double weight) : Mammal(weight), name_(name) {}

// GetName 成员函数返回猫的名字
std::string Cat::GetName() {
    return name_;
}

// MakeSound 静态函数返回猫的叫声
std::string Cat::MakeSound() {
    return "Meow";
}

