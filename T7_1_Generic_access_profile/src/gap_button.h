#include <mbed.h>
#include <BLE.h>
#include <string>

/**
 * @brief Generic Access Profile class that advertises number of button presses since system startup
 * 
 * It is non-copyable class that implements Mbed's ble::Gap::EventHandler class.
 * 
 * @note You must inherit this class as specified in the task description.
 * 
 * @note You can print errors of ble_error_t type using static member function 
 * ble::BLE::errorToString of ble::BLE class. This function returns a string; 
 * you can use the returned string at your convenience.
 */

class CGAPButton : private mbed::NonCopyable<CGAPButton>, public ble::Gap::EventHandler {

private: 
    ble::BLE& _ble; //!< A reference to the BLE system's BLE object instance
    events::EventQueue& _event_queue; //!< A reference to the application's EventQueue
    std::string _device_name; //!< The name of the device.

    uint32_t _button_press_count; //!< The number of button press counts since the system startup
    InterruptIn _button; //!< The button ISR that will be used for counting number of presses
    DigitalOut _led; //!< The system LED that will be used for indicating advertisement and connection status
    int _led_event_id; //!< The Event identifier (returned by EventQueue::call_every function)

    ble::AdvertisingDataBuilder _adv_data_builder; //!< Advertisement data builder that will be used for creating, storing and manipulating advertisement data
    uint8_t _adv_data_buffer[ble::LEGACY_ADVERTISING_MAX_SIZE]; //!< The buffer that is used by the advertisement data builder


protected: 
    /**
     * @brief Button pressed ISR function. 
     * 1. Detects a button press (discards button release), 
     * 2. updates the button press count, and 
     * 3. triggers advertisement data update
     * 
     * @note This function is in ISR context: It must be as simple as possible. Although it is possible 
     * to update advertisement data from it, it is a better practice to hand over that update to 
     * EventQueue dispatch loop using, for example, EventQueue::call function
     */
    void buttonPressedHandler();
    /**
     * @brief Toggles the LED state. 
     * 
     * @note This function must be called by the EventQueue dispatcher.
     */
    void toggleLED();
    /**
     * @brief Updates the advertisement data when the button is pressed. Th
     * 
     * @note This function must be called by the EventQueue dispatcher.
     */
    void updateAdvertisementData();
    /**
     * @brief This the application's system BLE initialization complete function.
     * 
     * @note This function must registered as BLE initialization completion handler function
     * by calling BLE::init member function of BLE class. 
     * 
     * @note There are different overloads of BLE::init 
     * 
     * @param context The initialization context
     */
    void onBLEInitCompleteHandler(BLE::InitializationCompleteCallbackContext *context);

    /**
     * @brief Redirects pending BLE events to EventQueue dispatcher, which calls BLE::processEvents
     * 
     * @note The BLE event processing can be handed over to the EventQueue dispatcher 
     * using EventQueue::call function. Therefore, we must use this function to bind 
     * Event function to BLE::processEvents function.
     * 
     * @param context The context of the events to be processed
     */
    void scheduleBLEEventsToProcess(BLE::OnEventsToProcessCallbackContext* context);

    /**
     * @brief Handler function called when the BLE connection process completes. 
     * 
     * @note You are required to stop blinking the application LED when BLE is connected.
     * You can use EventQueue::cancel function with the event identifier to stop periodically 
     * LED toggling.
     *  
     * @param event The connection event object
     */
    virtual void onConnectionComplete(const ble::ConnectionCompleteEvent &event) override;
    /**
     * @brief Handler function called when the BLE connection is terminated (disconnected)
     * 
     * @param event The disconnection event object
     */
    virtual void onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event) override;
public:
    /**
     * @brief Construct a new CGAPButton object
     * 
     * @param ble A reference to the system's BLE object
     * @param event_queue A reference to the application's event queue object
     * @param device_name The name of the device
     * @param button_pin The Button pin name that will be used by the application
     * @param led_pin The LED pin name that will be used by the application
     */
    CGAPButton(ble::BLE& ble, 
                EventQueue& event_queue, 
                const std::string& device_name, 
                PinName button_pin, 
                PinName led_pin);
    /**
     * @brief Starts BLE operation
     * 
     * It performs the following operations:
     * 1. Registers this object's member function as BLE::onEventsToProcess function
     *    In order to create FunctionPointerWithContext object (required by BLE::onEventsToProcess)
     *    you can use makeFunctionPointer function.
     * 2. Register GAP event handler as this object since this class is 
     *    inherited from ble::Gap::EventHandler structure.
     * 3. Initialize system's BLE object, and register this object's member function
     *    to be called when the BLE initialization completes.
     * 4. Dispatches EventQueue events for ever. 
     * 
     * @note It is useful to print the the status of this operations for debugging 
     * and monitoring purposes.
     * 
     */
    void run();
    /**
     * @brief Starts advertising
     * 
     * Advertisement is configured and started as follows:
     * 1. Create advertisement data using ble::AdvertisingDataBuilder type member
     * 2. Setup the advertisement parameters
     * 3. Set the advertisement payload
     * 4. Start the advertisement
     * 5. Start toggling the application LED
     * 
     * @note It is useful to print the the status of this operations for debugging 
     * and monitoring purposes.
     */
    void startAdvertising();
};