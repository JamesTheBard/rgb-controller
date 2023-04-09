#ifndef RGB_PARSER_H_
#define RGB_PARSER_H_

#include <Arduino.h>
#include <rgb_lib.h>

class Parser {
public:
  String command_buffer;
  Controller controller;
  void initializeCommands();
  void begin(int baud = 9600);
  void parseCommand();
  void parseConsole();

private:
  void error(String message, String prompt = "[ER]: ");
  void accept(String message, String prompt = "[OK]: ");
  void getVersion();
  bool validateData();
  void setPortColor();
  void setPortColorRange();
  void setPixelColor();
  void setGradient();
  void setOutput();
  void setDelayOnBoot();
  void dumpConfig();
};

#endif