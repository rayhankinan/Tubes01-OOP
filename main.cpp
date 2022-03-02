#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    string line, command;

    /* Read item from config file */
    ifstream itemConfigFile(itemConfigPath);

    while (getline(itemConfigFile, line)) {
        /* Do something with the line */
        cout << line << endl;
    }

    itemConfigFile.close();

    /* Read recipe from recipe folder */
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        string recipeConfigPath = entry.path().string();

        ifstream recipeConfigFile(recipeConfigPath);

        while (getline(recipeConfigFile, line)) {
            /* Do something with the line */
            cout << line << endl;
        }

        recipeConfigFile.close();
    }

    /* Read command from user */
    while (cin >> command) {
        if (command == "SHOW") {
            /* Display crafting table */

        } else if (command == "GIVE") {
            string itemName;
            int itemQty;

            cin >> itemName >> itemQty;
            /* Give item */

        } else if (command == "DISCARD") {
            string inventorySlotID;
            int itemQty;

            cin >> inventorySlotID >> itemQty;
            /* Discard item */

        } else if (command == "MOVE") {
            string slotSrc, slotDest;
            int slotQty;

            cin >> slotSrc >> slotQty >> slotDest;
            /* Move item */

        } else if (command == "USE") {
            string inventorySlotID;

            cin >> inventorySlotID;
            /* Use item */

        } else if (command == "CRAFT") {
            /* Craft item */

        } else if (command == "EXPORT") {
            string fileName;

            cin >> fileName;
            /* Export to file */

        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}