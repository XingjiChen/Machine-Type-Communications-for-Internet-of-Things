#pragma once
#include <BLE.h>
#include <mbed.h>

#include <memory>
#include <vector>

#include "gatt_service.h"
/**
 * @brief An example GattService implementation based on CGattService base class.
 *
 * @details
 */
class CExampleGattService : public CGattService {
   private:
    EventQueue &_event_queue;  //!< A reference to the application's EventQueue
	int _characteristic_led_index;	//!< The index of the LED2 characteristic in _characteristics container
	int _characteristic_dummy_config_index;	 //!< The index of the DummyConfig characteristic in
											 //!< _characteristics container
	int _characteristic_tick_count_index;  //!< The index of the TickCount characteristic in _characteristics
										   //!< container

	DigitalOut _led;		 //!< The system LED that will be used for indicating LED2 characteristic value
	uint8_t _led_value;		 //!< the value of the LED
	uint32_t _tick_count;	 //!< The latest tick count
	uint16_t _dummy_config;	 //!< The latest value of dummy config

	/**
	 * @brief Updates the tick count value by reading the time using
	 * Kernel::Clock::now().time_since_epoch().count()
	 */
	void updateTickCount();

   public:
	/**
	 * @brief Construct a new CExampleGattService object
	 *
	 * @param event_queue The event queue of the system that will be used for registering periodic tick
	 * reading
	 * @param led_pin The LED pin that will be used by the LED characteristic
	 */
	CExampleGattService(EventQueue &event_queue, PinName led_pin);
	/**
	 * @brief Destroy the CGattService object
	 *
	 */
	~CExampleGattService();

	// = delete; -> this prevents exposing base class member to the caller
	/**
	 * @brief Create a Service object
	 *
	 * @param uuid The UUID of the service
	 * @return ble_error_t indicating if there has been an error in creating the service
	 */
	ble_error_t createService(const char *uuid) = delete;

	/**
	 * @brief Handler, called when the value of a characteristic is modified
	 *
	 * @param characteristic the characteristic that has been modified
	 * @param data The written data
	 * @param size The size of the written data
	 */
	virtual void onDataWrittenHandler(GattCharacteristic *characteristic,
									  const uint8_t *data,
									  uint16_t size) override;

	/**
	 * @brief Get the Characteristic Value
	 *
	 * @note This function does NOT work on local copies of the Value attributes
	 *
	 * @tparam T The characteristic value type
	 * @param characteristic The characteristic
	 * @param value A reference to the value
	 * @return The error received while writing the characteristic value.
	 */
	template <typename T>
	static ble_error_t getCharacteristicValue(GattCharacteristic &characteristic, T &value) {
		ble::GattServer &server = ble::BLE::Instance().gattServer();
		// GattServer::read function uses lengthP parameter for two purposes.
		//  I. To indicate the maximum size that buffer parameter can store (in this case it must sizeof(T))
		//  II. To return the actual size of the value so that the next call would have a larger size

		// 1. Read the value of the characteristic
		//    i. declare size variable that is initialized to size of T data type
		//    ii. call GattServer::read function
		//    iii. You must store the return code of the call
		uint16_t length = sizeof(T);
        ble_error_t error = server.read(characteristic.getValueHandle(), reinterpret_cast<uint8_t*>(&value), &length);
		// 2. If return code indicates no error, check the value of lengthP argument of GattServer::read
		//    i. If returned value of lengthP is larger than size of T, return BLE_ERROR_BUFFER_OVERFLOW
		//    ii. Otherwise return the returned error code.
		if (error != BLE_ERROR_NONE) {
            return error; // Return the error code if the read operation failed
        }
        if (length > sizeof(T)) {
            return BLE_ERROR_BUFFER_OVERFLOW;
        }
        return error;
		//return BLE_ERROR_NOT_IMPLEMENTED;
		
	}

	/**
	 * @brief Set the Characteristic Value
	 *
	 * @note This function does NOT work on local copies of the Value attributes
	 *
	 * @tparam T The characteristic value type
	 * @param characteristic The characteristic
	 * @param value A reference to the value
	 * @return The error received while writing the characteristic value.
	 */
	template <typename T>
	static ble_error_t setCharacteristicValue(GattCharacteristic &characteristic, T &value) {
		ble::GattServer &server = ble::BLE::Instance().gattServer();
		// 1. Write the value of the characteristic
		//    i. call GattServer::read function. Note that localOnly argument must be false.
		//    ii. We must use reinterpret_cast operator to cast the T* to const uint8_t* to use value as
		//        destination buffer
		//    iii. Return the returned error code
		
		auto error = server.write(characteristic.getValueHandle(),reinterpret_cast<const uint8_t *>(&value),sizeof(T),false);
		return error;
		
	}

	/**
	 * @brief Registers this service to GattServer instance of the system.
	 *
	 * @param ble A reference to the system BLE instance.
	 */
	virtual void registerService(ble::BLE &ble) override;
};