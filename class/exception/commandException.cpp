#include "commandExceptionInterface.hpp"
#include <string>
using namespace std;

int CommandException::numOfCommandException = 0;

CommandException::CommandException(string _command) : Exception(ID)
{
  this->command = _command;
  CommandException::numOfCommandException++;
}

CommandException::CommandException(const CommandException &CE) : Exception(CE.ID)
{
  this->command = CE.command;
  CommandException::numOfCommandException++;
}

string CommandException::getCommandException()
{
  return this->command;
}

int CommandException::getNumOfCommandException()
{
  return CommandException::numOfCommandException;
}

void CommandException::displayMessage() const
{
  cout << "Command '" << this->command << "' invalid." << endl;
}
