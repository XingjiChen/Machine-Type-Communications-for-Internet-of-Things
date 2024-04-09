/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 In this example, we are going to create two tasks with the same priority
LED3 will be accessed by both of the threads, and it will be guarded by a mutex.
When a Task sets the state of LED3, it will remain in that state at least for 1
seconds

Task 1: It will have Normal Priority
    It will get the state of Button 1, and turn on LED1 when Button 1 is pressed
and turn it off when Button 1 is released. It will try to set the state of LED 3
according to Button 1 state

Task 2: It will have Normal Priority
    It will turn on LED2 when Button 2 is pressed, and turn it off when Button 2
is released. It will also try to set the state of LED 3 according to Button 2
state

Expected behavior: The tasks will be blocked when the other has an access right
to LED 3

*/

#include "mbed.h"
#include <iostream>
#include "nrf52832_app_protect.h"

// the following code is just a placeholder. You may remove it if you find it fit.
//---------------BEGIN PLACE HOLDER-------------------------/
// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
//---------------END PLACE HOLDER-------------------------/


// Declare LED 3 object used by both of the threads
DigitalOut led(LED3);
// Declare the mutex object used by both of the threads
Mutex led3_mutex;

// You can use the following function from task functions 
// to change the LED3 state

/**
 * @brief Set the state of led3
 * 
 * @param turnOn The LED state; recommended to use true value to indicate on state
 * @param taskName The name of the task calling this function
 */
void set_led3(bool turnOn, const char* taskName) {
    led3_mutex.lock(); // get the Mutex
    std::cout << taskName
              << " trying to get LED3 lock to set its state to " << turnOn
              << std::endl;
    led = turnOn;
    std::cout << taskName
              << " set the LED 3 state for 1s" 
              << std::endl;
    ThisThread::sleep_for(1s); // keep for 1s
    led3_mutex.unlock(); // release the Mutex
}

void task1_proc() {
    // create a DigitalOut object in the Task stack memory
    DigitalOut led(LED1);
    // create a DigitalIn object in the Task stack memory
    DigitalIn button1(BUTTON1);
    // turn off the LED
    led = 1;

    bool lastState = button1;
    while (true) {
        bool currentState = button1;
        if(currentState != lastState){
            led = button1;
            set_led3(button1, "Task1");
        }
        lastState = currentState; 
        ThisThread::sleep_for(BLINKING_RATE);
        //---------------END PLACE HOLDER-------------------------/
        
    }
}

void task2_proc() {
    // create a DigitalOut object in the Task stack memory
    DigitalOut led(LED2);
    // create a DigitalIn object in the Task stack memory
    DigitalIn button2(BUTTON2);
    // Turn off the LED
    led = 1;

    bool lastState = button2;
    while (true) {
        bool currentState = button2;
        if(currentState != lastState){
            led = button2;
            set_led3(button2, "Task2");
        }
        lastState = currentState; 
        // the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        ThisThread::sleep_for(BLINKING_RATE);
        //---------------END PLACE HOLDER-------------------------/
        
    }
}

int main()
{
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    nrf52_disable_approtect();
    ///////////////////////////////////////////////////////////
    /*---------------------------------------------------------*/
    // Start your implementation below
    // 1. create two threads with different priorities. 
    // the threads are created in suspended state
    Thread thread1;
    Thread thread2;

    // 2. start the threads, and assign their procedures (functions)
    thread1.start(task1_proc);
    thread2.start(task2_proc);
    
    // 3. wait for threads to terminate (if they ever terminate)
    thread1.set_priority(osPriorityNormal);
    thread2.set_priority(osPriorityNormal);

    // the following code is just a placeholder. You may remove it if you find it fit.
    //---------------BEGIN PLACE HOLDER-------------------------/
    while (true) {
        ThisThread::sleep_for(BLINKING_RATE);
    }
    //---------------END PLACE HOLDER-------------------------/
    
}