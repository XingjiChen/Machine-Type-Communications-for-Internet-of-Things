#include "gatt_service.h"
#include <iostream>
#include <memory>

CGattService::CGattService() {}

CGattService::~CGattService() {
	// TODO:: Implement this functions

	// 1. First release the service
	// you can use std::unique_ptr::reset function
    _service.reset();
	

	// 2. Destruct the characteristics
	 for (auto &c : _characteristics) {
        delete c;
    }
    _characteristics.clear();
	// 3. Destruct the characteristic descriptors
	for (auto &d : _characteristics_user_descriptions) {
        for (auto &desc : d) {
            delete desc;
        }
    }
    _characteristics_user_descriptions.clear();
}

bool CGattService::addCharacteristic(
        const char *uuid,
        const uint8_t properties /*= GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NONE*/,
        const char *user_description /*= nullptr*/,
        uint8_t *value /*= nullptr*/,
        size_t max_value_size /*= 0*/) {
    // TODO:: Implement this functions

    // 1. check whether the service has not been created yet.
    if (_service) {
        // if it is, we cannot add characteristics to it.
        return false;
    }
    // 2. create the user description attribute
    //  i. create a vector for the characteristic descriptors. You might want to check
    //      std::vector::emplace_back and std::vector::back functions.
    std::vector<GattAttribute *> characteristicDescriptors;
    //  ii. if the user_description is not empty
    //      a. create (by dynamically allocating) a new attribute. assert that the attribute memory can be
    //          allocated. // NOTE:: You cannot use static_assert function. Why?
    //      b. add it to the just created list
    //  iii. If the user_description is empty, just keep the list empty
    // if(user_description){
    GattAttribute* userDescriptionAtt = new GattAttribute(BLE_UUID_DESCRIPTOR_CHAR_USER_DESC,/*Bluetooth defined UUID for CHARACTERISTIC_DESCRIPTOR*/
                                                          (uint8_t *)user_description, /*Value of this attribute*/
                                                          strlen(user_description)+1, /*size of the initial value*/
                                                          strlen(user_description)+1, /*maximum size the attribute value might have*/
                                                          false /*this attribute has fixed size */);

    assert(userDescriptionAtt != nullptr && "Memory allocation for userDescriptionAtt failed");
    characteristicDescriptors.emplace_back(userDescriptionAtt);

    _characteristics_user_descriptions.emplace_back(characteristicDescriptors);
    // }

    // 3. create the characteristic by using the fact that std::vector places its element
    //    in contiguous memory region to get the characteristic attributes
    //
    //    allocate new entry to service
    //    i. allocate a new characteristic. Note that len is equal max_value_size when value is not nullptr.
    //       maxLen is always equal to max_value_size
    //    ii. assert that the attribute memory can be
    //          allocated. // NOTE:: You cannot use static_assert function. Why?
    //    iii. add the characteristic to _characteristics

    // GattAttribute* characteristic1Descriptors[1];
    // characteristic1Descriptors[0] = characteristicDescriptors.back();

    GattCharacteristic* gattCharacteristic = new GattCharacteristic(uuid, /*UUID of the characteristic*/
                                                                    value, /*Memory buffer holding the initial value. */
                                                                    (value ? max_value_size : 0), /*The size in bytes of the characteristic's value*/
                                                                    max_value_size, /*The capacity in bytes of the characteristic value buffer*/
                                                                    properties, /*An 8-bit field that contains the characteristic's properties*/
                                                                    _characteristics_user_descriptions.back().data(), /*A pointer to an array of descriptors to be included within this characteristic.*/
                                                                    1, /*The number of descriptors presents in descriptors array*/
                                                                    false /*Flag that indicates if the attribute's value has variable length*/);

    // std::cout << user_description << std::endl;
    if(!strcmp(user_description,"LED2")){
        std::cout << "setting LED2 authentication" << std::endl;
        gattCharacteristic->setReadSecurityRequirement(ble::att_security_requirement_t::UNAUTHENTICATED);
        gattCharacteristic->setWriteSecurityRequirement(ble::att_security_requirement_t::AUTHENTICATED);
        gattCharacteristic->setUpdateSecurityRequirement(ble::att_security_requirement_t::UNAUTHENTICATED);
        // std::cout << gattCharacteristic->getReadSecurityRequirement() << std::endl;
    }else if(!strcmp(user_description,"DummyConfig")){
        std::cout << "setting DummyConfig authentication" << std::endl;
        gattCharacteristic->setReadSecurityRequirement(ble::att_security_requirement_t::UNAUTHENTICATED);
        gattCharacteristic->setWriteSecurityRequirement(ble::att_security_requirement_t::AUTHENTICATED);
        gattCharacteristic->setUpdateSecurityRequirement(ble::att_security_requirement_t::UNAUTHENTICATED);
    }else if(!strcmp(user_description,"TickCount")){
        std::cout << "setting TickCount authentication" << std::endl;
        gattCharacteristic->setReadSecurityRequirement(ble::att_security_requirement_t::UNAUTHENTICATED);
        gattCharacteristic->setWriteSecurityRequirement(ble::att_security_requirement_t::UNAUTHENTICATED);
        gattCharacteristic->setUpdateSecurityRequirement(ble::att_security_requirement_t::AUTHENTICATED);
    }else{
        std::cout << " error when creating gattcharacteristic" << std::endl;
        return false;
    }

    assert(gattCharacteristic != nullptr && "Memory allocation for gattCharacteristic failed");
    _characteristics.emplace_back(gattCharacteristic);
    return true;
}

