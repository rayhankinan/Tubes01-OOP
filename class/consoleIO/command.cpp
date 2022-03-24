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
  Command::numOfCommand++;
  table.show();
  inv.show();
}

void Command::DISCARD(Inventory &inv, string slotID, int qty)
{
  Command::numOfCommand++;
  inv.discard(slotID, qty);
}

void Command::MOVE(Inventory &inv, string slotSrc, int qty, string slotTarget)
{
  Command::numOfCommand++;
  inv.moveInInventory(slotSrc, qty, slotTarget);
}

void Command::MOVE(CraftingTable &table, Inventory &inv, string slotCraft, int n, string slotInv)
{
  Command::numOfCommand++;
  table.move(inv, slotCraft, n, slotInv);
}

void Command::MOVE(CraftingTable &table, Inventory &inv, string slotInv, int n, vector<string> slotCrafts)
{
  Command::numOfCommand++;
  table.move(inv, slotInv, n, slotCrafts);
}

void Command::USE(Inventory &inv, string slotID)
{
  Command::numOfCommand++;
  inv.use(slotID);
}

void Command::CRAFT(CraftingTable &table, Inventory& inv)
{
  Command::numOfCommand++;
  table.craft(inv);
}

void Command::EXPORT(Inventory &inv, string fileName)
{
  Command::numOfCommand++;
  inv.EXPORT(fileName);
}


void Command::GIVE(Inventory &inv, string name, int qty)
{
  Command::numOfCommand++;
  inv.give(name, qty);
}

void Command::INVALID_COMMAND(string command)
{
  throw CommandException(command);
}
