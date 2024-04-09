#pragma once

#include <BLE.h>

#include <list>
#include <memory>

#include "gatt_service.h"

/**
 * @brief A Gatt Server class derived from GattServer::EventHandler.
 *
 * @details This class is a service container so that several services can be added to it.
 * It provide a CGattServer::registerServer class, which adds its services to
 * GattServer instance of the system. It does so by calling CGattService::registerService
 * virtual function.
 *
 * NOTE: C++ inheritance allows us to change the functions that would normally require
 * function pointers.
 *
 * This class implements several (basic) GattServer event handlers.
 * Uou are required to implement these handler functions.
 *
 */
class CGattServer : public GattServer::EventHandler, public mbed::NonCopyable<CGattServer> {
   private:
	// This time we are not required to store our managed objects in contiguous memory regions.
	// we can use std::list container which has relaxed insertion, removal properties.
	std::list<CGattService *> _services;  //!< The services of this server.
	bool _started;						  //!< Indicates that the server has started when it is true.

   public:
	/**
	 * @brief Construct a new CGattServer object
	 *
	 */
	CGattServer();
	/**
	 * @brief Destroy the CGattServer object
	 *
	 */
	~CGattServer();
	/**
	 * @brief Adds a service to this server.
	 * @details A service can be added if
	 * 1. Service has been created
	 * 2. The server has not been started
	 *
	 * @param service The service to be added
	 * @return true If service can be added
	 * @return false If service cannot be added
	 */
	bool addService(CGattService &service);
	/**
	 * @brief Starts this server by performing registration operations
	 *
	 * @details The server is started regardless of number of added services
	 * 1. It registers each of this server's service.
	 * 2. Registers this object as an event handler of syetem's GattServer
	 *
	 * @param ble A reference to system's BLE instance
	 */
	void startServer(ble::BLE &ble);
	/**
	 * @brief Handler called after an attribute has been written.
	 *
	 * @param e Event parameters
	 */
	virtual void onDataWritten(const GattWriteCallbackParams &e) override;
	/**
	 * @brief Handler called after an attribute has been read.
	 *
	 * @param e The event parameters
	 */
	virtual void onDataRead(const GattReadCallbackParams &e) override;
	/**
	 * @brief Handler called after a client has subscribed to notification or indication.
	 *
	 * @param params The event parameters
	 */
	virtual void onUpdatesEnabled(const GattUpdatesEnabledCallbackParams &params) override;
	/**
	 * @brief Handler called after a client has cancelled his subscription from
	 * notification or indication.
	 *
	 * @param params The event parameters
	 */
	virtual void onUpdatesDisabled(const GattUpdatesDisabledCallbackParams &params) override;
	/**
	 * @brief Handler called when an indication confirmation has been received.
	 *
	 * @param params The event parameters
	 */
	virtual void onConfirmationReceived(const GattConfirmationReceivedCallbackParams &params) override;
};