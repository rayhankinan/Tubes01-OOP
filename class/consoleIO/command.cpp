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

void Command::SHOW(Inventory &inv, CraftingTable& table)
{
  cout << "SHOW" << endl;
  Command::numOfCommand++;
  table.show();
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

void Command::MOVE(CraftingTable &table, Inventory &inv, string slotCraft, int n, string slotInv)
{
  cout << "MOVE" << " " << slotCraft << " " << n << " " << slotInv << endl;
  Command::numOfCommand++;
  try
  {
    table.move(inv, slotCraft, n, slotInv);
  }
  catch (const Exception &e)
  {
    e.displayMessage();
  }
}

void Command::MOVE(CraftingTable &table, Inventory &inv, string slotInv, int n, vector<string> slotCrafts)
{
  cout << "MOVE" << " " << slotInv << " " << n << " ";
  for (int i = 0; i < n; i++) {
    cout << slotCrafts[i] << " ";
  } 
  cout << endl;
  Command::numOfCommand++;
  try
  {
    table.move(inv, slotInv, n, slotCrafts);
  }
  catch (const Exception &e) {
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

void Command::CRAFT(CraftingTable &table, Inventory& inv)
{
  cout << "CRAFT" << endl;
  Command::numOfCommand++;
  try
  {
    table.craft(inv);
  }
  catch (const Exception &e) {
    e.displayMessage();
  }
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
