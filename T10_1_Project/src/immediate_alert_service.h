#pragma once
#include <BLE.h>
#include <mbed.h>

#include <memory>
#include <vector>

#include "gatt_service.h"
/**
 * @brief An example CImmediateAlertService declaration based on CGattService base class.
 *
 * @details YOU MUST COMPLETE THIS CLASS. THIS IS A MERE PLACE HOLDER STRIPPED FROM
 * CExampleGattService CLASS
 *
 * @note UUID of the service is GattService::UUID_IMMEDIATE_ALERT_SERVICE
 */
class CImmediateAlertService : public CGattService {
   public:
	/**
	 * \brief Immediate Alert Service alert levels
	 *
	 */
	enum AlertLevel { IAS_ALERT_LEVEL_NO_ALERT = 0, IAS_ALERT_LEVEL_MEDIUM = 1, IAS_ALERT_LEVEL_HIGH = 2 };

   private:
	PwmOut _led;  //!< The system LED that will be used to indicate alerts

	AlertLevel _alert_level;	 //!< The current alert level
	uint8_t _alert_level_value;	 //!< the value of the alert level

   public:
	CImmediateAlertService() = delete;
	CImmediateAlertService(const CImmediateAlertService &) = delete;
	const CImmediateAlertService &operator=(const CImmediateAlertService &) = delete;
	/**
	 * @brief Construct a new CImmediateAlertService object
	 *
	 * @param led_pin The LED pin that will be used by the service
	 */
	CImmediateAlertService(PinName led_pin);
	/**
	 * @brief Destroy the CGattService object
	 *
	 */
	~CImmediateAlertService();

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
									  uint16_t size) final;
	/**
	 * @brief Handler, called when a peer is connected to the GATT server
	 *
	 */
	virtual void onConnected(void) final;
	/**
	 * @brief Handler, called when a peer is disconnected from the GATT server
	 *
	 */
	virtual void onDisconnected(void) final;

	/**
	 * @brief Registers this service to GattServer instance of the system.
	 *
	 * @param ble A reference to the system BLE instance.
	 */
	virtual void registerService(ble::BLE &ble) final;
};