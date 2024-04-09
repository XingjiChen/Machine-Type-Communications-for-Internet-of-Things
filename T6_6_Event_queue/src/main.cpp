/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "nrf52832_app_protect.h"
#include "mbed_events.h"

// the following is just a placeholder. You may remove it if you find it fit.
// Blinking rate in milliseconds
//---------------BEGIN PLACE HOLDER-------------------------/
#define BLINKING_RATE     500ms
//---------------END PLACE HOLDER-------------------------/


void eventHandler(int id){
    // complete the function definition
    printf("Event ID: %d\n", id);
}

// Declare EventQueue object 
EventQueue event_queue;
// Declare Event object
Event<void(int)> event(&event_queue, eventHandler);

/**
 * @brief The task procedure to post the events
 * 
 */
void task_proc(void) {

    // Events can be posted multiple times and enqueue gracefully until
    // the dispatch function is called.
    event.post(1);
    event.post(2);
    event.post(3);
}

int main()
{
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    nrf52_disable_approtect();
    ///////////////////////////////////////////////////////////
    /*---------------------------------------------------------*/
    // Start your implementation below
    // 1. create a thread with the specified priority. 
    // the threads are created in suspended state
    Thread thread(osPriorityNormal);

    // 2. Configure the event object period and delay
    // The event can be manually configured for special timing requirements
    // specified in milliseconds
    event.delay(100ms); // Set event delay
    event.period(200ms); // Set event period

    // 3. start the thread, and assign their procedures (functions)
    thread.start(callback(task_proc));

    // 4. Call the queue dispatch function
    // Posted events are dispatched in the context of the queue's
    // dispatch function
    event_queue.dispatch_for(1000ms);
    
    // 5. wait for thread to terminate (if it ever terminates)
    thread.join();

    // the following code is just a placeholder. You may remove it if you find it fit.
    //---------------BEGIN PLACE HOLDER-------------------------/
    //DigitalOut led(LED1);
    while (true) {
        //led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
    //---------------END PLACE HOLDER-------------------------/
    
    return 1;
}