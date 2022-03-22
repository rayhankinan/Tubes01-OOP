#ifndef CONSOLE_IO_INTERFACE_HPP
#define CONSOLE_IO_INTERFACE_HPP

#include "commandInterface.hpp"

#include <string>
#include <iostream>
using namespace std;

class ConsoleIO : public Command
{
private:
  string command;

public:
  // default ctor
  ConsoleIO();
  // user defined ctor
  ConsoleIO(string);
  // cctor
  ConsoleIO(const ConsoleIO &CI);
  // getter
  string getCommand();
  // setter
  void setCommand(string);
  // override function for CLI-based command
  void setCommand();
  // main logic
  void start();
};

#endif
