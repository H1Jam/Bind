#ifndef __BIND_H
#define __BIND_H
#include <stdint.h>
#include "Stream.h"
#include "DataProtocol.h"
#include "BindButtonHandler.hpp"
#include "BindDialKnobHandler.hpp"
#include "BindSwitchHandler.hpp"
#include "BindSeekBarHandler.hpp"
#include "BindJoystickHandler.hpp"
#include "BindColorPickerHandler.hpp"
#include "BindViewAutoTag.hpp"
#include "BindView.h"
#include "BindUtils.hpp"
#include "BindButton.hpp"
#include "BindKnob.hpp"
#include "BindTextLabel.hpp"
#include "BindWidgets.hpp"
// Maximum number of object handlers
#define MAX_HANDLERS 16
// This command either adds the object to the canvas (screen) or refreshes the existing one.
#define BIND_ADD_OR_REFRESH_CMD 0
// This command removes the object from the canvas (screen).
#define BIND_REMOVE_CMD 1
// This command disables the object.
#define BIND_DISABLE_CMD 2
// This command enables the object.
#define BIND_ENABLE_CMD 3
// This command hides the object.
#define BIND_HIDE_CMD 4
// This command restores the object's visibility.
#define BIND_VISIBLE_CMD 5
// This command refreshes the existing object without moving or resizing it; it simply updates the data, such as text.
#define BIND_DATA_ONLY_CMD 6

/**
 * @brief The Bind class provides a framework for creating interactive applications with BindCanvas.
 *
 * Bind is a versatile class that enables you to build applications that interact with BindCanvas.
 * It provides functions for binding and synchronizing various UI elements, including buttons,
 * knobs, switches, seekbars, joysticks, color pickers, and terminals. You can use Bind to connect
 * your application to the BindCanvas screen, manage user interactions, and update UI elements in real time.
 *
 * To use Bind effectively, you can define a setup callback function to configure the initial state
 * of your application, including screen setup and object synchronization. Bind also allows you to
 * set the communication device, such as a serial port, for data exchange with BindCanvas.
 *
 * @note To ensure smooth operation and responsiveness, regularly call the 'sync' function to
 * synchronize your Bind objects with the current state of the BindCanvas screen.
 */
class Bind
{
public:
  // Constructors and setup functions...

  Bind()
  {
    setupCallback = NULL;
    buttons = new ButtonHandler[MAX_HANDLERS];
    dialKnobHandlers = new DialKnobHandler[MAX_HANDLERS];
    switchHandlers = new SwitchHandler[MAX_HANDLERS];
    seekBarHandlers = new SeekBarHandler[MAX_HANDLERS];
    joystickHandlers = new JoystickHandler[MAX_HANDLERS];
    colorPickerHandlers = new ColorPickerHandler[MAX_HANDLERS];
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
    return init;
  }

  /**
   * @brief Synchronizes a BindView object with the BindCanvas screen.
   *
   * This function synchronizes a 'BindView' object, 'obj,' with the BindCanvas screen, ensuring that
   * the object reflects the most up-to-date data and appearance as intended.
   *
   * @param obj A pointer to the 'BindView' object (e.g. BindButton, BindSeekbar) to synchronize.
   */
  void sync(BindView *obj);

  /**
   * @brief Synchronizes the bind with the current state.
   *
   * This function synchronizes the Bind object with the current state by
   * reading data from the canvas and managing user interactions with Bind
   * views, such as button presses or connection requests.
   * In simpler terms, it reads the screen.
   * @attention: To ensure smooth operation and prevent data loss or lag,
   * regularly run the following line of code. It's recommended to execute it
   * a few times per second, and faster is even better!
   * Try to achieve a rate more than 10Hz for optimal performance."
   */
  void sync();

  // Binding functions for UI elements...

  /**
   * @brief Sets the communication device for the Bind framework.
   *
   * This function configures the communication device for the Bind framework. It takes a pointer
   * to a 'Stream' object, 'stream,' which represents the device used for data exchange with Bind.
   * This stream object can be any serial port including hardware or software serial or
   * blutooth classic serial port.
   *
   * @param stream A pointer to the 'Stream' object representing the communication device.
   */
  void setBindDevice(Stream *stream);

  /**
   * @brief set the the screen setup callback.
   *
   * Bind automatically invokes this callback function upon connecting to BindCanvas.
   * You should sync all the screen objects here.
   * You'll receive two integers as the parameters: 'w' for width and 'h' for height.
   * These values allow you to ensure that the objects' positioning and size remain
   * consistent across various devices with varying screen sizes."
   *
   * Note: You don't need to call this function manually!
   *
   * @param w The width of the screen in dp (Density-independent Pixels).
   * @param h The height of the screen in dp (Density-independent Pixels).
   */
  void bindScreenSetup(void (*setupCallback)(int16_t, int16_t));

  /**
   * @brief Binds a Button object to a click callback function.
   *
   * This function establishes a connection between a Button object and a click callback function.
   * It takes two parameters: a pointer to the 'BindButton' object, 'screenButton,' and a pointer
   * to a callback function, 'clickCallback,' which handles button click events.
   *
   * @param screenButton A pointer to the 'BindButton' object to bind.
   * @param clickCallback A pointer to the callback function that responds to button clicks.
   */
  void bindButton(BindButton *screenButton, void (*clickCallback)(void));

