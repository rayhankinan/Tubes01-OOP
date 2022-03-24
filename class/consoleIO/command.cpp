#include "commandInterface.hpp"
using namespace std;

int Command::numOfCommand = 0;

Command::Command()
{
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
  inv.discard(slotID, qty);
}

void Command::MOVE(Inventory &inv, string slotSrc, int qty, string slotTarget)
{
  cout << "MOVE" << " " << slotSrc << " " << qty << " " << slotTarget << endl;
  Command::numOfCommand++;
  inv.moveInInventory(slotSrc, qty, slotTarget);
}

void Command::MOVE(CraftingTable &table, Inventory &inv, string slotCraft, int n, string slotInv)
{
  cout << "MOVE" << " " << slotCraft << " " << n << " " << slotInv << endl;
  Command::numOfCommand++;
  table.move(inv, slotCraft, n, slotInv);
}

void Command::MOVE(CraftingTable &table, Inventory &inv, string slotInv, int n, vector<string> slotCrafts)
{
  cout << "MOVE" << " " << slotInv << " " << n << " ";
  for (int i = 0; i < n; i++) {
    cout << slotCrafts[i] << " ";
  } 
  cout << endl;
  table.move(inv, slotInv, n, slotCrafts);
}

void Command::USE(Inventory &inv, string slotID)
{
  cout << "USE " << slotID << endl;
  Command::numOfCommand++;
  inv.use(slotID);
}

void Command::CRAFT(CraftingTable &table, Inventory& inv)
{
  cout << "CRAFT" << endl;
  Command::numOfCommand++;
  table.craft(inv);
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
  inv.give(name, qty);
}

void Command::INVALID_COMMAND(string command)
{
  throw CommandException(command);
}
