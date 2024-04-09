/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 In this example, we are going to create three tasks with the same priority
LED3 will be accessed by both of the threads, and it will be guarded by a mutex.
When a Task sets the state of LED3, it will remain in that state at least for 1
seconds

Task 1: It will have Normal Priority
    It will get the state of Button 1, and try to get one LED to show the Button
1 state

Task 2: It will have Normal Priority
    It will get the state of Button 2, and try to get one LED to show the Button
2 state

Task 3: It will have Normal Priority
    It will get the state of Button 3, and try to get one LED to show the Button
3 state

In total 2 LEDs will be available, and 3 tasks will race to get a LED.
The tasks will be blocked when two LEDs are already occupied. When one
thread gets a button it will keep it for 1s

Expected Behavior: One of the tasks will be blocked when two of them gets the
LEDs
 */

#include "mbed.h"
#include <iostream>
#include <sstream>
#include <list>


#include "nrf52832_app_protect.h"

// 
/**
 * @brief This is a led class, with identifier. You can use inheritance to
 * add new attributes to the base classes.
 * 
 * This class has "id" and "name" attributes.
 */
class AppLED: public DigitalOut{
private:
    // the id of the LED
    int id;
    // the name of the LED
    std::string name;
public:
    AppLED(PinName pin, int id) : DigitalOut(pin, 1), id(id){
        std::ostringstream oss;
        oss << "LED " << this->id;
        this->name = oss.str();
    }

    void set_id(int id){
        this->id = id;
    }

    int get_id(){
        return this->id;
    } 

    const std::string& str(){
        return this->name;
    }
};

/**
 * @brief This class the manager of the Application LEDs. 
 * 
 * It has the leds that can be used at a time, and provides 
 * a LED to the caller if one is available. 
 */
class AppLEDs{
private:
    // The application LEDs of AppLED type. -- all leds have id and name attributes
    std::list<AppLED> leds; 
    // declare a semaphore guard to the application LEDs
    Semaphore guard;
    static AppLED invalidLed;
public:
    // Default Constructor for our two LEDs
    /**
     * @brief Construct a new AppLEDs object
     * 
     * @note Since Semaphore is non-copyable, you must use initializer list to properly construct it!
     */
    //AppLEDs(){}

    /*BEGIN SOLUTION*/
    AppLEDs():guard(2){
        // Complete the constructor according to the task description
        leds.push_back(AppLED(LED1, 1));
        leds.push_back(AppLED(LED2, 2)); 
    }
    
    /**
     * @brief Acquires a LED from the application LEDs list if available. 
     * 
     * If no LED is available, blocks the caller task until a LED becomes available.
     * 
     * @param taskName The name of the caller task
     * @return A reference to the acquired led 
     */
    AppLED & acquire(const char* taskName){
        uint64_t ticks = Kernel::Clock::now().time_since_epoch().count();
        std::cout << taskName << " tries to acquire a LED" << std::endl;
        // try to acquire the semaphore
        //std::cout << "Before Acquire, Get the queue information1: " << leds.front().str() << std::endl;
        //std::cout << "Before Acquire, Get the queue information2: " << leds.back().str() << std::endl;
        if(guard.try_acquire()){
            //guard.acquire();
            // get the first led from the list, and assign it to local `led` variable
            // of AppLED reference type.
            AppLED& led = leds.front();
            std::cout << led.get_id() <<std::endl;
            std::cout << taskName << " acquired " 
            << led.str() <<" in " << Kernel::Clock::now().time_since_epoch().count() - ticks 
            << "ms" << std::endl;
            leds.pop_front(); // Remove the LED from the available list
            return led;
        }
        else{
            std::cout << taskName << " did not acquire a LED (no LED available)" << std::endl;
            AppLED invalidLed = AppLED(NC, -1);
            return invalidLed; // No LED was acquired
        }
    }
    /**
     * @brief Releases an acquired LED
     * 
     * @param led A reference to the LED that will be released
     * @param taskName The name of the task releasing the LED
     */
    void release(AppLED& led, const  char* taskName){
        if(!leds.empty() and leds.front().get_id() == led.get_id()){
            if(led.get_id() == 1){
                std::cout << taskName << " releases " << AppLED(LED2, 2).str() << std::endl;
                leds.push_back(AppLED(LED2, 2));
            }
            else{
                std::cout << taskName << " releases " << AppLED(LED1, 1).str() << std::endl;
                leds.push_back(AppLED(LED1, 1));
            }
            guard.release();
            return;
        }
        std::cout << taskName << " releases " << led.str() << std::endl;
        // put the LED to the list
        leds.push_back(led);
        // increase the semaphore count
        guard.release(); // Release the semaphore
        //std::cout << "After release, Get the queue information1: " << leds.front().str() << std::endl;
        //std::cout << "After release, Get the queue information2: " << leds.back().str() << std::endl;
    }
};

// this is the LEDs manager of the application
AppLEDs ledManager;

void task1_proc() {
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON1);
    bool lastState = button;
    while (true) {
        // complete the task function according to the instruction.
        // you can use "Task 1" as task name 
        bool currentState = button;
        if(currentState != lastState){
            AppLED& led = ledManager.acquire("Task 1");
            if(led.get_id() != -1){
                led.write(button);
                ThisThread::sleep_for(1s);
                ledManager.release(led, "Task 1");
            }
        }
        lastState = currentState;
        ThisThread::sleep_for(100ms);
    }
}

void task2_proc() {
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON2);
    bool lastState = button;
    while (true) {
        // complete the task function according to the instruction.
        // you can use "Task 2" as task name
        bool currentState = button;
        if(currentState != lastState){
            AppLED& led = ledManager.acquire("Task 2");
            if(led.get_id() != -1){
                led.write(button);
                ThisThread::sleep_for(1s);
                ledManager.release(led, "Task 2");
            }
        }
        lastState = currentState;
        ThisThread::sleep_for(100ms);
    }
}

void task3_proc() {
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON3);
    bool lastState = button;
    while (true) {
        // complete the task function according to the instruction.
        // you can use "Task 3" as task name
        bool currentState = button;
        if(currentState != lastState){
            //std::cout << "current state: " << button << " last state: " << lastState << std::endl;
            AppLED& led = ledManager.acquire("Task 3");
            if(led.get_id() != -1){
                led.write(button);
                ThisThread::sleep_for(1s);
                ledManager.release(led, "Task 3");
            }
        }
        lastState = currentState;
        ThisThread::sleep_for(100ms);
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

    // 1. create three threads with required priorities. 
    // the threads are created in suspended state
    Thread thread1;
    Thread thread2;
    Thread thread3;

    // 2. start the threads, and assign their procedures (functions)
    thread1.start(task1_proc);
    thread2.start(task2_proc);
    thread3.start(task3_proc);
    
    // 3. wait for threads to terminate (if they ever terminate)
    thread1.set_priority(osPriorityNormal);
    thread2.set_priority(osPriorityNormal);
    thread3.set_priority(osPriorityNormal);
    
    // the following code is just a placeholder. You may remove it if you find it fit.
    //---------------BEGIN PLACE HOLDER-------------------------/
    while (true) {
        ThisThread::sleep_for(1s);
    }
    //---------------END PLACE HOLDER-------------------------/
    
}