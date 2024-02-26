
/**
 * @brief Adds a text label to the user interface.
 * 
 * This function sets the position, label text, color, font size, and command ID of the text label.
 * It then synchronizes the changes with the bind object.
 */
void addtTextlabel() {
  textLabel1.x = 50;
  textLabel1.y = 80;
  textLabel1.setlabel("Servo Tester");
  textLabel1.color = WHITE;
  textLabel1.fontSize = 36;
  textLabel1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  bind.sync(textLabel1);
}