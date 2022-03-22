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

void Command::SHOW(Inventory &inv)
{
  cout << "SHOW" << endl;
  Command::numOfCommand++;
  inv.show();
}

void Command::DISCARD(Inventory &inv, string slotID, int qty)
{
  cout << "DISCARD " << slotID << " " << qty << endl;
  Command::numOfCommand++;
  try 
  {
    inv.discard(slotID, qty);
  }
  catch (InventoryException &IE)
  {
    IE.displayMessage();
  }
}

void Command::MOVE(Inventory &inv, string slotSrc, int qty, string slotTarget)
{
  cout << "MOVE" << " " << slotSrc << " " << qty << " " << slotTarget << endl;
  Command::numOfCommand++;
  try
  {
    inv.moveInInventory(slotSrc, qty, slotTarget);
  }
  catch (const Exception &e)
  {
    e.displayMessage();
  }
}


void Command::USE(Inventory &inv, string slotID)
{
  cout << "USE " << slotID << endl;
  Command::numOfCommand++;
  try
  {
    inv.use(slotID);
  }
  catch (const InventoryException &e)
  {
    e.displayMessage();
  }
}


void Command::CRAFT()
{
  cout << "CRAFT" << endl;
  Command::numOfCommand++;
}


void Command::EXPORT(Inventory &inv, string fileName)
{
  cout << "EXPORT " << fileName << endl;
  Command::numOfCommand++;
  inv.EXPORT(fileName);
}


void Command::GIVE(Inventory &inv, string name, int qty)
{
  cout << "GIVE " << name << " " << qty << endl;
  Command::numOfCommand++;
  try
  {
    inv.give(name, qty);
  }
  catch (const InventoryException &e)
  {
    e.displayMessage();
  }
}


void Command::INVALID_COMMAND(string command)
{
  throw CommandException(command);
}