  /**
   * @brief Binds a Dial Knob object to a change callback function.
   *
   * This function establishes a connection between a Dial Knob object and a change callback function.
   * It takes two parameters: a pointer to the 'BindKnob' object, 'screenKnob,' and a pointer to a
   * callback function, 'changeCallback,' which handles changes in the dial knob's value.
   * @attention The changeCallback receives a 16-bit integer representing the knob angle,
   * and the range of values depends on the user's configuration for that knob.
   *
   * @param screenKnob A pointer to the 'BindKnob' object to bind.
   * @param changeCallback A pointer to the callback function that responds to dial knob value changes.
   */
  void bindDialKnob(BindKnob *screenKnob, void (*changeCallback)(int16_t));

  /**
   * @brief Binds a ON/OFF Switch object to a click callback function.
   *
   * This function establishes a connection between a Switch object and a click callback function.
   * It takes two parameters: a pointer to the 'BindSwitch' object, 'screenSwitch,' and a pointer
   * to a callback function, 'clickCallback,' which handles switch state changes.
   * @attention The clickCallback receives a boolean representing the state of the switch.
   *
   * @param screenSwitch A pointer to the 'BindSwitch' object to bind.
   * @param clickCallback A pointer to the callback function that responds to switch state changes.
   */
  void bindSwitch(BindSwitch *screenSwitch, void (*clickCallback)(bool));

  /**
   * @brief Binds a SeekBar object to a change callback function.
   *
   * This function establishes a connection between a SeekBar object and a change callback function.
   * It takes two parameters: a pointer to the 'BindSeekBar' object, 'screenSeekBar,' and a pointer
   * to a callback function, 'changeCallback,' which handles SeekBar value changes.
   * The callback receives an integer parameter representing the new value of the seekbar.
   * @attention The clickCallback receives a 16-bit integer representing the progress of
   * the seekbar, and the range of values depends on the user's configuration for that seekbar.
   *
   * @param screenSeekBar A pointer to the 'BindSeekBar' object to bind.
   * @param changeCallback A pointer to the callback function that responds to SeekBar changes.
   */
  void bindSeekBar(BindSeekBar *screenSeekBar, void (*changeCallback)(int16_t));

  /**
   * @brief Binds a Joystick object to a change callback function.
   *
   * This function establishes a connection between a Joystick object and a change callback function.
   * It takes two parameters: a pointer to the 'BindJoystick' object, 'screenJoystick,' and a pointer
   * to a callback function, 'changeCallback,' which handles changes in the joystick's position.
   * @attention The clickCallback receives two 16-bit integers representing
   * the X and Y axes of the joystick, with each axis ranging from -100 to 100.
   *
   * @param screenJoystick A pointer to the 'BindJoystick' object to bind.
   * @param changeCallback A pointer to the callback function that responds to joystick position changes.
   */
  void bindJoystick(BindJoystick *screenJoystick, void (*changeCallback)(int16_t, int16_t));

  /**
   * @brief Binds a Color Picker object to a click callback function.
   *
   * This function establishes a connection between a Color Picker object and a click callback function.
   * It takes two parameters: a pointer to the 'BindColorPicker' object, 'screenColorPicker,' and a pointer
   * to a callback function, 'clickCallback,' which handles color selection events.
   * @attention The clickCallback receives three 8-bit integers (ranging from 0 to 255)
   * that represent the Red, Green, and Blue elements of the selected color.
   *
   * @param screenColorPicker A pointer to the 'BindColorPicker' object to bind.
   * @param clickCallback A pointer to the callback function that responds to color selection events.
   */
  void bindColorPicker(BindColorPicker *screenColorPicker, void (*clickCallback)(uint8_t, uint8_t, uint8_t));

  /**
   * @brief Synchronizes chart data of a BindChart object.
   *
   * This function synchronizes the chart data represented by a float value with a 'BindChart' object.
   * It takes two parameters: the 'chartData' to be synchronized and a
   * pointer to the 'BindChart' object, 'obj' so that it knows the data blong to which chart.
   * This function updates the chart data on the screen immediately.
   *
   * @param chartData The data to be synchronized with the 'BindChart' object.
   * @param obj A pointer to the 'BindChart' object for data synchronization.
   */
  void syncChartData(float chartData, BindChart *obj);

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
   * @param obj A pointer to the 'BindTerminal' object for data synchronization.
   */
  void syncTerminalData(const char *str, int32_t textColor, bool autoScroll, bool newLine, bool bold, bool italic, BindTerminal *obj);

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
  void syncTerminalData(const char *str, BindTerminal *obj);

private:
  // Private member variables and functions...
  int16_t valTmp1 = 0;
  int16_t valTmp2 = 0;
  int16_t valTmp3 = 0;
  int dataLen = 0;
  DataParser dataParser;
  ButtonHandler *buttons;
  DialKnobHandler *dialKnobHandlers;
  SwitchHandler *switchHandlers;
  SeekBarHandler *seekBarHandlers;
  JoystickHandler *joystickHandlers;
  ColorPickerHandler *colorPickerHandlers;
  uint8_t buttonIndex = 1;
  uint8_t dialKnobIndex = 1;
  uint8_t switchIndex = 1;
  uint8_t seekBarIndex = 1;
  uint8_t joystickHandlerIndex = 1;
  uint8_t colorPickerHandlerIndex = 1;
  bool init = false;
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
};

#endif /* __BIND_H */
