#include <Arduino.h>
#include <rgb_parser.h>

Parser cmd_parser;

void setup() { cmd_parser.begin(); }

void loop() {
  cmd_parser.parseConsole();
  delay(10);
}
