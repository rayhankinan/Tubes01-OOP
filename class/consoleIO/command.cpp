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

void Command::SHOW(Inventory& inv)
{
  cout << "SHOW" << endl;
  Command::numOfCommand++;
  inv.show();
}

void Command::DISCARD(Inventory &inv, string slotID, int qty)
{
  cout << "DISCARD " << slotID << " " <<  qty << endl;
  Command::numOfCommand++;
  inv.discard(slotID, qty);
}

void Command::MOVE(Inventory &inv)
{
  cout << "MOVE" << endl;
  Command::numOfCommand++;
}
void Command::USE(Inventory &inv, string slotID)
{
  cout << "USE " << slotID << endl;
  Command::numOfCommand++;
  inv.use(slotID);
}
void Command::CRAFT()
{
  cout << "CRAFT" << endl;
  Command::numOfCommand++;
}
void Command::EXPORT(Inventory& inv, string fileName)
{
  cout << "EXPORT " << fileName << endl;
  Command::numOfCommand++;
  inv.EXPORT(fileName);
}

void Command::GIVE(Inventory &inv, string slotID, int qty)
{
  cout << "GIVE " << slotID << " " << qty << endl;
  Command::numOfCommand++;
}

void Command::INVALID_COMMAND(string command)
{
  throw CommandException(command);
}