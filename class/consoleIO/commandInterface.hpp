#ifndef COMMAND_INTERFACE_HPP
#define COMMAND_INTERFACE_HPP

#include "../exception/commandExceptionInterface.hpp"
#include <string>
#include <iostream>
using namespace std;

class Command
{
protected:
  static int numOfCommand;

public:
  // DEFAULT CTOR
  Command();
  // getter
  int getNumOfCommand();
  // ini fungsi boleh ganti parameter sama return valuenya tergantung
  // fungsi yang berkaitan sama modul kalian masing-masing
  void SHOW();
  void DISCARD();
  void MOVE();
  void USE();
  void CRAFT();
  void EXPORT();
  void GIVE();
  void INVALID_COMMAND(string);
};

#endif