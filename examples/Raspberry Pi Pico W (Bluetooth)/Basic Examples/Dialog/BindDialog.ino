// Atention: For Raspberry Pi Pico W, this library needs Bluetooth enabled.
// Go to 'Tools->IP/Bluetooth Stack' menu in the IDE and select 'x + Bluetooth'.
#include "Bind.h"
#include <SerialBT.h>

Bind bind;

// Create different types of dialog boxes
BindDialog confirmDialog(NO_INPUT_TEXT);   // Regular dialog with no input
BindDialog nameDialog(TEXT_INPUT);         // Dialog with text input
BindDialog passwordDialog(PASSWORD_INPUT); // Dialog with password input
BindButton showConfirmBtn;                 // Button to show confirm dialog
BindButton showInputBtn;                   // Button to show text input dialog
BindButton showPasswordBtn;                // Button to show password dialog

// Store the entered name and password for later use
char enteredName[32] = "";
char enteredPassword[32] = "";

/**
 * @brief Callback for the confirmation dialog (no text input)
 * 
 * This function is called when the user interacts with the confirmation dialog.
 * The result parameter indicates which button was pressed.
 * 
 * @param result true if primary button was pressed, false if secondary button was pressed
 */
void confirmDialogCallback(bool result) {
  Serial.print("Confirmation dialog: ");
  if (result) {
    Serial.println("User confirmed (OK)");
  } else {
    Serial.println("User cancelled");
  }
}

/**
 * @brief Callback for the text input dialog
 * 
 * This function is called when the user interacts with the text input dialog.
 * It receives both the result (OK/Cancel) and the text the user entered.
 * 
 * @param result true if primary button was pressed, false if secondary button was pressed
 * @param text the text entered by the user
 */
void nameDialogCallback(bool result, const char *text) {
  if (result) {
    Serial.print("Name entered: ");
    Serial.println(text);
    strcpy(enteredName, text);
  } else {
    Serial.println("Name input cancelled");
  }
}

/**
 * @brief Callback for the password dialog
 * 
 * This function is called when the user interacts with the password dialog.
 * It receives both the result (OK/Cancel) and the password the user entered.
 * 
 * @param result true if primary button was pressed, false if secondary button was pressed
 * @param text the password entered by the user
 */
void passwordDialogCallback(bool result, const char *text) {
  if (result) {
    Serial.print("Password entered: ");
    Serial.println(text); // In a real app, you'd avoid printing passwords
    strcpy(enteredPassword, text);
    
    // Example of checking a password
    if (strcmp(text, "1234") == 0) {
      // Password is correct, show a confirmation
      confirmDialog.setTitle("Success");
      confirmDialog.setMessage("Password is correct!");
      confirmDialog.setPrimaryButton("OK");
      confirmDialog.singleButton = true;  // Only show the OK button
      bind.sync(confirmDialog);
    } else {
      // Password is incorrect, show an error
      confirmDialog.setTitle("Error");
      confirmDialog.setMessage("Incorrect password!");
      confirmDialog.setPrimaryButton("Try Again");
      confirmDialog.singleButton = true;
      bind.sync(confirmDialog);
    }
  } else {
    Serial.println("Password input cancelled");
  }
}

/**
 * @brief Callback for the "Show Confirm" button
 */
void onShowConfirmClick() {
  Serial.println("Showing confirmation dialog");
  bind.sync(confirmDialog);
}

/**
 * @brief Callback for the "Show Input" button
 */
void onShowInputClick() {
  Serial.println("Showing text input dialog");
  bind.sync(nameDialog);
}

/**
 * @brief Callback for the "Show Password" button
 */
void onShowPasswordClick() {
  Serial.println("Showing password dialog");
  bind.sync(passwordDialog);
}

/**
 * @brief Adds buttons to the screen to trigger different dialogs
 */
void addButtons() {
  // Button to show confirmation dialog
  showConfirmBtn.x = 30;
  showConfirmBtn.y = 100;
  showConfirmBtn.fontSize = 16;
  showConfirmBtn.backColor = BLUE;
  showConfirmBtn.setLabel("Show Confirm Dialog");
  showConfirmBtn.cmdId = BIND_ADD_OR_REFRESH_CMD;
  showConfirmBtn.setCallback(onShowConfirmClick);
  bind.sync(showConfirmBtn);

  // Button to show text input dialog
  showInputBtn.x = 30;
  showInputBtn.y = 160;
  showInputBtn.fontSize = 16;
  showInputBtn.backColor = GREEN;
  showInputBtn.setLabel("Show Name Dialog");
  showInputBtn.cmdId = BIND_ADD_OR_REFRESH_CMD;
  showInputBtn.setCallback(onShowInputClick);
  bind.sync(showInputBtn);

  // Button to show password dialog
  showPasswordBtn.x = 30;
  showPasswordBtn.y = 220;
  showPasswordBtn.fontSize = 16;
  showPasswordBtn.backColor = CYAN;
  showPasswordBtn.textColor = BLACK;
  showPasswordBtn.setLabel("Show Password Dialog");
  showPasswordBtn.cmdId = BIND_ADD_OR_REFRESH_CMD;
  showPasswordBtn.setCallback(onShowPasswordClick);
  bind.sync(showPasswordBtn);
}

/**
 * @brief Screen Setup Callback for BindCanvas
 *
 * This callback is automatically invoked by BindCanvas upon establishing a connection.
 */
void onConnection(int16_t width, int16_t height) {
  Serial.print("Connected. Screen size: ");
  Serial.print(width);
  Serial.print("x");
  Serial.println(height);
  
  // Add buttons to trigger dialogs
  addButtons();
}

void setup() {
  Serial.begin(115200);
  
  // Set up the confirmation dialog
  confirmDialog.setTitle("Confirmation");
  confirmDialog.setMessage("Are you sure you want to proceed?");
  confirmDialog.setPrimaryButton("Yes");
  confirmDialog.setSecondaryButton("No");
  confirmDialog.setCallback(confirmDialogCallback);
  
  // Set up the name input dialog
  nameDialog.setTitle("Your Name");
  nameDialog.setMessage("Please enter your name:");
  nameDialog.setPrimaryButton("Submit");
  nameDialog.setSecondaryButton("Cancel");
  nameDialog.setCallback(nameDialogCallback);
  
  // Set up the password dialog
  passwordDialog.setTitle("Password Required");
  passwordDialog.setMessage("Enter your password (hint: 1234)");
  passwordDialog.setPrimaryButton("Login");
  passwordDialog.setSecondaryButton("Cancel");
  passwordDialog.setCallback(passwordDialogCallback);
  
  // Initialize the Bind object and specify the communication method  and callback function (onConnection).
  SerialBT.begin();
  bind.init(SerialBT, onConnection);
  
}

void loop() {
  // Synchronize Bind UI Events (Not required on ESP32 when using BindOverBLE or BindOverWifi)
  // Callin bind.sync() regularly is crucial to handle of user inputs and touch events.
  // It's recommended to call bind.sync() a couple of times per second, but the faster, the better!
  bind.sync();
  
  // Optional: add any processing you need to do here
  delay(10);
}
