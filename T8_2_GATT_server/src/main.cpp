#include <BLE.h>
#include <mbed.h>

#include <iostream>

#include "example_gatt_service.h"
#include "gap.h"
#include "gatt_server.h"
#include "nrf52832_app_protect.h"

int main() {
	/////////////////////////////////////////////////////////
	// the following must always present in main files
	nrf52_disable_approtect();
	///////////////////////////////////////////////////////////
	/*---------------------------------------------------------*/

	// TODO:: Implement this functions

	std::cout << "Starting GattServer application" << std::endl;
	

	// 1. Create EventQueue object for the application
    events::EventQueue queue;
	// 2. Get a reference to system's BLE instance
    BLE &ble = BLE::Instance();
	// 3. Instantiate CGap object with the required parameters (use the provided global uuids, and
	// characteristics descriptions)
    CGap gap(ble, queue, "BLEButton", LED1);
	// 4. Instantiate CExampleGattService object
    CExampleGattService exampleGattService(queue, LED2);
	// 5. instantiate CGattServer object
    CGattServer gattServer;
	// 6. Add CExampleGattService object to CGattServer
    gattServer.addService(exampleGattService);
	// 7. Set onBLEInitComplete callback of Gap to CGattServer::startServer function
	//    of the instantiated object.
    gap.setOnBLEInitCompleteCallback(mbed::callback(&gattServer, &CGattServer::startServer));
	// 8. Call CGap::run member function to start the application
    gap.run();
	return 0;
}