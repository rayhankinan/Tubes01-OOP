#ifndef CONSOLE_INPUT_INTERFACE_HPP
#define CONSOLE_INPUT_INTERFACE_HPP

#include <string>
#include <iostream>
using namespace std;

class ConsoleInput
{
private:
  string command;

public:
  //default ctor
  ConsoleInput();
  // user defined ctor
  ConsoleInput(string);
  // cctor
  ConsoleInput(const ConsoleInput& CI);
  // getter
  string getCommand();
  // setter
  void setCommand(string);
  // override function for CLI-based command
  void setCommand();
};

#endif