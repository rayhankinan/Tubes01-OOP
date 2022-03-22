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
#include "./class/exception/inventoryException.cpp"
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

  try {
    vector<Recipe> r = FIO.listOfRecipe();
    CraftingTable table = CraftingTable(r.size());
    table.setRecipes(r);

    // // test nontool
    // NonTool* i = new NonTool(0, "OAK_PLANK", "PLANK", 2);
    // NonTool* j = new NonTool(0, "SPRUCE_PLANK", "PLANK", 2);
    // NonTool* k = new NonTool(0, "BIRCH_PLANK", "PLANK", 2);
    // NonTool* l = new NonTool(0, "STICK", "-", 3);
    // NonTool* m = new NonTool(0, "STICK", "-", 2);
    // table.addItem(0, 0, i);
    // table.addItem(0, 1, j);
    // table.addItem(1, 1, k);
    // table.addItem(2, 0, l);
    // table.addItem(1, 0, m);

    // test tool
    Tool* a = new Tool(0, "WOODEN_AXE", "-", 7);
    Tool* b = new Tool(0, "WOODEN_AXE", "-", 6);
    table.addItem(0, 1, a);
    table.addItem(2, 2, b);

    // display 
    cout << "BEFORE" << endl;
    table.show();
    cout << endl << "AFTER CRAFT" << endl;
    table.craft();
    table.show();
    cout << endl << "AFTER SECOND CRAFT" << endl;
    table.craft();
    table.show();

  }
  catch (CraftingException e) {
    e.displayMessage();
  }

  //  start program
  CIO.start();
}
