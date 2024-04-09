#include <BLE.h>
#include <mbed.h>

#include <iostream>

#include "alert_notification_service.h"
#include "gatt_server.h"
#include "immediate_alert_service.h"
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
    CSecureGap secure_gap(ble_instance, event_queue, "MTC-BLE", LED1);
	// 4. Instantiate a CImmediateAlertService object and a CAlertNotificationService object
    CImmediateAlertService immediateAlertService(LED3);
    CAlertNotificationService alertNotificationService(BUTTON1);
	// 5. instantiate CGattServer object
    CGattServer gattServer;
	// 6. Add service objects to CGattServer
    gattServer.addService(immediateAlertService);
    gattServer.addService(alertNotificationService);
	// 7. Set onBLEInitComplete callback of Gap to CGattServer::startServer function
	//    of the instantiated object.
    secure_gap.setOnBLEInitCompleteCallback(mbed::callback(&gattServer, &CGattServer::startServer));
	// 8. Set onConnected callback of Gap to CGattServer::onConnected function
	//    of the instantiated object.
    secure_gap.setOnConnectedCallback(mbed::callback(&gattServer, &CGattServer::onConnected));
	// 9. Set onDisconnected callback of Gap to CGattServer::onDisconnected function
	//    of the instantiated object.
    secure_gap.setOnDisconnectedCallback(mbed::callback(&gattServer, &CGattServer::onDisconnected));
	// 10. Call CSecureGap::run member function to start the application
    secure_gap.run();
	return 0;
}