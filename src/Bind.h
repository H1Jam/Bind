#ifndef __BIND_H
#define __BIND_H
#include <stdint.h>
#include "Stream.h"
#include "SLPacker.hpp"
#include "DataProtocol.h"
#include "BindUtils.hpp"
#include "BindWidgets.hpp"
/// \brief Maximum number of object handlers
#define MAX_HANDLERS 16

/// \brief This command either adds the object to the canvas (screen) or refreshes the existing one.
#define BIND_ADD_OR_REFRESH_CMD 0

///\brief This command refreshes the existing object without moving or resizing it; it simply updates the data, such as text.
#define BIND_DATA_ONLY_CMD 6

///\brief This command removes the object from the canvas (screen).
#define BIND_REMOVE_CMD 1

///\brief This command disables the object.
#define BIND_DISABLE_CMD 2

///\brief This command enables the object.
#define BIND_ENABLE_CMD 3

///\brief This command hides the object.
#define BIND_HIDE_CMD 4

//!\brief This command restores the object's visibility.
#define BIND_VISIBLE_CMD 5

/**
 * @brief The Bind class provides a framework for creating interactive applications with BindCanvas.
 *
 * Bind is a versatile class that enables you to build applications that interact with BindCanvas.
 * It provides functions for binding and synchronizing various UI elements, including buttons,
 * knobs, switches, seekbars, joysticks, color pickers, terminals, and many more. You can use Bind to connect
 * your c++ programme to the BindCanvas screen, manage user interactions, and update UI elements in real time.
 *
 * <table style="text-align:center; margin-left:auto; margin-right:auto; font-style: italic">
 * <tr>
 * <td> \image html demo_app.png Sample app created by Bind
 * <td> \image html demo_app2.png Sample app created by Bind
 * </table>
 *
 * To use Bind effectively, you can define a setup callback function to configure the initial state
 * of your application, including screen setup and object synchronization. Bind also allows you to
 * set the communication device, such as a serial port, for data exchange with BindCanvas.
 *
 * @note To ensure smooth operation and responsiveness, regularly call the 'sync' function to
 * synchronize your Bind objects with the current state of the BindCanvas screen. Failing to
 * do so may result in missed events, such as button clicks or user interactions with your
 * UI elements.
 */
class Bind
{
public:
  // Constructors and setup functions...

  Bind()
  {
    setupCallback = NULL;
    // Allocate memory for an array of pointers to Bind objects
    switchObjects = new BindSwitch*[MAX_HANDLERS]; 
    buttonObjects = new BindButton*[MAX_HANDLERS]; 
    knobObjects = new BindKnob*[MAX_HANDLERS];
    seekBarObjects = new BindSeekBar*[MAX_HANDLERS];
    joystickObjects = new BindJoystick*[MAX_HANDLERS];
    colorPickerObjects = new BindColorPicker*[MAX_HANDLERS];
    textInputObjects = new BindTextInput*[MAX_HANDLERS];

    for (int i = 0; i < MAX_HANDLERS; ++i)
    {
      // Initialize each pointer to nullptr
      switchObjects[i] = nullptr; 
      buttonObjects[i] = nullptr;
      knobObjects[i] = nullptr;
      seekBarObjects[i] = nullptr;
      joystickObjects[i] = nullptr;
      colorPickerObjects[i] = nullptr;
      textInputObjects[i] = nullptr;
    }
  }

  /**
   * @brief Constructs a Bind object with a setup callback function.
   *
   * This constructor creates a Bind object and associates it with a setup callback function.
   * The setup callback is in charge of configuring the initial state of the Bind object,
   * which includes screen rotation and syncing all the objects. To put it simply,
   * 'setupCallback' is where you construct the application view.
   *
   * @param _setupCallback A pointer to the setup callback function that initializes the Bind screen.
   */
  Bind(void (*_setupCallback)(int16_t, int16_t)) : Bind()
  {
    setupCallback = _setupCallback;
  }

