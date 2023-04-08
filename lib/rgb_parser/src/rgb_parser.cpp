#include <Arduino.h>
#include <map>
#include <rgb_parser.h>

String valid_data_values = "abcdef0123456789";
String valid_command_values =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

char version[] = "1.0.1";

bool valid_command = true;
bool verbose_output = true;

typedef enum {
  Undefined,
  SetPortColor,
  SetPortColorRange,
  SetPixelColor,
  SetGradient,
  SetBrightness,
  Show,
  SaveConfig,
  LoadConfig,
  SetOutput,
  GetVersion
} RGBCommands;

std::map<String, int> commandMap;

void Parser::initializeCommands() {
  commandMap["all"] = SetPortColor;
  commandMap["rng"] = SetPortColorRange;
  commandMap["pix"] = SetPixelColor;
  commandMap["gra"] = SetGradient;
  commandMap["bri"] = SetBrightness;
  commandMap["sho"] = Show;
  commandMap["sav"] = SaveConfig;
  commandMap["loa"] = LoadConfig;
  commandMap["log"] = SetOutput;
  commandMap["ver"] = GetVersion;
}

void Parser::begin(int baud) {
  controller.initializeConfig();
  initializeCommands();
  Serial.begin(baud);
}

void Parser::parseConsole() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
    case ';':
      parseCommand();
      break;
    case '\n':
      if (!verbose_output) break;
      Serial.print("[BU]: ");
      Serial.println(command_buffer);
      break;
    default:
      if (valid_command_values.indexOf(c) == -1)
        break;
      command_buffer += c;
    }
  }
}

bool Parser::validateData() {
  int len = command_buffer.length();
  for (int i = 3; i < len; i++) {
    if (valid_data_values.indexOf(command_buffer.charAt(i)) == -1) {
      return false;
    }
  }
  return true;
}

void Parser::setPortColor() {
  int len = command_buffer.length();
  if (len != 7 && len != 10) {
    error("invalid length");
    return;
  }
  int port = command_buffer.substring(3, 4).toInt();
  String color = command_buffer.substring(4);
  controller.setColor(port, color);
}

void Parser::setPortColorRange() {
  int len = command_buffer.length();
  if (len != 11 && len != 14) {
    error("invalid length");
    return;
  }
  int port = command_buffer.substring(3, 4).toInt();
  String range = command_buffer.substring(4, 8);
  String color = command_buffer.substring(8);
  controller.setRange(port, range, color);
}

void Parser::setPixelColor() {
  int len = command_buffer.length();
  if (len != 9 && len != 12) {
    error("invalid length");
    return;
  }
  int port = command_buffer.substring(3, 4).toInt();
  String pixel = command_buffer.substring(4, 6);
  String color = command_buffer.substring(6);
  controller.setPixel(port, pixel, color);
}

void Parser::setGradient() {
  int len = command_buffer.length();
  if (len != 14 && len != 20) {
    error("invalid length");
    return;
  }
  int port = command_buffer.substring(3, 4).toInt();
  String range = command_buffer.substring(4, 8);
  String colors = command_buffer.substring(8);
  controller.setGradient(port, range, colors);
}

void Parser::getVersion() {
  if (command_buffer.length() != 3) {
    error("invalid length");
    return;
  }
  Serial.print(">>>> Version " );
  Serial.println(version);
}

void Parser::parseCommand() {
  valid_command = true;
  command_buffer.toLowerCase();
  if (!validateData()) {
    error("invalid characters in string");
    command_buffer = "";
    return;
  }
  String command = command_buffer.substring(0, 3);
  int len = command_buffer.length();

  switch (commandMap[command]) {
  case GetVersion:
    getVersion();
    break;
  case SetPortColor:
    setPortColor();
    break;
  case SetPortColorRange:
    setPortColorRange();
    break;
  case SetPixelColor:
    setPixelColor();
    break;
  case SetGradient:
    setGradient();
    break;
  case SetBrightness:
    if (len != 5) {
      error("invalid length");
      break;
    }
    controller.setBrightness(command_buffer.substring(3));
    break;
  case Show:
    if (len != 3) {
      error("invalid length");
      break;
    }
    controller.show();
    break;
  case SaveConfig:
    if (len != 3) {
      error("invalid length");
      break;
    }
    controller.saveConfig();
    break;
  case LoadConfig:
    if (len != 3) {
      error("invalid length");
      break;
    }
    controller.loadConfig();
    break;
  case SetOutput:
    setOutput();
    break;
  }

  if (commandMap[command] == Undefined) {
    error("unknown command");
  }
  if (valid_command) {
    accept(command_buffer);
  }
  command_buffer = "";
}

void Parser::setOutput() {
  int len = command_buffer.length();
  if (len != 4) {
    error("invalid length");
    return;
  }
  int level = command_buffer.substring(3).toInt();
  switch (level) {
  case 0:
    verbose_output = false;
    return;
  case 1:
    verbose_output = true;
    return;
  default:
    error("invalid verbose level");
  }
}

void Parser::error(String message, String prompt) {
  valid_command = false;
  if (!verbose_output) {
    Serial.print('!');
    return;
  }
  Serial.print(prompt);
  Serial.print(message);
  Serial.print(" <");
  Serial.print(command_buffer);
  Serial.println(">");
}

void Parser::accept(String error_message, String prompt) {
  if (!verbose_output) {
    Serial.print('.');
    return;
  }
  Serial.print("[OK]: ");
  Serial.println(command_buffer);
}
