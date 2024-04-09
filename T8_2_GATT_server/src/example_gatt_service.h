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
	int _characteristic_led_index;	//!< The index of the LED2 characteristic in _characteristics container
	int _characteristic_dummy_config_index;	 //!< The index of the DummyConfig characteristic in
											 //!< _characteristics container
	int _characteristic_tick_count_index;  //!< The index of the TickCount characteristic in _characteristics
										   //!< container

    EventQueue &_event_queue;  //!< A reference to the application's EventQueue
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
	 * @brief Registers this service to GattServer instance of the system.
	 *
	 * @param ble A reference to the system BLE instance.
	 */
	virtual void registerService(ble::BLE &ble) override;
};