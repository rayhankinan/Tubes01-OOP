// HEADER
#include "./class/fileIO/fileIOInterface.hpp"
#include "./class/item/itemInterface.hpp"
#include "./class/item/nonToolInterface.hpp"
#include "./class/item/toolInterface.hpp"
#include "./class/fileIO/fileIO.cpp"
#include "./class/crafting/recipeInterface.hpp"
#include "./class/crafting/craftingTableInterface.hpp"
#include "./class/inventory/inventoryInterface.hpp"
#include "./class/collection/matrixInterface.hpp"
#include "./class/consoleIO/commandInterface.hpp"
#include "./class/consoleIO/consoleIOInterface.hpp"
// BIAR GAUSAH PAKE MAKE FILE TESTNYA
#include "./class/item/item.cpp"
#include "./class/item/nonTool.cpp"
#include "./class/item/tool.cpp"
#include "./class/exception/exception.cpp"
#include "./class/exception/itemException.cpp"
#include "./class/exception/nonToolException.cpp"
#include "./class/exception/toolException.cpp"
#include "./class/exception/matrixException.cpp"
#include "./class/exception/craftingException.cpp"
#include "./class/exception/commandException.cpp"
#include "./class/exception/fileException.cpp"
#include "./class/crafting/recipe.cpp"
#include "./class/crafting/craftingTable.cpp"
#include "./class/inventory/inventory.cpp"
#include "./class/consoleIO/command.cpp"
#include "./class/consoleIO/consoleIO.cpp"

using namespace std;

int main()
{
  FileIO FIO;
  ConsoleIO CIO;

  // display item
  FIO.displayNonTool();
  FIO.displayTool();
  // display recipe
  FIO.displayRecipe();

  //  start program
  CIO.start();
}
