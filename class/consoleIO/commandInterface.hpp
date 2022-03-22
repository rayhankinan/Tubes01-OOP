#ifndef COMMAND_INTERFACE_HPP
#define COMMAND_INTERFACE_HPP

#include "../exception/commandExceptionInterface.hpp"
#include "../crafting/craftingTableInterface.hpp"
#include "../inventory/inventoryInterface.hpp"
#include <string>
#include <iostream>
using namespace std;

class Command
{
protected:
  static int numOfCommand;

public:
  // DEFAULT CTOR
  Command();
  // getter
  int getNumOfCommand();
  // ini fungsi boleh ganti parameter sama return valuenya tergantung
  // fungsi yang berkaitan sama modul kalian masing-masing
  void SHOW(Inventory&, CraftingTable&);
  void DISCARD(Inventory&, string, int);
  void MOVE(Inventory&, string, int, string);
  void MOVE(CraftingTable&, Inventory&, string, int, string);
  void MOVE(CraftingTable&, Inventory&, string, int, vector<string>);
  void USE(Inventory&, string);
  void CRAFT(CraftingTable&, Inventory&);
  void EXPORT(Inventory&, string);
  void GIVE(Inventory&, string, int);
  void INVALID_COMMAND(string);
};

#endif