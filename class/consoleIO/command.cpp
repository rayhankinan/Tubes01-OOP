#include "commandInterface.hpp"
using namespace std;

int Command::numOfCommand = 0;

Command::Command()
{
  numOfCommand++;
}

int Command::getNumOfCommand()
{
  return Command::numOfCommand;
}

void Command::SHOW()
{
  cout << "BABI" << endl;
  Command::numOfCommand++;
}

void Command::DISCARD() { Command::numOfCommand++; }
void Command::MOVE() { Command::numOfCommand++; }
void Command::USE() { Command::numOfCommand++; }
void Command::CRAFT() { Command::numOfCommand++; }
void Command::EXPORT() { Command::numOfCommand++; }
void Command::GIVE() { Command::numOfCommand++; }

void Command::INVALID_COMMAND(string command)
{
  throw CommandException(command);
}