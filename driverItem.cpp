// HEADER
#include "./class/item/itemInterface.hpp"
#include "./class/item/nonToolInterface.hpp"
#include "./class/item/toolInterface.hpp"
// BIAR GAUSAH PAKE MAKE FILE TESTNYA
#include "./class/item/item.cpp"
#include "./class/item/nonTool.cpp"
#include "./class/item/tool.cpp"
#include "./class/exception/exception.cpp"
#include "./class/exception/itemException.cpp"
#include "./class/exception/nonToolException.cpp"
#include "./class/exception/toolException.cpp"

int main() {

    try {
        Item *Oak_Log1 = new NonTool(1, "OAK_LOG", "LOG", 72); // THROW EXCEPTION

        delete Oak_Log1;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Iron_Sword = new Tool(23, "IRON_SWORD", "-", 15);

        delete Iron_Sword;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Oak_Log1 = new NonTool(1, "OAK_LOG", "LOG", 32);
        Item *Oak_Log2 = new NonTool(1, "OAK_LOG", "LOG", 32);

        *(Oak_Log1) += *(Oak_Log2);
        cout << *Oak_Log1 << endl;

        *(Oak_Log1) += *(Oak_Log2); // THROW EXCEPTION
        cout << *Oak_Log1 << endl;

        delete Oak_Log1;
        delete Oak_Log2;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Wooden_Pickaxe = new Tool(13, "WOODEN_PICKAXE", "-", 10);
        Item *Stick = new NonTool(7, "STICK", "-", 32);

        *(Wooden_Pickaxe) += *(Stick); // THROW EXCEPTION

        delete Wooden_Pickaxe;
        delete Stick;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Diamond = new NonTool(12, "DIAMOND", "-", 64);

        cout << Diamond->getQuantity() << endl;
        cout << Diamond->getDurability() << endl; // THROW EXCEPTION

        delete Diamond;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Diamond_Sword = new Tool(24, "DIAMOND_SWORD", "-", 5);

        cout << Diamond_Sword->getDurability() << endl;
        cout << Diamond_Sword->getQuantity() << endl; // THROW EXCEPTION

        delete Diamond_Sword;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Diamond_Sword = new Tool(24, "DIAMOND_SWORD", "-", 5);
        Item *Diamond = new NonTool(12, "DIAMOND", "-", 64);

        Diamond_Sword->use();
        cout << *Diamond_Sword << endl;

        Diamond_Sword->use();
        Diamond_Sword->use();
        cout << *Diamond_Sword << endl;

        Diamond->use(); // THROW EXCEPTION
        cout << *Diamond << endl;

        delete Diamond_Sword;
        delete Diamond;

    } catch (ItemException &e) {
        e.displayMessage();
    }

    try {
        Item *Wooden_Pickaxe = new Tool(13, "WOODEN_PICKAXE", "-", 10);
        Item *Stick = new NonTool(7, "STICK", "-", 32);

        cout << Wooden_Pickaxe->isTool() << endl;
        cout << Stick->isTool() << endl;

        delete Wooden_Pickaxe;
        delete Stick;

    } catch (ItemException &e) {
        e.displayMessage();
    }
}