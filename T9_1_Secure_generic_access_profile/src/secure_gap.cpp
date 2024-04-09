#include "secure_gap.h"

#include <iostream>

#include "ble_utils.h"

CSecureGap::CSecureGap(ble::BLE &ble,
					   EventQueue &event_queue,
					   const std::string &device_name,
					   PinName led_pin,
					   const mbed::Callback<void(ble::BLE &)> &on_ble_init_callback /*= nullptr*/)
	: CGap(ble, event_queue, device_name, led_pin, on_ble_init_callback) {}

void CSecureGap::onBLEInitCompleteHandler(BLE::InitializationCompleteCallbackContext *context) {
	ble::peripheral_privacy_configuration_t privacyConfiguration;
	ble_error_t error;
	if (context->error) {
		std::cout << "Error during the initialisation" << std::endl;
		return;
	}
	// 1. initialize security manager. Set IO capabilities to DISPLAY_ONLY
	error = this->getBLEInstance().securityManager().init(
        false,  // enableBonding
        //true
        true,  // requireMITM
        SecurityManager::IO_CAPS_DISPLAY_ONLY,
        //SecurityManager::IO_CAPS_DISPLAY_ONLY
        nullptr  /*Passkey*/,
        false /*Support data signing*/);

	std::cout << bleErrorToString(error, "_ble.securityManager().init() ") << std::endl;
	if (error != BLE_ERROR_NONE) {
		return;
	}
	// 2. enable legacy pairing
	error = this->getBLEInstance().securityManager().allowLegacyPairing(true);
	std::cout << bleErrorToString(error, "SecurityManager.allowLegacyPairing() ") << std::endl;
	if (error != BLE_ERROR_NONE) {
		return;
	}
	// 3. set the event handler to this object
	this->getBLEInstance().securityManager().setSecurityManagerEventHandler(this);

	// 4. set pairing request authorization
	error = this->getBLEInstance().securityManager().setPairingRequestAuthorisation(true);

	std::cout << bleErrorToString(error, "SecurityManager::setPairingRequestAuthorisation() ") << std::endl;
	if (error != BLE_ERROR_NONE) {
		return;
	}
	// 5. Configure privacy settings
	/*BEGIN SOLUTION*/
	privacyConfiguration.use_non_resolvable_random_address = false;
	privacyConfiguration.resolution_strategy =
		ble::peripheral_privacy_configuration_t::REJECT_NON_RESOLVED_ADDRESS;

	ble::BLE::Instance().gap().setPeripheralPrivacyConfiguration(&privacyConfiguration);

	// 6. start advertisement using CGAP instance of this class
    if(!_on_ble_init_callback){
        // return;
    }else{
        _on_ble_init_callback(this->getBLEInstance());
    }
	startAdvertising();

	// 7. enable privacy
	error = this->getBLEInstance().gap().enablePrivacy(true);

	std::cout << bleErrorToString(error, "GAP::enablePrivacy() ") << std::endl;
	if (error != BLE_ERROR_NONE) {
		return;
	}
}

void CSecureGap::pairingRequest(ble::connection_handle_t connectionHandle) {
	std::cout << "Pairing requested - authorizing" << std::endl;
    this->getBLEInstance().securityManager().acceptPairingRequest(connectionHandle);
	
}

void CSecureGap::linkEncryptionResult(ble::connection_handle_t connectionHandle,
									  ble::link_encryption_t result) {
	if(result == ble::link_encryption_t::ENCRYPTED) {
          std::cout << "Link ENCRYPTED" << std::endl;
    } else if(result == ble::link_encryption_t::ENCRYPTED_WITH_MITM) {
        std::cout << "Link ENCRYPTED_WITH_MITM" << std::endl;
    } else if(result == ble::link_encryption_t::NOT_ENCRYPTED) {
        std::cout << "Link NOT_ENCRYPTED" << std::endl;
    }
}

void CSecureGap::passkeyDisplay(ble::connection_handle_t connectionHandle,
								const SecurityManager::Passkey_t passkey) {
    std::cout << "Input passKey: ";
    for(unsigned i = 0; i < ble::SecurityManager::PASSKEY_LEN; i++) {
        printf("%c ", passkey[ble::SecurityManager::PASSKEY_LEN - 1 - i]);
    }
    std::cout << std::endl;
	
}

void CSecureGap::confirmationRequest(ble::connection_handle_t connectionHandle) {
	std::cout << "Confirmation requested!" << std::endl;
}

void CSecureGap::passkeyRequest(ble::connection_handle_t connectionHandle) {
	std::cout << "Passkey requested!" << std::endl;
}

void CSecureGap::keypressNotification(ble::connection_handle_t connectionHandle,
									  SecurityManager::Keypress_t keypress) {
	std::cout << "keypressNotification" << std::endl;
}

void CSecureGap::signingKey(ble::connection_handle_t connectionHandle,
							const ble::csrk_t *csrk,
							bool authenticated) {
	std::cout << "signingKey" << std::endl;
}

void CSecureGap::pairingResult(ble::connection_handle_t connectionHandle,
							   SecurityManager::SecurityCompletionStatus_t result) {
	if (result == SecurityManager::SEC_STATUS_SUCCESS) {
		std::cout << "Security success" << std::endl;
	} else {
		std::cout << "Security failed" << std::endl;
	}
}

void CSecureGap::onConnectionComplete(const ble::ConnectionCompleteEvent &event) {
	ble_error_t error;
	// print the connection status here!
	std::cout << bleErrorToString(event.getStatus(), "GAP::OnConnectionComplete()") << std::endl;
    CGap::onConnectionComplete(event);
	// 1. Check that the status is successful.
	//    a. If not, just return
	//    b. If it is successful, continue with the other steps
    if (event.getStatus() != BLE_ERROR_NONE) {
        std::cout << "Connection failed" << std::endl;
		return; // Connection not successful, just return
	}
	
	// 2. Set the link security for the SecurityManager instance of system BLE instance
	//    a. Get the connection handle
	auto connectionHandle = event.getConnectionHandle();
    //    b. Set the link security to SECURITY_MODE_ENCRYPTION_WITH_MITM
	error = this->getBLEInstance().securityManager().setLinkSecurity(
	    connectionHandle,
	    SecurityManager::SECURITY_MODE_ENCRYPTION_WITH_MITM);
    //    c. Get the return code and print it
	std::cout << bleErrorToString(error, "SecurityManager::setLinkSecurity()");
}
