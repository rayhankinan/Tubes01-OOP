#ifndef COMMAND_EXCEPTION_INTERFACE_HPP
#define COMMAND_EXCEPTION_INTERFACE_HPP

#include "exceptionInterface.hpp"
#include <string>
using namespace std;

class CommandException : public Exception
{
protected:
  static int numOfCommandException;
  string command;

public:
  CommandException(int, string);              // user-defined ctor
  CommandException(const CommandException &); // cctor

  string getCommandException();
  static int getNumOfCommandException();
};

#endif