  /**
   * @brief Checks if the bind object is in a ready state.
   *
   * This function checks whether the Bind object is in a ready state,
   * which indicates whether it is connected or not.
   *
   * @return True if the object is ready; otherwise, false.
   */
  bool isReady()
  {
    return isInitialized;
  }

  /**
   * @brief Synchronizes a BindView object with the BindCanvas screen.
   * Same as sync(BindView *obj) but uses the object refrence to prevent common mistakes.
   */
  void sync(BindView &obj);

  /**
   * @brief Synchronizes the bind with the current state.
   *
   * This function synchronizes the Bind object with the current state by
   * reading data from the canvas and managing user interactions with Bind
   * views, such as button presses or connection requests.
   * In simpler terms, it reads the screen.
   * @attention To ensure smooth operation and prevent data loss or lag,
   * regularly run the following line of code. It's recommended to execute it
   * a few times per second, and faster is even better!
   * Try to achieve a rate more than 10Hz for optimal performance."
   * @note Not needed if using ESP32 as the sync function is called automatically.
   */
  void sync();

  /**
   * @brief Synchronizes the bind with the current state.
   * 
   * Similar to sync() but uses the buffer directly to be used in some cases 
   * that the regular stream object is not available. for example ble, wifi or
   * any other custom communication.
   * 
   * @param buffer a pointer to the buffer that contains the data to be processed.
   * @param size size of the buffer.
   */
  void sync(const uint8_t *buffer, size_t size);

  // Binding functions for UI elements...

  /**
   * @brief Initializes the Bind framework with communication and screen setup.
   *
   * This function serves a dual purpose:
   * 1. It configures the communication device for the Bind framework using a 'Stream' object.
   *    The 'stream' can represent any serial port, including hardware, software serial, or
   *    Bluetooth classic serial.
   * 2. It sets the screen setup callback. This callback function is automatically invoked by
   *    BindCanvas upon establishing a connection. It plays a crucial role in configuring the
   *    screen and ensuring that all screen objects are synchronized properly. You will receive
   *    two parameters: 'w' for screen width and 'h' for screen height in density-independent pixels (dp).
   *    These values allow you to maintain consistent object positioning  and size across various devices
   *    with different screen dimensions.
   *  @note For more information about density-independent pixels (dp) visit:
   *                  http://en.wikipedia.org/wiki/Device-independent_pixel
   *
   * @param stream A pointer to the 'Stream' object representing the communication device.
   * @param setupCallback A pointer to the screen setup callback function.
   *                     This function receives 'w' for width and 'h' for height.
   *                     It ensures consistent object positioning and size across devices.
   * @return Returns 'true' if initialization is successful; otherwise, returns 'false'.
   */
  bool init(Stream *stream, void (*setupCallback)(int16_t, int16_t));

  /**
   * @brief Initializes the Bind framework with communication and screen setup.
   *
   * This function serves a dual purpose:
   * 1. It configures the communication device for the Bind framework using a 'Stream' object.
   *    The 'stream' can represent any serial port, including hardware, software serial, or
   *    Bluetooth classic serial.
   * 2. It sets the screen setup callback. This callback function is automatically invoked by
   *    BindCanvas upon establishing a connection. It plays a crucial role in configuring the
   *    screen and ensuring that all screen objects are synchronized properly. You will receive
   *    two parameters: 'w' for screen width and 'h' for screen height in density-independent pixels (dp).
   *    These values allow you to maintain consistent object positioning  and size across various devices
   *    with different screen dimensions.
   *  @note For more information about density-independent pixels (dp) visit:
   *                  http://en.wikipedia.org/wiki/Device-independent_pixel
   *
   * @param stream A reference to the 'Stream' object representing the communication device.
   * @param setupCallback A reference to the screen setup callback function.
   *                      This function receives 'w' for width and 'h' for height.
   *                      It ensures consistent object positioning and size across devices.
   * @return Returns 'true' if initialization is successful; otherwise, returns 'false'.
   */
  bool init(Stream &stream, void (&setupCallback)(int16_t, int16_t));

