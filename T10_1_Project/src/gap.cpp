#include "gap.h"

#include <iostream>

#include "ble_utils.h"

// TODO: Copy your solution from Module 8.
// Note: onBLEInitCompleteHandler member is virtual now.
// Note: You can get human readable strings of ble_error_t type returns values
// using bleErrorToString function declared in ble_utils.h

void CGap::toggleLED() {
	// TODO:: Implement this functions
	_led = !_led;
}

void CGap::updateAdvertisementData() {
	// We do not need to update advertisement data
	std::cout << "Advertisement data updated!" << std::endl;
}
void CGap::onBLEInitCompleteHandler(BLE::InitializationCompleteCallbackContext *context) {
	// TODO:: Implement this functions
	// 1. check for the initialization errors using error member of context
	if (context->error) {
        std::cout << "BLE initialization failed." << std::endl;
        return;
    }
	// The BLE interface can be accessed now.
	std::cout << "BLE init completed" << std::endl;
	// 2. get and print the device address
	ble::own_address_type_t addrType;
	ble::address_t address;
	auto error = context->ble.gap().getAddress(addrType, address);
	std::cout << bleErrorToString(error, "GAP::getAddress()") << std::endl;
	if (error == BLE_ERROR_NONE){
        // print the own Bluetooth address using
		// printBluetoothAddress utility function defined in ble_utils.h
		// note that there are 3 overloads of that function.
		std::cout << bluetoothAddressToString(addrType, address) << std::endl;
    } else {
        std::cout << "Failed to get device address." << std::endl;
    }
	// 3. call _on_ble_init_callback member if it is not nullptr
	_on_ble_init_callback(_ble);
	// 4. start advertising
	startAdvertising();
}

void CGap::scheduleBLEEventsToProcess(BLE::OnEventsToProcessCallbackContext *context) {
	// TODO:: Implement this functions
	_event_queue.call(callback(&_ble, &BLE::processEvents));
}


// TODO:: Implement this constructor
CGap::CGap(ble::BLE &ble,
		   EventQueue &event_queue,
		   const std::string &device_name,
		   PinName led_pin,
		   const mbed::Callback<void(ble::BLE &)> &on_ble_init_callback,
           const mbed::Callback<void(void)> &on_connected,
           const mbed::Callback<void(void)> &on_disconnected) :
_ble(ble),
_event_queue(event_queue), 
_device_name(device_name), 
_led(led_pin),
_adv_data_builder(_adv_data_buffer),
_on_ble_init_callback(on_ble_init_callback),
_on_connected(on_connected),
_on_disconnected(on_disconnected)
{}


void CGap::run() {
	// TODO:: Implement this functions
	// 1. Register on events to process callback function.
	_ble.onEventsToProcess(makeFunctionPointer(this, &CGap::scheduleBLEEventsToProcess));
	// 2. Register GAP event handler
	_ble.gap().setEventHandler(this);
	// 3. Initialize the BLE interface by registering a callback function
	_ble.init(this, &CGap::onBLEInitCompleteHandler);
	std::cout << "Starting BLE Application with device name \"" << _device_name << '\"' << std::endl;
	// 4. Dispatch events forever from the main thread
	_event_queue.dispatch_forever();
	// never reaches this line!
}

void CGap::startAdvertising() {
	// TODO:: Implement this functions
	// create an ble::AdvertisingParameters object with the specified configuration
	ble::AdvertisingParameters adv_parameters(
        ble::advertising_type_t::CONNECTABLE_UNDIRECTED,
        ble::adv_interval_t(ble::millisecond_t(100))
    );
	// 1. Create advertisement data
	_adv_data_builder.clear();
    _adv_data_builder.setFlags();
    _adv_data_builder.setName(_device_name.c_str());

    uint8_t byte1 = (0x11 & 0xFF); // set the data
    uint8_t manufacturerData[] = {0x34, 0x12, byte1};
    Span<uint8_t> data_span(manufacturerData, sizeof(manufacturerData));
    _adv_data_builder.addData(ble::adv_data_type_t::MANUFACTURER_SPECIFIC_DATA, data_span);
	// 2. setup the parameters
	ble_error_t error = _ble.gap().setAdvertisingParameters(
        ble::LEGACY_ADVERTISING_HANDLE,
        adv_parameters
    );
	// this is an example error print. You can come up with your own ways to do so.
	// Note that the ble_error_t type variable name is error
	std::cout << bleErrorToString(error, "GAP::setAdvertisingParameters()") << std::endl;
	if (error != BLE_ERROR_NONE) {
        std::cout << "Failed to setup the parameters: " << ble::BLE::errorToString(error) << std::endl;
		return;
	}
	// 3. set the advertisement payload
	error = _ble.gap().setAdvertisingPayload(
        ble::LEGACY_ADVERTISING_HANDLE, 
        _adv_data_builder.getAdvertisingData()
    );
	std::cout << bleErrorToString(error, "GAP::setAdvertisingPayload()") << std::endl;
	

	// 4. Start advertising
	error = _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
	std::cout << bleErrorToString(error, "GAP::startAdvertising()") << std::endl;
	
	// 5. Start blinking the Application LED
	_event_queue.cancel(_led_event_id);
    _led_event_id = _event_queue.call_every(500ms, callback(this, &CGap::toggleLED));
	std::cout << "Device is advertising" << std::endl;
}

void CGap::onConnectionComplete(const ble::ConnectionCompleteEvent &event) {
	// TODO:: Implement this functions
	// 1. if on_connected callback is not nullptr, call it
    if (_on_connected) {
        _on_connected();
    }
	// 2. keep the LED on
	_event_queue.cancel(_led_event_id);
    _led.write(0);
	std::cout << "Device is connected" << std::endl;
}
void CGap::onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event) {
	// TODO:: Implement this functions
	// 1. if on_disconnected is not nullptr, call it
    if (_on_disconnected) {
        _on_disconnected();
    }
    _event_queue.cancel(_led_event_id);
    _led_event_id = _event_queue.call_every(500ms, this, &CGap::toggleLED);
    std::cout << "Device is disconnected" << std::endl;
    // 2. start advertising
    startAdvertising();
}

void CGap::setOnBLEInitCompleteCallback(const mbed::Callback<void(ble::BLE &)> &callback) {
	// TODO:: Implement this functions
	_on_ble_init_callback = callback;
}

void CGap::setOnConnectedCallback(const mbed::Callback<void(void)> &callback) {
	// TODO:: Implement this functions
    _on_connected = callback;
}

void CGap::setOnDisconnectedCallback(const mbed::Callback<void(void)> &callback) {
	// TODO:: Implement this functions
	_on_disconnected = callback;
}
