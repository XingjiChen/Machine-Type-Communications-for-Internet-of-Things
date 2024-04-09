#include <BLE.h>
#include <mbed.h>
#include <iostream>

#include "gap.h"
#include "gatt_service.h"
#include "nrf52832_app_protect.h"

/**
 * @brief Characteristics UUIDs generated by https://www.uuidgenerator.net/
 *
 */
const char* characteristics_uuids[] = {"6a7a0839-a67d-4fb9-ac5d-65f2843d5250",
									   "8cc6f2b4-a06e-4905-bfb7-0eb93889bfe6",
									   "02f4685a-a39e-481d-b932-1129012be897"};
/**
 * @brief Service UUID generated by https://www.uuidgenerator.net/
 *
 */
const char* service_uuid = "10ffbbdf-15eb-4a3c-9a12-3391bc95a127";
/**
 * @brief The characteristics user descriptions
 *
 */
const char* characteristic_descriptions[] = {"Characteristic 1", "Characteristic 2", "Characteristic 3"};

int main() {
	/////////////////////////////////////////////////////////
	// the following must always present in main files
	nrf52_disable_approtect();
	///////////////////////////////////////////////////////////
	/*---------------------------------------------------------*/

	// TODO:: Implement this functions

    std::cout << "Starting GattService application" << std::endl;
	

	// 1. Create EventQueue object for the application
    events::EventQueue queue;
	// 2. Get a reference to system's BLE instance
    BLE &ble = BLE::Instance();
	// 3. Instantiate CGap object with the required parameters (use the provided global uuids, and
	// characteristics descriptions)
    CGap gap(ble, queue, "BLEButton", LED1);
	// 4. Instantiate CGattService object
    CGattService gattService;
	// 5. Add 3 characteristics (with empty values) to the service using CGattService::addCharacteristic
	// function
    for (int i = 0; i < 3; ++i) {
        std::cout << "Added characteristics_uuid is: " << *(characteristics_uuids+i) << std::endl;
        gattService.addCharacteristic(characteristics_uuids[i], 
                                    GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NONE,
                                    characteristic_descriptions[i],
                                    nullptr, 0);
    }
	// 6. Create the service using CGattService::createService function
    gattService.createService(service_uuid);
	// 7. Set onBLEInitComplete callback of Gap to CGattService::registerService function
	//    of the instantiated object.
    gap.setOnBLEInitCompleteCallback(mbed::callback(&gattService, &CGattService::registerService));
	// 8. Call CGap::run member function to start the application
    gap.run();
	return 0;
}