  /**
   * @brief Synchronizes chart data of a BindChart object.
   *
   * This function synchronizes the chart data represented by a float value with a 'BindChart' object.
   * It takes two parameters: the 'chartData' to be synchronized and a
   * pointer to the 'BindChart' object, 'obj' so that it knows the data blong to which chart.
   * This function updates the chart data on the screen immediately.
   *
   * @param chartData The data to be synchronized with the 'BindChart' object.
   * @param obj A reference to the 'BindChart' object for data synchronization.
   */
  void sync(float chartData, BindChart &obj);

  /**
   * @brief Prints terminal data in a BindTerminal object.
   *
   * This function synchronizes terminal data, including text, text color, formatting options, and
   * terminal behavior, with a 'BindTerminal' object.
   *
   * @param str The text data to be printed in the 'BindTerminal' object.
   * @param textColor The color of the text.
   * @param autoScroll Determines whether auto-scrolling is enabled.
   * @param newLine Determines whether a new line is added after the text.
   * @param bold Indicates whether the text should be bold.
   * @param italic Indicates whether the text should be italic.
   * @param obj A reference to the 'BindTerminal' object for data synchronization.
   */
  void sync(const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic, BindTerminal &obj);

  /**
   * @brief Prints terminal data in a BindTerminal object.
   *
   * This function prints terminal data with this simple format:
   * textColor is white
   * autoScroll is enable
   * always adds a new line
   * No bold, no italic
   *
   * @param str The text data to be printed in the 'BindTerminal' object.
   * @param obj A pointer to the 'BindTerminal' object for data synchronization.
   */
  void sync(const char *str, BindTerminal &obj);

  void sync(BindSwitch &obj);
  void sync(BindButton &obj);
  void sync(BindKnob &obj);
  void sync(BindSeekBar &obj);
  void sync(BindJoystick &obj);
  void sync(BindColorPicker &obj);
  void sync(BindTextInput &obj);

private:
  // Private member variables and functions...
  uint8_t bufFrame[MAX_DATA_LENGHT];
  uint8_t frameTXBuffer[MAX_DATA_LENGHT + 6];
  int16_t valTmp1 = 0;
  int16_t valTmp2 = 0;
  int16_t valTmp3 = 0;
  int dataLen = 0;
  uint32_t lastMs = 0;
  uint32_t deltaMs = 0;
  BindSwitch** switchObjects;
  BindButton** buttonObjects;
  BindKnob** knobObjects;
  BindSeekBar** seekBarObjects;
  BindJoystick** joystickObjects;
  BindColorPicker** colorPickerObjects;
  BindTextInput** textInputObjects;
  DataParser dataParser;
  uint8_t buttonIndex = 1;
  uint8_t dialKnobIndex = 1;
  uint8_t switchIndex = 1;
  uint8_t seekBarIndex = 1;
  uint8_t joystickHandlerIndex = 1;
  uint8_t colorPickerHandlerIndex = 1;
  uint8_t textInputHandlerIndex = 1;
  bool isInitialized = false;
  void (*setupCallback)(int16_t, int16_t);
  void screenInit(int16_t w, int16_t h);
  Stream *bindStream = NULL;
  int updateScreen(uint8_t inp);
  void updateScreen(Stream *stream);
  int updateScreenInternal(uint8_t *dataFrame);
  void updateJoystick(uint8_t tag, int16_t valX, int16_t valY);
  void updateColorPicker(uint8_t tag, uint8_t r, uint8_t g, uint8_t b);
  void updateSeekBar(uint8_t tag, int16_t val);
  void knobChanged(int8_t tag, int val);
  void clickButton(uint8_t tag);
  void updateSwitch(uint8_t tag, bool val);
  void updateTextInput(uint8_t tag, const char *val, uint8_t length);
  void internalSync(BindView *obj);
};

#endif /* __BIND_H */
