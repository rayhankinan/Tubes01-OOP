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

int main() {

    FileIO FIO;
    vector<Recipe> r = FIO.listOfRecipe();
    Inventory inv = Inventory();

    try {
        NonTool* i = new NonTool(0, "SPRUCE_PLANK", "PLANK", 2);
        NonTool* j = new NonTool(0, "BIRCH_PLANK", "PLANK", 2);
        NonTool* k = new NonTool(0, "OAK_PLANK", "PLANK", 2);
        NonTool* l = new NonTool(0, "STICK", "-", 3);
        NonTool* m = new NonTool(0, "STICK", "-", 2);
        Tool* a = new Tool(0, "WOODEN_AXE", "-", 7);
        Tool* b = new Tool(0, "WOODEN_AXE", "-", 6);
        vector<Recipe> r = FIO.listOfRecipe();

        // check constructor
        CraftingTable table = CraftingTable();
        cout << "START CRAFTING TEST" << endl;

        // check setRecipes
        table.setRecipes(r);

        // check getter and setter
        cout << "Num of Recipes: " << table.getNumOfRecipes() << "/" << table.getMaxRecipes() << endl;
        cout << "C1 before: " << table.getElmt("C1") << endl;
        table.setElmt("C1", a);
        cout << "C1 after: " << table.getElmt("C1")->getName() << endl;

        // test tool draft
        table.addItem(2, 2, b);
        cout << endl << "BEFORE CRAFT" << endl;
        table.show();
        inv.show();
        table.craft(inv);
        cout << endl << "AFTER CRAFT" << endl;
        table.show();
        inv.show();

        // test move inv to craft
        cout << endl << "MOVE TOOL FROM INV TO CRAFT" << endl;
        vector<string> temp = { "C0" };
        table.move(inv, "I0", 1, temp);
        table.show();
        inv.show();

        // test move craft to inv
        cout << endl << "RETURN TOOL FROM CRAFT TO INV" << endl;
        table.move(inv, "C0", 1, "I0");
        table.show();
        inv.show();

        // check nontool craft + multi craft
        table.addItem(0, 0, i);
        table.addItem(0, 1, j);
        table.addItem(1, 1, k);
        table.addItem(2, 0, l);
        table.addItem(1, 0, m);

        cout << endl << "BEFORE 1st CRAFT" << endl;
        table.show();
        inv.show();
        table.craft(inv); // first craft

        cout << endl << "AFTER 1st CRAFT & BEFORE 2nd CRAFT" << endl;
        table.show();
        inv.show();
        table.craft(inv); // second craft

        cout << endl << "AFTER 2nd CRAFT & BEFORE 3rd CRAFT" << endl;
        table.show();
        inv.show();
        table.craft(inv); // third craft (harusnya ga lolos)

        // harusnya ga masuk sini
        cout << endl << "AFTER 3rd CRAFT" << endl;
        table.show();
        inv.show();
    }
    catch (Exception &e) {
        e.displayMessage();
    }
}