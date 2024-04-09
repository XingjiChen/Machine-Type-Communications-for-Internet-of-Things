#include "gap_button.h"
#include "ble_utils.h"
#include <iostream>
volatile bool buttonPressedFlag = false;
void CGAPButton::buttonPressedHandler(){
    _button_press_count ++;
    //_button_press_count ++;
    //std::cout << "_button_press_count is : " << _button_press_count << std::endl;
    _event_queue.call(callback(this, &CGAPButton::updateAdvertisementData));
}

void CGAPButton::toggleLED(){
    //std::cout << "LED state: " <<  _led.read() << std::endl;
    _led = !_led;
}

void CGAPButton::updateAdvertisementData(){
    //_button_press_count++;
    std::cout << "button_press_count: " << _button_press_count << std::endl;
    
    uint8_t byte1 = (_button_press_count & 0xFF);
    uint8_t manufacturerData[] = {0x34, 0x12, byte1};
    Span<uint8_t> data_span(manufacturerData, sizeof(manufacturerData));
    _adv_data_builder.replaceData(ble::adv_data_type_t::MANUFACTURER_SPECIFIC_DATA, data_span);

    // 3. set the advertisement payload
    ble_error_t error = _ble.gap().setAdvertisingPayload(
        ble::LEGACY_ADVERTISING_HANDLE, 
        _adv_data_builder.getAdvertisingData()
    );
    if (error!= 0U) {
        // this is an example error print. You can come up with your own ways to do so.
        // Note that the ble_error_t type variable name is error
        std::cout << "Failed to set advertising payload: " << ble::BLE::errorToString(error) << std::endl;
        return;
    }
    
    std::cout << "Advertisement data updated!" << std::endl;
}

void CGAPButton::onBLEInitCompleteHandler(BLE::InitializationCompleteCallbackContext *context){
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
    if (error == BLE_ERROR_NONE)
        // print the own Bluetooth address using 
        // printBluetoothAddress utility function defined in ble_utils.h
        // note that there are 3 overloads of that function.
        std::cout << printBluetoothAddress(addrType, address) << std::endl;

    else
        std::cout << "Failed to get device address." << std::endl;
        
    // 3. start blinking the led
    _event_queue.cancel(_led_event_id);
    _led_event_id  = _event_queue.call_every(500ms, this, &CGAPButton::toggleLED);
    // 4. start advertising
    startAdvertising();
}

void CGAPButton::scheduleBLEEventsToProcess(BLE::OnEventsToProcessCallbackContext* context){
    _event_queue.call(callback(&_ble, &BLE::processEvents));
}



CGAPButton::CGAPButton(ble::BLE& ble, 
                        EventQueue& event_queue, 
                        const std::string& device_name, 
                        PinName button_pin, 
                        PinName led_pin):
_ble(ble),
_event_queue(event_queue), 
_device_name(device_name), 
_button_press_count(0),
_button(button_pin), 
_led(led_pin),
_adv_data_builder(_adv_data_buffer)
{
    _button.fall(callback(this, &CGAPButton::buttonPressedHandler)); 
}
//_button.fall(callback(this, &CGAPButton::buttonPressedHandler)); 

void CGAPButton::run(){
    // 1. Register on events to process callback function.
    _ble.onEventsToProcess(makeFunctionPointer(this, &CGAPButton::scheduleBLEEventsToProcess));
    // 2. Register GAP event handler 
    _ble.gap().setEventHandler(this);
    // 3. Initialize the BLE interface by registering a callback function
    _ble.init(this, &CGAPButton::onBLEInitCompleteHandler);
    std::cout << "Starting BLE Application " << std::endl;
    // 4. Dispatch events forever from the main thread
    _event_queue.dispatch_forever();
    // never reaches this line!
}

void CGAPButton::startAdvertising(){
    // create an ble::AdvertisingParameters object with the specified configuration
    ble::AdvertisingParameters adv_parameters(
        ble::advertising_type_t::CONNECTABLE_UNDIRECTED,
        ble::adv_interval_t(ble::millisecond_t(100))
    );
    // 1. Create advertisement data
    _adv_data_builder.clear();
    _adv_data_builder.setFlags();
    _adv_data_builder.setName(_device_name.c_str());

    uint8_t byte1 = (_button_press_count & 0xFF);
    uint8_t manufacturerData[] = {0x34, 0x12, byte1};
    Span<uint8_t> data_span(manufacturerData, sizeof(manufacturerData));
    _adv_data_builder.addData(ble::adv_data_type_t::MANUFACTURER_SPECIFIC_DATA, data_span);

    // 2. setup the parameters
    ble_error_t error = _ble.gap().setAdvertisingParameters(
        ble::LEGACY_ADVERTISING_HANDLE,
        adv_parameters
    );
    if (error != 0U) {
        // this is an example error print. You can come up with your own ways to do so.
        // Note that the ble_error_t type variable name is error
        std::cout << "Failed to setup the parameters: " << ble::BLE::errorToString(error) << std::endl;
        return;
    }
    // 3. set the advertisement payload
    error = _ble.gap().setAdvertisingPayload(
        ble::LEGACY_ADVERTISING_HANDLE, 
        _adv_data_builder.getAdvertisingData()
    );
    if (error!= 0U) {
        // this is an example error print. You can come up with your own ways to do so.
        // Note that the ble_error_t type variable name is error
        std::cout << "Failed to set advertising payload: " << ble::BLE::errorToString(error) << std::endl;
        return;
    }
    // 4. Start advertising 
    error = _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
    if (error!= 0U) {
        std::cout << "Failed to start advertising: " << ble::BLE::errorToString(error) << std::endl;
        return;
    }
    // 5. Start blinking the Application LED
    _event_queue.cancel(_led_event_id);
    _led_event_id = _event_queue.call_every(500ms, callback(this, &CGAPButton::toggleLED));
    std::cout << "Device is advertising" << std::endl;
}

void CGAPButton::onConnectionComplete(const ble::ConnectionCompleteEvent &event){
    //stops blinking the LED
    _event_queue.cancel(_led_event_id);
    // keep the LED on
    _led.write(0);
    std::cout << "Device is connected" << std::endl;
}
void CGAPButton::onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event){
    _event_queue.cancel(_led_event_id);
    _led_event_id = _event_queue.call_every(500ms, this, &CGAPButton::toggleLED);
    std::cout << "Device is disconnected" << std::endl;
    startAdvertising();
}