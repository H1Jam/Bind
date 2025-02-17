
// Function to add knobs to the BindCanvas screen
void addKnob()
{
  // Configure and synchronize Knob 1
  knob1.x = 110;
  knob1.y = 130;
  knob1.dimSize = 150; // The dimensions(width = height) of the knob1.
  knob1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  knob1.minValue = -90;
  knob1.maxValue = 90;
  knob1.value = 0; // Initial value
  knob1.setlabel("Servo\n Deg");
  knob1.setCallback(knob1_changed);
  bind.sync(knob1);
}

// Callback for Knob 1 Value Change
void knob1_changed(int16_t val)
{
#ifndef USE_USB_SERIAL_FOR_BIND
  Serial.print("Knob 1 value has changed to: ");
  Serial.print(val);
  Serial.print("\t");
#endif
  myservo.write(90 + val);
}