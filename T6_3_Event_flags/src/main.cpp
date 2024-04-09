/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include "nrf52832_app_protect.h"

/*
 In this example, we are going to create two tasks with different priorities

Task 1: It will have Normal Priority
    It will get the Button state from task 2, and turn on LED1 when Button 1 is pressed and turn it off when Button 1
is released

Task 2: It will have AboveNormal Priority
    It will turn on LED2 when Button 1 is pressed, and turn it off when Button 1
is released. It will set EventFlag when button state changes

Expected behavior: Task 2 sets EventFlags, and Task 1 gets that info after it

*/

// the following is just a placeholder. You may remove it if you find it fit.
//---------------BEGIN PLACE HOLDER-------------------------/
// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
//---------------END PLACE HOLDER-------------------------/


// Useful bitmasks that can used for event flag monitoring
#define BUTTON_PRESSED_FLAG_MASK (1 << 0) // this is the Least Significant Bit
#define BUTTON_RELEASED_FLAG_MASK (1 << 1)  // this is the Least Significant Bit
#define BUTTON_STATE_FLAG_MASK  (BUTTON_PRESSED_FLAG_MASK | BUTTON_RELEASED_FLAG_MASK)

// Declare EventFlag object used by the tasks
EventFlags eventFlags;

void task1_proc() {
    // create a DigitalOut object in the Task stack memory
    DigitalOut led(LED1);
    // turn off the LED
    led = 1;
    while (true) {
        
        // the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        uint32_t flags = eventFlags.wait_any(BUTTON_STATE_FLAG_MASK);
        if (flags & BUTTON_PRESSED_FLAG_MASK) {
            led = 0; // Turn on LED1
        }
        if (flags & BUTTON_RELEASED_FLAG_MASK) {
            led = 1; // Turn off LED1
        }
        printf("LED state: %d\n", led.read());
        ThisThread::sleep_for(BLINKING_RATE);
        //---------------END PLACE HOLDER-------------------------/
        
    }
}

void task2_proc() {
    // create a DigitalOut object in the Task stack memory
    DigitalOut led(LED2);
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON1);
    bool lastState = button;
    // Turn off the LED
    led = 1;
    while (true) {
        
        // the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        bool currentState = button;
        if (currentState != lastState) { // Check if button state has changed
            if (currentState == 0) { // Button pressed
                eventFlags.set(BUTTON_PRESSED_FLAG_MASK);
            } else { // Button released
                eventFlags.set(BUTTON_RELEASED_FLAG_MASK);
            }
            lastState = currentState; // Update lastState
            printf("Button change: state: %d\n", currentState);
        }
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
    thread2.set_priority(osPriorityAboveNormal);

    // the following code is just a placeholder. You may remove it if you find it fit.
    //---------------BEGIN PLACE HOLDER-------------------------/
    DigitalOut led(LED1);
    while (true) {
        // led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
    //---------------END PLACE HOLDER-------------------------/
    
   return 1;
}