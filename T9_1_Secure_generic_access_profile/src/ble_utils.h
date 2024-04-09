#ifndef _BLE_UTILS_H_
#define _BLE_UTILS_H_

#include <BLE.h>

#include <iomanip>
#include <sstream>
/**
 * @brief This fails has definitions of common utility functions.
 * See individual function documentations for details.
 */

/**
 * @brief Returns bluetooth address as a human readable hex string
 *
 * @param address The address to be printed
 * @return The address string
 */
std::string bluetoothAddressToString(const ble::address_t& address);

/**
 * @brief Returns human readable string for own Bluetooth device address
 *
 * @param type The address type
 * @param address The bluetooth address
 * @return The address string
 */
std::string bluetoothAddressToString(const ble::own_address_type_t type, const ble::address_t& address);

/**
 * @brief Returns human readable string for peer Bluetooth device address
 *
 * @param type The address type
 * @param address The bluetooth address of the peer device
 * @return The address string
 */
std::string bluetoothAddressToString(const ble::peer_address_type_t type, const ble::address_t& address);
/**
 * @brief Creates a string representation of the buffer in hex format
 *
 * @param buffer The buffer to be printed
 * @param size The size of the buffer
 * @return Hex string of the buffer
 */
std::string bufferToHex(const uint8_t* buffer, size_t size);

/**
 * @brief Returns a string that can be printed on the screen
 *
 * @param passkey The passkey
 * @return The human readable string of the passkey
 */
std::string passKeyToString(const SecurityManager::Passkey_t passkey);

/**
 * @brief Returns a human readable string for  Mbed OS BLE errors
 *
 * @param error The error code
 * @param message The message prepended to the error string
 * @return The error string in the format
 * "<message>: BLE error code <error number>\n\t <error description>" if message is non-null
 * "BLE error code <error number>\n\t <error description>" if message is null
 */
std::string bleErrorToString(ble_error_t error, const char* message = nullptr);
#endif	//! _BLE_UTILS_H_