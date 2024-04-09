#include "ble_utils.h"

/*
 * @brief Returns bluetooth address as a human readable hex string
 *
 * @param address The address to be printed
 * @return The address string
 */
std::string printBluetoothAddress(const ble::address_t& address) {
	/* Print out device MAC address to the console*/
	std::stringstream sstream;
	sstream << "Address ";
	for (int i = address.size() - 1; i >= 0; i--) {
		sstream << std::setw(2) << std::setfill('0') << std::right << std::hex << (int)address[i];
		if (i > 0) {
			sstream << ':';
		}
	}
	return sstream.str();
}

/*
 * @brief Returns human readable string for own Bluetooth device address
 *
 * @param type The address type
 * @param address The bluetooth address
 * @return The address string
 */
std::string printBluetoothAddress(const ble::own_address_type_t type, const ble::address_t& address) {
	std::stringstream sstream;
	/* Print out device MAC address to the console*/
	sstream << "LOCAL BLUETOOTH DEVICE ADDRESS ";
	switch (type.value()) {
		case ble::own_address_type_t::PUBLIC:
			sstream << "Type PUBLIC ";
			break;
		case ble::own_address_type_t::RANDOM:
			sstream << "Type RANDOM ";
			break;
		case ble::own_address_type_t::RESOLVABLE_PRIVATE_ADDRESS_PUBLIC_FALLBACK:
			sstream << "Type PUBLIC FALLBACK";
			break;
		case ble::own_address_type_t::RESOLVABLE_PRIVATE_ADDRESS_RANDOM_FALLBACK:
			sstream << "Type PRIVATE FALLBACK ";
			break;
		default:
			sstream << "Type UNKNOWN ";
			break;
	}
	sstream << printBluetoothAddress(address);
	return sstream.str();
}

/*
 * @brief Returns human readable string for peer Bluetooth device address
 *
 * @param type The address type
 * @param address The bluetooth address of the peer device
 * @return The address string
 */
std::string printBluetoothAddress(const ble::peer_address_type_t type, const ble::address_t& address) {
	std::stringstream sstream;
	/* Print out device MAC address to the console*/
	sstream << "PEER BLUETOOTH DEVICE ADDRESS ";
	switch (type.value()) {
		case ble::peer_address_type_t::PUBLIC:
			sstream << "Type PUBLIC ";
			break;
		case ble::peer_address_type_t::RANDOM:
			sstream << "Type RANDOM ";
			break;
		case ble::peer_address_type_t::RANDOM_STATIC_IDENTITY:
			sstream << "Type RANDOM STATIC IDENTITY ";
			break;
		case ble::peer_address_type_t::ANONYMOUS:
			sstream << "Type ANONYMOUS BROADCASTER";
			break;
		default:
			sstream << "Type UNKNOWN ";
			break;
	}
	sstream << printBluetoothAddress(address);
	return sstream.str();
}

/*
 * @brief Creates a string representation of the buffer in hex
 *
 * @param buffer The buffer to be printed
 * @param size The size of the buffer
 * @return Hex string of the buffer
 */
std::string bufferToHex(const uint8_t* buffer, size_t size) {
	std::stringstream sstream;
	for (int i = 0; i < int(size); i++) {
		sstream << std::setw(2) << std::setfill('0') << std::right << std::hex << (int)buffer[i];
		if (i < int(size - 1)) {
			sstream << ':';
		}
	}
	return sstream.str();
}