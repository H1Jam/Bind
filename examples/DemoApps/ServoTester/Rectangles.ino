
/**
 * @brief Adds a rectangle to the display with specified properties.
 * Rectangles can be used as backgrounds, borders, or to group other UI elements.
 * 
 * This function configures and synchronizes a rectangle object with the given properties.
 * 
 * @param screenWidth The width of the screen.
 * @param screenHeight The height of the screen.
 */
void addRectangle1(int16_t screenWidth, int16_t scrennHeight) {
  // Configure and synchronize the rectangle
  rectangle1.x = screenWidth*0.05;
  rectangle1.y = 128;
  rectangle1.width = screenWidth *0.9;
  rectangle1.height = 250;
  rectangle1.cmdId = BIND_ADD_OR_REFRESH_CMD;
  rectangle1.fillColor = rgb(204, 230, 255);                 // Fill color of the rectangle (in RGB format)
  rectangle1.borderColor = RGB(100, 100, 100);  // Border color of the rectangle (in RGB format)
  rectangle1.borderWidth = 1;                   // Border width
  rectangle1.cornersRadius = 5;                 /// Radius of the rectangle's rounded corners.
  bind.sync(rectangle1);
}

