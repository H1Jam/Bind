void addButton1() {
  // Syncing Button 1:
  // Set the Button's position on the screen.
  // Tip: You can use the grid view mode in BindCanvas app to determine the x and y coordinates
  // and replace these numbers with the grid values for precise positioning.
  button1.x = 135;
  button1.y = 300;
  // Set the Button's text label.
  button1.setLabel("Center");     // button label
  button1.fontSize = 23;      // The dimensions(width and height) of the Button on the screen are determined relative to the Font size.
  button1.textColor = BLACK;  // Text color
  button1.backColor = GREEN;  // button color
  // Specify the command to either add the object to the BindCanvas or refresh the existing one.
  button1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  button1.setCallback(button1_pressed);
  // Synchronize the button1 object with BindCanvas.
  bind.sync(button1);
}

void button1_pressed() {
  myservo.write(90);
#ifndef USE_USB_SERIAL_FOR_BIND
  Serial.println("Button 1 has been pressed!");
#endif
  knob1.value = 0;  // Initial value
  knob1.cmdId = BIND_DATA_ONLY_CMD;
  bind.sync(knob1);
}

