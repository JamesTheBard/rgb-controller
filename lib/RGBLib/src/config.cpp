#include <Arduino.h>
#include <FastLED.h>
#include <FlashStorage.h>
#include <rgb_lib.h>

const int WRITTEN_SIGNATURE = 0x05319009;

FlashStorage(flash_config, RGBConfig);

void Controller::saveConfig() {
  config.signature = WRITTEN_SIGNATURE;
  config.brightness = FastLED.getBrightness();
  flash_config.write(config);
}

bool Controller::loadConfig() {
  config = flash_config.read();
  if (config.signature != WRITTEN_SIGNATURE) {
    return false;
  }
  FastLED.setBrightness(config.brightness);
  return true;
}

void Controller::initializeConfig() {
  FastLED.addLeds<NEOPIXEL, 14>(config.ports[0], NUM_OF_LEDS);
  FastLED.addLeds<NEOPIXEL, 15>(config.ports[1], NUM_OF_LEDS);
  FastLED.addLeds<NEOPIXEL, 16>(config.ports[2], NUM_OF_LEDS);
  FastLED.addLeds<NEOPIXEL, 17>(config.ports[3], NUM_OF_LEDS);
  FastLED.addLeds<NEOPIXEL, 18>(config.ports[4], NUM_OF_LEDS);
  FastLED.addLeds<NEOPIXEL, 19>(config.ports[5], NUM_OF_LEDS);

  if (!loadConfig()) {
    config.brightness = 50;
    for (unsigned int i = 0; i < NUM_OF_PORTS; i++) {
      for (unsigned int j = 0; j < NUM_OF_LEDS; j++) {
        config.ports[i][j] = CRGB::Black;
      }
    }
  }

  FastLED.show();
}
