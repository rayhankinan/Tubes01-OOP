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
#include "./class/exception/fileException.cpp"
#include "./class/crafting/recipe.cpp"
#include "./class/crafting/craftingTable.cpp"
#include "./class/inventory/inventory.cpp"

using namespace std;

int main(){

    Inventory INV;
    try{
        cout << "START INVENTORY TEST" << endl;
        INV.show();
        cout << "GIVE OAK_PLANK 2 and GIVE BIRCH_PLANK 2" << endl;
        INV.give("OAK_PLANK", 2);
        INV.give("BIRCH_PLANK", 2);
        INV.show();
        cout << "TAKE OAK_PLANK 1 and TAKE BIRCH_PLANK 1" << endl;
        INV.discard("I0", 1);
        INV.discard("I1", 1);
        INV.show();
        cout << "GIVE DIAMOND_SWORD 1" << endl;
        INV.give("DIAMOND_SWORD", 1);
        INV.show();
        cout << "USE DIAMOND_SWORD" << endl;
        INV.use("I2");
        INV.show();
        cout << "GIVE OAK_PLANK 1" << endl;
        INV.give("OAK_PLANK", 1);
        INV.show();
        cout << "MOVE OAK_PLANK to SLOT I26" << endl;
        INV.moveInInventory("I0",1, "I26");
        INV.show();
    }
    catch (Exception &e){
        e.displayMessage();
    }
}