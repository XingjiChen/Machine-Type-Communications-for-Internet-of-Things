#pragma once
#include <BLE.h>
#include <mbed.h>

#include <memory>
#include <vector>

/**
 * @brief A GattService class which allows managing its characteristics
 * using C++ containers, smart pointers and templates.
 *
 * The class is designed so that
 * 1. The caller adds as many characteristics as desired.
 * 2. Creates the service.
 * 3. Registers the service to the (system's) GattServer instance
 *
 * IMPORTANT::
 * This class uses C++ containers, C++ templates, and smart pointers.
 * If you are not familiar with these, first check the container Module in Part I.
 * For templates and smart pointers, see the Advanced C++ concepts module.
 *
 * @note std::vector stores its elements in contiguous memory region. Therefore,
 * an address of its first element can be used as an C array.
 *
 * @details Mbed OS GattService and GattCharacteristic classes have some non-trivial
 * assumptions about their member life spans. For example, when constructing a characteristic
 * attributes are copied from the constructor arguments, but later managed (copying and/or moving)
 * to the memory that is managed by the stack. Therefore, it is developer's responsibility to
 * make sure that the constructor arguments are valid till the stack moves/copies the
 * arguments to the stack.
 *
 * This class ensures that the memory remains intact.
 *
 * NOTE: This class cannot be copied since _service is stored as std::unique_ptr
 */
class CGattService : mbed::NonCopyable<CGattService> {
   protected:
	std::vector<std::vector<GattAttribute *>>
		_characteristics_user_descriptions;	 //!< The user description attributes of all the characteristics
	std::vector<GattCharacteristic *> _characteristics;	 //!< The characteristics of the service

	std::unique_ptr<GattService> _service;	//!< The service encapsulated in unique pointer
   public:
	/**
	 * @brief Construct a new CGattService object
	 * Initially the service is empty
	 */
	CGattService();
	/**
	 * @brief Destroy the CGattService object
	 *
	 */
	~CGattService();

	/**
	 * @brief Adds an empty characteristic to the service if the service has not been created
	 *
	 * @details The created characteristic does not have a value
	 *
	 * @param uuid The UUID of the characteristic
	 * @param properties The properties of the characteristic. It does not have any properties by default.
	 * @param user_description The user description of the characteristic. It does not have a user description
	 * by default.
	 * @param value The initial value of the characteristic
	 * @param max_value_size The maximum value of the characteristic. If value is not nullptr, its size must
	 * be equal to max_value_size.
	 * @return true If the characteristic can be created and added (when service has not been created yet)
	 * @return false If the service is created already or there is an error in creating the characteristic
	 */

	bool addCharacteristic(const char *uuid,
						   const uint8_t properties = GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NONE,
						   const char *user_description = nullptr,
						   uint8_t *value = nullptr,
						   size_t max_value_size = 0);

	/**
	 * @brief Adds a characteristic to the service if the service has not been created
	 *
	 * @tparam T The type of the characteristic value
	 * @param uuid The UUID of the characteristic
	 * @param value The default value of the characteristic
	 * @param properties The properties of the characteristic. It does not have any properties by default.
	 * @param user_description The user description of the characteristic. It does not have a user description
	 * by default.
	 * @return true If the characteristic can be created and added (when service has not been created yet)
	 * @return false If the service is created already or there is an error in creating the characteristic
	 */
	template <typename T>
	bool addCharacteristic(const char *uuid,
						   const T &value,
						   const uint8_t properties = GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NONE,
						   const char *user_description = nullptr) {
		// This function is not required for this task. You will implement it in the next task.
		return false;
	}
	/**
	 * @brief Get the Characteristic that has the specified Value attribute Handle
	 *
	 * @note this function must be called only if BLE is successfully initialized
	 *
	 * @param value_handle The handle of the characteristics value attribute
	 * @return A pointer to the characteristics. nullptr if a characteristics
	 * with the specfied value handle cannot be found.
	 */
	GattCharacteristic *getCharacteristicWithValueHandle(const GattAttribute::Handle_t &value_handle) const;

	/**
	 * @brief Returns the user description of the characteristic with the specfied value handle
	 *
	 * @param value_handle The value handle of the characteristic
	 * @return nullptr if the characteristic is not in this service or its user description is not set;
	 * otherwise, a pointer to the user description string
	 */
	const char *getCharacteristicUserDescription(const GattAttribute::Handle_t &value_handle) const;

	/**
	 * @brief Handler, called when the value of a characteristic is modified
	 *
	 * @param characteristic the characteristic that has been modified
	 * @param data The written data
	 * @param size The size of the written data
	 */
	virtual void onDataWrittenHandler(GattCharacteristic *characteristic, const uint8_t *data, uint16_t size);
	/**
	 * @brief Create a Service object
	 *
	 * @param uuid The UUID of the service
	 * @return ble_error_t indicating if there has been an error in creating the service
	 */
	ble_error_t createService(const char *uuid);

	/**
	 * @brief Get a shared pointer to the GattService of this object
	 *
	 * @return A pointer to the GattService of this object. nullptr if the is has been created.
	 */
	GattService *getService() const;
	/**
	 * @brief Get the Characteristic Count added to this service
	 *
	 * @return The number of characteristics
	 */
	unsigned int getCharacteristicCount() const;

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
		// This function is not required for this task. You will implement it in the next task.
		return BLE_ERROR_NOT_IMPLEMENTED;
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
		// This function is not required for this task. You will implement it in the next task.
		return BLE_ERROR_NOT_IMPLEMENTED;
	}

	/**
	 * @brief Returns whther this service has been created
	 *
	 * @return true if service has been created
	 * @return false if service has not been created
	 */
	explicit operator bool() const {
		// use the bool operator of std::unique_ptr
		return bool(_service);
	}

	/**
	 * @brief Registers this service to GattServer instance of the system.
	 *
	 * @param ble A reference to the system BLE instance.
	 */
	virtual void registerService(ble::BLE &ble);
};