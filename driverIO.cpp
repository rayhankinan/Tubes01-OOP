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
  // file IO
  FileIO FIO;

  // display item
  FIO.displayNonTool();
  FIO.displayTool();
  // display recipe
  FIO.displayRecipe();

  // get config path
  cout << "config path: " << FIO.getConfigPath() << endl;
  cout << "tests path : " << FIO.getTestsPath() << endl;

  // get all line from a file
  try
  {
    string filePath = FIO.getTestsPath() + "/1.in";
    vector<vector<string>> testFile = FIO.vectorOfWords(filePath);

    // print all string from testFile
    for (int i = 0; i < testFile.size(); i++)
    {
      for (int j = 0; j < testFile[i].size(); j++)
      {
        cout << testFile[i][j] << " ";
      }
      cout << endl;
    }
  }
  catch (FileException &FE)
  {
    FE.displayMessage();
  }

  // get all line from a non existent file
  try
  {
    string errorPath = FIO.getTestsPath() + "/0.in";
    vector<vector<string>> testerror = FIO.vectorOfWords(errorPath);
  }
  catch (FileException &FE)
  {
    FE.displayMessage();
  }

  // command and console IO
  ConsoleIO CIO;
  Inventory Inv = Inventory();
  CraftingTable Craft = CraftingTable();

  // manually set command
  CIO.setCommand("SHOW");
  CIO.SHOW(Inv, Craft);

  // print num of command used (should be 1)
  cout << "Number of Command used: " << CIO.getNumOfCommand() << endl;

  // override to ask from console
  cout << "Set your command: ";
  CIO.setCommand();
  // print command
  cout << "Command from user: " << CIO.getCommand() << endl;


  //  start program
  cout << endl;
  cout << "start of the program" << endl;
  cout << "type EXIT to close the program" << endl;
  CIO.start();
  cout << "you reached the end of the program" << endl;
  cout << "Number of valid Command used: " << CIO.getNumOfCommand() << endl;
}
