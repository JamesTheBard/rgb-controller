#include <Arduino.h>
#include <rgb_parser.h>

Parser cmd_parser;

void setup() {
  cmd_parser.begin();
  delay(3000);
  cmd_parser.controller.show();
}

void loop() {
  cmd_parser.parseConsole();
  delay(10);
}
