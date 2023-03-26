#ifndef RGB_LIB_H_
#define RGB_LIB_H_

#include <FastLED.h>
#include <FlashStorage.h>

const unsigned int NUM_OF_PORTS = 6;
const unsigned int NUM_OF_LEDS = 256;

typedef struct {
  int signature;
  unsigned char brightness;
  CRGB ports[NUM_OF_PORTS][NUM_OF_LEDS];
} RGBConfig;

class Controller {
public:
  bool loadConfig();
  void initializeConfig();
  void saveConfig();
  void setColor(int port, CRGB color);
  void setColor(int port, String color);
  void setPixel(int port, int pixel, CRGB color);
  void setPixel(int port, int pixel, String color);
  void setPixel(int port, String pixel, String color);
  void setRange(int port, int begin_pixel, int end_pixel, CRGB color);
  void setRange(int port, int begin_pixel, int end_pixel, String color);
  void setRange(int port, String pixel_range, String color);
  void setBrightness(unsigned char brightness);
  void setBrightness(String brightness);
  void setGradient(int port, int start_pixel, int end_pixel, CRGB start_color,
                   CRGB end_color);
  void setGradient(int port, String pixel_range, String colors);
  void show();

private:
  RGBConfig config;
  CRGB parseRGBString(String color);
  int getPixelFromString(String pixel);
};

#endif