GattCharacteristic *CGattService::getCharacteristicWithValueHandle(
	const GattAttribute::Handle_t &value_handle) const {
	// TODO:: Implement this functions
	// 1. Iterate over _characteristics
	//    i. For each characteristic, compare its value handle with the argument value handle
	//    ii. If a characteristic has a value handle, return it.
	//    iii. If no characteristic has the indicated value handle, return nullptr.
    for (const auto &characteristic : _characteristics) {
        if (characteristic->getValueHandle() == value_handle) {
            return characteristic;
        }
    }
    return nullptr;
}

const char *CGattService::getCharacteristicUserDescription(
	const GattAttribute::Handle_t &value_handle) const {
	// TODO:: Implement this functions
	// int characteristic_index = 0;
	// 1. Iterate over _characteristics
	//    i. For each characteristic, compare its value handle with the argument value handle
	//    ii. If a characteristic has the value handle value_handle,
	//        a. Get the descriptors of that characteristic in _characteristics_user_descriptions vector
	//        b. Get the first descriptor
	//        c. Get the value pointer of the attribute using you can use GattAttribute::getValuePtr function.
	//        d. Cast it to const char*
    //    iii. Otherwise, increase characteristic index
	//    iv. If no characteristic has the indicated value handle, return nullptr.
	for (size_t i = 0; i < _characteristics.size(); i++) {
        if (_characteristics[i]->getValueHandle() == value_handle) {
            if (!_characteristics_user_descriptions[i].empty()) {
                return reinterpret_cast<const char*>(_characteristics_user_descriptions[i].front()->getValuePtr());
            }
            break;
        }
    }
	return nullptr;
}

/**
 * @brief Handler, called when the value of a characteristic is modified
 *
 * @param characteristic the characteristic that has been modified
 * @param data The written data
 * @param size The size of the written data
 */
void CGattService::onDataWrittenHandler(GattCharacteristic *characteristic,
										const uint8_t *data,
										uint16_t size) {
	(void)characteristic;
	(void)data;
	(void)size;
	// This function is a placeholder, and will be overriden by the derived classes.
}

ble_error_t CGattService::createService(const char *uuid) {
	// TODO:: Implement this functions

	// 1. assert that the service has already been created.
	//    if it has been created, and this function is called again,
	//    there is something wrong with the software design
	if (_service) {
        return BLE_ERROR_OPERATION_NOT_PERMITTED;
    }
    std::cout << "Service has already been created" << std::endl;
	// 2. check whether the service has some characteristics that can be added to the service
	//    If there is no characteristics, return BLE_ERROR_INVALID_STATE
	if (_characteristics.empty()) {
        return BLE_ERROR_INVALID_STATE;
    }
	// 3. create a shared pointer for the service
	//    you can use std::make_unique function
	_service = std::make_unique<GattService>(UUID(uuid), _characteristics.data(), _characteristics.size());
	// 4. assert that the _service memory has been successfully allocated
	if (!_service) {
        std::cout << "Service memory allocated Failed" << std::endl;
    }
    std::cout << "Service memory allocated successfully" << std::endl;
	// 5. Return BLE_ERROR_NONE
	return BLE_ERROR_NONE;
	//return BLE_ERROR_NOT_IMPLEMENTED;
}

GattService *CGattService::getService() const {
	// TODO:: Implement this functions
	return _service.get();
	//return nullptr;
	
}

unsigned int CGattService::getCharacteristicCount() const {
	// TODO:: Implement this functions
	return _characteristics.size();
	//return 0;
	
}

void CGattService::registerService(ble::BLE &ble) {
	// TODO:: Implement this functions
	if (_service) {
        ble.gattServer().addService(*_service);
    }
}