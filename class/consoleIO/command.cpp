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
  cout << "SHOW" << endl;
  Command::numOfCommand++;
}

void Command::DISCARD()
{
  cout << "DISCARD" << endl;
  Command::numOfCommand++;
}
void Command::MOVE()
{
  cout << "MOVE" << endl;
  Command::numOfCommand++;
}
void Command::USE()
{
  cout << "USE" << endl;
  Command::numOfCommand++;
}
void Command::CRAFT()
{
  cout << "CRAFT" << endl;
  Command::numOfCommand++;
}
void Command::EXPORT()
{
  cout << "EXPORT" << endl;
  Command::numOfCommand++;
}
void Command::GIVE()
{
  cout << "GIVE" << endl;
  Command::numOfCommand++;
}

void Command::INVALID_COMMAND(string command)
{
  throw CommandException(command);
}