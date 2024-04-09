#include <mbed.h>
#include <BLE.h>
#include "gap_button.h"
#include "nrf52832_app_protect.h"

int main() {
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    nrf52_disable_approtect();
    ///////////////////////////////////////////////////////////
    /*---------------------------------------------------------*/

    // 1. Create EventQueue object for the application
    events::EventQueue event_queue;
    // 2. Get a reference to system's BLE instance 
    BLE &ble_interface = BLE::Instance();
    // 3. Instantiate CGAPButton object with the required parameters
    CGAPButton gapButton(ble_interface, event_queue, "BLEButton", BUTTON1, LED1);
    // 4. Call CGapButton::run member function to start the application  
    gapButton.run();
    
    return 0;
}