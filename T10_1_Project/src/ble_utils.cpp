#include "ble_utils.h"

std::string bluetoothAddressToString(const ble::address_t &address) {
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

std::string bluetoothAddressToString(const ble::own_address_type_t type, const ble::address_t &address) {
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
	sstream << bluetoothAddressToString(address);
	return sstream.str();
}

std::string bluetoothAddressToString(const ble::peer_address_type_t type, const ble::address_t &address) {
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
	sstream << bluetoothAddressToString(address);
	return sstream.str();
}

std::string bufferToHex(const uint8_t *buffer, size_t size) {
	std::stringstream sstream;
	for (int i = 0; i < int(size); i++) {
		sstream << std::setw(2) << std::setfill('0') << std::right << std::hex << (int)buffer[i];
		if (i < int(size - 1)) {
			sstream << ':';
		}
	}
	return sstream.str();
}

std::string passKeyToString(const SecurityManager::Passkey_t passkey) {
	std::stringstream sstream;
	sstream << "Input passKey: ";
	for (unsigned i = ble::SecurityManager::PASSKEY_LEN; i > 0; i--) {
		sstream << char(passkey[i - 1]);
		if (i > 1) {
			sstream << " ";
		}
	}
	sstream << std::endl;
	return sstream.str();
}

std::string bleErrorToString(ble_error_t error, const char *message/* = nullptr*/) {
	std::stringstream sstream;
	if (message) {
		sstream << message << ": ";
	}
	sstream << "BLE error code " << int(error) << "\n\t";
	sstream << ble::BLE::errorToString(error);
	return sstream.str();
}