#include "consoleInputInterface.hpp"

ConsoleInput::ConsoleInput(){
  this->command = "";
}

ConsoleInput::ConsoleInput(string command){
  this->command = command;
}

ConsoleInput::ConsoleInput(const ConsoleInput& CI){
  this->command = CI.command;
}

string ConsoleInput::getCommand(){
  return this->command;
}

void ConsoleInput::setCommand(string command){
  this->command = command;
}

void ConsoleInput::setCommand(){
  string command;
  cin >> command;
  this->command = command;
}