#include "./class/fileIO/fileIOInterface.hpp"
#include "./class/consoleIO/consoleIOInterface.hpp"
#include "./class/inventory/InventoryInterface.hpp"

using namespace std;

int main() {
  FileIO FIO;
  ConsoleIO CIO;
  string FileName;

  Inventory INV;
  // INV.show();  

  FIO.displayTool();
  FIO.displayNonTool();
  // FIO.displayRecipe();
  
  // check for how many test case is needed
  int countFile =  FIO.countOfTestFile(FIO.getTestsPath());

  // USING MAKE ALL
  for (int i = 0; i < countFile; i++) {
    CIO.start();
  }

  // DIFFERENT WAY OF TESTING
  // string test1 = "1.in";
  // string test2 = "2.in";
  // FIO.start(test1); 
  // FIO.start(test2);
}