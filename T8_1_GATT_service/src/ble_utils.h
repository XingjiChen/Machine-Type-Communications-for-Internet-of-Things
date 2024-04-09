#ifndef _BLE_UTILS_H_
#define _BLE_UTILS_H_

#include <BLE.h>
#include <sstream>
#include <iomanip>
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
std::string printBluetoothAddress(const ble::address_t& address);

/**
 * @brief Returns human readable string for own Bluetooth device address
 * 
 * @param type The address type
 * @param address The bluetooth address
 * @return The address string
 */
std::string printBluetoothAddress(const ble::own_address_type_t type, 
                                         const ble::address_t& address);

/**
 * @brief Returns human readable string for peer Bluetooth device address
 * 
 * @param type The address type
 * @param address The bluetooth address of the peer device
 * @return The address string
 */
std::string printBluetoothAddress(const ble::peer_address_type_t type,
                                 const ble::address_t& address);

#endif //! _BLE_UTILS_H_