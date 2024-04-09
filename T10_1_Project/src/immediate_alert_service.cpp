#include "immediate_alert_service.h"
#include <iostream>

CImmediateAlertService::CImmediateAlertService(PinName led_pin)
	: _led(led_pin), _alert_level(IAS_ALERT_LEVEL_NO_ALERT), _alert_level_value(IAS_ALERT_LEVEL_NO_ALERT) {
	// TODO:: implement this constructor
	// 1. set the PWM period to 1 seconds
    _led.period(1.0f);
	// 2. create the characteristics with UUID GattCharacteristic::UUID_ALERT_LEVEL_CHAR
	//    assert that the characteristic is successfully created
    const char *description = "immediateAlertService";
    bool result = this->addCharacteristic(
	    GattCharacteristic::UUID_ALERT_LEVEL_CHAR,
	    GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE,
	    description,
	    &_alert_level_value,
	    1);
    if(result)
        std::cout << "Add immediateAlertService successfully" << std::endl;
    else std::cout << "Failed to add characteristic" << std::endl;

	// 3. create the service with UUID GattService::UUID_IMMEDIATE_ALERT_SERVICE
	//    assert that the service is successfully created
    _service.reset(new GattService(GattService::UUID_IMMEDIATE_ALERT_SERVICE, _characteristics.data(), _characteristics.size()));
    if(_service != nullptr)
        std::cout << "Create service successfully" << std::endl;
    else std::cout << "Failed to Create service" << std::endl;
}

CImmediateAlertService::~CImmediateAlertService() {}

void CImmediateAlertService::onDataWrittenHandler(GattCharacteristic* characteristic,
												  const uint8_t* data,
												  uint16_t size) {
	// TODO:: implement this function
	// 1. Validate that characteristics has the value handle of this service's characteristic's value handle
	// 2. Cast the new value to AlertLevel enum type
	// 3. Switch between supported different options
	// 4. Set the PwM duty cycle according to alert level.
	//    i. NO_ALERT -> OFF (100%)
	//    ii. MEDIUM -> around 50%
	//    iii. HIGH  -> ON (0%)
    if (size != sizeof(AlertLevel)){
        std::cout << "Size is not match" << std::endl;
        return;
    }
    _alert_level = static_cast<AlertLevel>(*data);
	_alert_level_value = *data;
    setCharacteristicValue(*_characteristics[0], _alert_level_value);
	if (_alert_level == IAS_ALERT_LEVEL_NO_ALERT){
        _led.write(1.0); // PWM duty cycle 100% (LED OFF)
    } else if(_alert_level == IAS_ALERT_LEVEL_MEDIUM){
        _led.write(0.5); // PWM duty cycle 50% (LED Medium)
    } else if(_alert_level == IAS_ALERT_LEVEL_HIGH){
        _led.write(0.0); // PWM duty cycle 0% (LED ON)
    }
}

void CImmediateAlertService::onConnected(void) {
	// TODO:: implement this function
	_alert_level = IAS_ALERT_LEVEL_NO_ALERT;
	_alert_level_value = IAS_ALERT_LEVEL_NO_ALERT;
	// set the characteristic value
	setCharacteristicValue(*_characteristics[0], _alert_level_value);
    _led.write(1.0);
    
}

void CImmediateAlertService::onDisconnected(void) {
	// TODO:: implement this function
	_alert_level = IAS_ALERT_LEVEL_MEDIUM;
	_alert_level_value = IAS_ALERT_LEVEL_MEDIUM;
	// set the characteristic value
    setCharacteristicValue(*_characteristics[0], _alert_level_value);
	_led.write(0.5);
}

void CImmediateAlertService::registerService(ble::BLE& ble) {
	// TODO:: implement this function
	// call the registerService function of the base class
	CGattService::registerService(ble);
}
