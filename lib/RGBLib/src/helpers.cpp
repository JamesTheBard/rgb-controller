#include <Arduino.h>
#include <rgb_lib.h>

CRGB Controller::parseRGBString(String color) {
  bool isLong = !(color.length() & 1);
  char char_buffer[3];
  int colors[3];

  for (int i = 0; i < 3; i++) {
    color.substring(i * (isLong + 1), (i + 1) * (isLong + 1))
        .toCharArray(char_buffer, 3);
    colors[i] = strtol(char_buffer, 0, 16);
    colors[i] *= isLong ? 1 : 0x11;
  }
  return CRGB(colors[0], colors[1], colors[2]);
}

int Controller::getPixelFromString(String pixel) {
  if (pixel.length() > 2) {
    return 0;
  }
  char buffer[3];
  pixel.toCharArray(buffer, 3);
  return strtol(buffer, 0, 16);
}
