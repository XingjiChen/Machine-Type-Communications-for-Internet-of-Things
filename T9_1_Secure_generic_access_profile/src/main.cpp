#include <BLE.h>
#include <mbed.h>

#include <iostream>

#include "example_gatt_service.h"
#include "gatt_server.h"
#include "nrf52832_app_protect.h"
#include "secure_gap.h"

int main() {
	/////////////////////////////////////////////////////////
	// the following must always present in main files
	nrf52_disable_approtect();
	///////////////////////////////////////////////////////////
	/*---------------------------------------------------------*/

	// TODO:: Implement this functions

	std::cout << "Starting GattServer application" << std::endl;
	

	// 1. Create EventQueue object for the application
	events::EventQueue event_queue;
    // 2. Get a reference to system's BLE instance
	BLE &ble_instance = BLE::Instance();
    // 3. Instantiate CSecureGap object with the required parameters
	CSecureGap secure_gap(ble_instance, event_queue, "SecureGattServer", LED1);
    // 4. Instantiate CExampleGattService object (use the provided global uuids, and characteristics
	// descriptions)
	CExampleGattService example_gatt_service(event_queue, LED2);    
    // 5. instantiate CGattServer object
	CGattServer gattServer;
    // 6. Add CExampleGattService object to CGattServer
	gattServer.addService(example_gatt_service);
    // 7. Set onBLEInitComplete callback of Gap to CGattServer::startServer function
	//    of the instantiated object.
	secure_gap.setOnBLEInitCompleteCallback(mbed::callback(&gattServer, &CGattServer::startServer));
    // 8. Call CSecureGap::run member function to start the application
	secure_gap.run();
    
    return 0;
}