#include <FastLED.h>
#include <FlashStorage.h>
#include <colorutils.h>
#include <rgb_lib.h>

void Controller::setPixel(int port, int pixel, CRGB color) {
  config.ports[port][pixel] = color;
}

void Controller::setPixel(int port, int pixel, String color) {
  setPixel(port, pixel, parseRGBString(color));
}

void Controller::setPixel(int port, String pixel, String color) {
  int int_pixel = getPixelFromString(pixel);
  setPixel(port, int_pixel, color);
}

void Controller::setColor(int port, CRGB color) {
  for (unsigned int i = 0; i < NUM_OF_LEDS; i++) {
    setPixel(port, i, color);
  }
}

void Controller::setColor(int port, String color) {
  setColor(port, parseRGBString(color));
}

void Controller::setRange(int port, int begin_pixel, int end_pixel,
                          CRGB color) {
  for (int i = begin_pixel; i < (1 + end_pixel); i++) {
    setPixel(port, i, color);
  }
}

void Controller::setRange(int port, int begin_pixel, int end_pixel,
                          String color) {
  setRange(port, begin_pixel, end_pixel, parseRGBString(color));
}

void Controller::setRange(int port, String pixel_range, String color) {
  int begin_pixel = getPixelFromString(pixel_range.substring(0, 2));
  int end_pixel = getPixelFromString(pixel_range.substring(2));
  setRange(port, begin_pixel, end_pixel, color);
}

void Controller::setBrightness(unsigned char brightness) {
  config.brightness = brightness;
  FastLED.setBrightness(brightness);
}

void Controller::setBrightness(String brightness) {
  char buffer[3];
  brightness.toCharArray(buffer, 3);
  setBrightness(strtol(buffer, 0, 16));
}

void Controller::show() { FastLED.show(); }

void Controller::setGradient(int port, int start_pixel, int end_pixel,
                             CRGB start_color, CRGB end_color) {
  fill_gradient_RGB(config.ports[port], start_pixel, start_color, end_pixel,
                    end_color);
};

void Controller::setGradient(int port, String pixel_range, String colors) {
  int start_pixel = getPixelFromString(pixel_range.substring(0, 2));
  int end_pixel = getPixelFromString(pixel_range.substring(2));
  int len = colors.length() >> 1;
  CRGB start_color = parseRGBString(colors.substring(0, len));
  CRGB end_color = parseRGBString(colors.substring(len));
  setGradient(port, start_pixel, end_pixel, start_color, end_color);
};