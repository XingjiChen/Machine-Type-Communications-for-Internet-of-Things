/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include "nrf52832_app_protect.h"

int function1(int a, int b) {
    return a + b + 1;
}

int function2(int a, int b) {
    return a * b + 1;
}

class MyClass {
public:
    int function1(int a, int b) {
        return a + b;
    }

    int function2(int a, int b) {
        return a * b;
    }
};

int main()
{
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    nrf52_disable_approtect();
    ///////////////////////////////////////////////////////////
    /*---------------------------------------------------------*/
    // Start your implementation below
    
    MyClass mObj;
    Callback<int(int, int)> cb;
    // declare an instance of Callback.
    // the variable name is cb.
    
    // assign cb to global function1
    cb = function1;
    std::cout << "callback(1, 2) with global function1 returns "
              << cb(1,2)
              << std::endl;

    // assign cb to global function2
    cb = function2;
    std::cout << "callback(1, 2) with global function2 returns "
              << cb(1, 2)
              << std::endl;

    // assign cb to MyClass::function1
    cb = callback(&mObj, &MyClass::function1);
    std::cout << "callback(1, 2) with MyClass::function1 returns "
              << cb(1, 2)
              << std::endl;

    // assign cb to MyClass::function2
    cb = callback(&mObj, &MyClass::function2);
    std::cout << "callback(1, 2) with MyClass::function2 returns "
              << cb(1, 2)
              << std::endl;

    while (true) {
        ThisThread::sleep_for(1s);
    }
    
    return 1;
}