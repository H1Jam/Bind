
/**
 * @brief Sets the screen configuration.
 * 
 * This function configures the screen settings, including the screen orientation and background color.
 * The screen orientation can be set to either landscape or portrait mode.
 * The background color can be specified using the RGB values.
 * 
 */
void setScreenConfig() {
  // Configure screen settings
  BindCanvasSettings canvasSettings;

  // Screen orientation is unspecified, allowing the system to decide.
  //canvasSettings.screenOrientation = SCREEN_ORIENTATION_UNSPECIFIED;

  // Landscape mode: screen width > height.
  // canvasSettings.screenOrientation = SCREEN_ORIENTATION_LANDSCAPE;

  // Portrait mode: screen height > width.
  canvasSettings.screenOrientation = SCREEN_ORIENTATION_PORTRAIT;
  canvasSettings.backColor = rgb(0, 163, 204);
  // Or use RGB(R:0-255, G:0-255, B0-255).
  // For example:
  // canvasSettings.backColor = RGB(100,255,40);
  bind.sync(canvasSettings);
}

