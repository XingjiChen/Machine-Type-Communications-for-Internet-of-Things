#include "alert_notification_service.h"

void CAlertNotificationService::buttonPressedHandler() {
	// TODO: implement this function
	// add a new alert to the ANS_TYPE_SIMPLE_ALERT category
    if(_is_connected){
        _button_press_count++;
        _alert_status[ANS_TYPE_SIMPLE_ALERT].fields.count++;
        setCharacteristicValue(*_characteristics[2], _button_press_count);
        int a = 1;
        setCharacteristicValue(*_characteristics[3], a);
	    setCharacteristicValue(*_characteristics[4], _alert_status);
    }
}

CAlertNotificationService::CAlertNotificationService(PinName button_pin)
	: _button_press_count(0), _button(button_pin) {
	// TODO:: implement this constructor

	// 1. initialize the class attributes to 0
	//      1. _supported_new_alert_category
	//      2. _supported_unread_alert_category
	//      3. _enabled_new_alert_category
	//      4. _enabled_unread_alert_category
	//      5. _alert_status -- for each category, set the alert counts to 0 but correctly initialize the
	//      category
	//                          field
    _supported_new_alert_category = 0;
    _supported_unread_alert_category = 0;
    _enabled_new_alert_category = 0;
    _enabled_unread_alert_category = 0;
    for (int i = 0; i < ANS_ALERT_CATEGORY_COUNT; i++) {
        _alert_status[i].value = 0;
        _alert_status[i].fields.category = i; 
    }
	// 2. create the characteristics with UUIDs declared under GattService class namespace
	//      GattCharacteristic::UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR
    this->addCharacteristic(
        GattCharacteristic::UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR,
        &_supported_new_alert_category,
        GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ,
        nullptr
        );
    //      GattCharacteristic::UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR
    this->addCharacteristic(
        GattCharacteristic::UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR,
        &_supported_unread_alert_category,
        GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ,
        nullptr
        );
    //      GattCharacteristic::UUID_UNREAD_ALERT_CHAR
    this->addCharacteristic(
        GattCharacteristic::UUID_UNREAD_ALERT_CHAR,
        &_enabled_unread_alert_category,
        GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY,
        nullptr
        );
    
    //      GattCharacteristic::UUID_NEW_ALERT_CHAR
    this->addCharacteristic(
        GattCharacteristic::UUID_NEW_ALERT_CHAR,
        &_enabled_new_alert_category,
        GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY,
        nullptr
        );

    //      GattCharacteristic::UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR
    this->addCharacteristic(
        GattCharacteristic::UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR,
        &_alert_status,
        GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE,
        nullptr
        );

	//    As you did in Modules 8, follow the characteristics indices as the creation order
	//
	
	// 3. create the service with UUID GattService::UUID_ALERT_NOTIFICATION_SERVICE
	_service.reset(new GattService(
        GattService::UUID_ALERT_NOTIFICATION_SERVICE,
        _characteristics.data(),
        _characteristics.size()));
	// 4. configure Falling edge ISR function for the button
	_button.fall(callback(this, &CAlertNotificationService::buttonPressedHandler));
}

CAlertNotificationService::~CAlertNotificationService() {}

void CAlertNotificationService::onDataWrittenHandler(GattCharacteristic* characteristic,
													 const uint8_t* data,
													 uint16_t size) {}

void CAlertNotificationService::onConnected(void) {
    _is_connected = true;
}

void CAlertNotificationService::onDisconnected(void) {
    _is_connected = false;
    _button_press_count = 0;
}

void CAlertNotificationService::registerService(ble::BLE& ble) {
    if (_service) {
        ble.gattServer().addService(*_service);
    }
}

bool CAlertNotificationService::addNewAlertToCategory(CAlertNotificationService::CategoryId category) {
    _alert_status[category].fields.count++;
    // Increment the alert count
    return true; 
}
bool CAlertNotificationService::setSupportedUnreadAlertsCategory(uint16_t supportedUnreadAlerts) {
	return false;
}

bool CAlertNotificationService::addSupportedUnreadAlertsCategory(
	CAlertNotificationService::CategoryId category) {
	return false;
}

bool CAlertNotificationService::removeSupportedUnreadAlertsCategory(
	CAlertNotificationService::CategoryId category) {
	return false;
}

bool CAlertNotificationService::setSupportedNewAlertsCategory(uint16_t supportedUnreadAlerts) {
	return false;
}

bool CAlertNotificationService::addSupportedNewAlertsCategory(
	CAlertNotificationService::CategoryId category) {
	return false;
}

bool CAlertNotificationService::removeSupportedNewAlertsCategory(
	CAlertNotificationService::CategoryId category) {
	return false;
}

void CAlertNotificationService::clearAlertsOfCategory(CategoryId category) {
    if (category == ANS_TYPE_ALL_ALERTS) {
        for (int i = 0; i < ANS_ALERT_CATEGORY_COUNT; i++) {
            _alert_status[i].fields.count = 0;
        }
    } else {
        _alert_status[category].fields.count = 0;
    }
}
