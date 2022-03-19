#include "inventoryInterface.hpp"
#include <iostream>

using namespace std;

// default constructor for inventory
Inventory::Inventory() {
    // create Matrix of pointers to items
    this->table = Matrix<Item*>(length, width);
}
// cctor for inventory
Inventory::Inventory(const Inventory& inv) {
    // create Matrix of pointers to items
    this->table = Matrix<Item*>(length, width);
    // copy table
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            table(i, j) = inv.table(i, j);
        }
    }
}
// dtor for inventory
Inventory::~Inventory() {
    // delete all items in table
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            delete table(i, j);
        }
    }
}
/* Menambahkan Item ke Inventory. Sejumlah Item dengan jenis yang sama akan ditambahkan ke slot inventory, Berisi item nontool dengan jenis yang sama
Apabila tidak ditemukan slot yang memenuhi syarat tersebut, item ditambahkan pada slot kosong, Penambahan item dilakukan dari ID inventory terkecil. 
use try-catch and exception handling */
void Inventory::give(Item* item, const int qty){
    //check item type
    if (item->getType() == "nontool") {
        //check item name
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table(i, j)->getName() == item->getName()) {
                    table(i, j) += qty;
                    return;
                }
            }
        }
        //if not found, add to empty slot
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table(i, j) == NULL) {
                    table(i, j) = item;
                    table(i, j) += qty;
                    return;
                }
            }
        }
    }
    else if (item->getType() == "tool") {
        //check item name
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table(i, j)->getName() == item->getName()) {
                    table(i, j) += qty;
                    return;
                }
            }
        }
        //if not found, add to empty slot
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table(i, j) == NULL) {
                    table(i, j) = item;
                    table(i, j) += qty;
                    return;
                }
            }
        }
    }
}
// Membuang item di slot inventory dengan kuantitas yang diberikan.
void Inventory::discard(Item* item, const int qty) {
    //check item type
    if (item->getType() == "nontool") {
        //check item name
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table(i, j)->getName() == item->getName()) {
                    table(i, j) -= qty;
                    table(i, j) = NULL;
                    return;
                }
            }
        }
    }
    else if (item->getType() == "tool") {
        //check item name
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table(i, j)->getName() == item->getName()) {
                    table(i, j) -= qty;
                    table(i, j) = NULL;
                    return;
                }
            }
        }
    }
}

// print matrix inventory to console output 
// if nontool print slotID, name and quantity of item [ID | name | quantity]
// if tool print slotID, name, durability of item [ID | name | durability]
// if empty print slotID [ID]
void Inventory::show() const{
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (table(i, j) == NULL) {
                cout << "[I" << i*9+j << "|empty] ";
                if (j == 8) {
                    cout << endl;
                }
            }
            else if (table(i, j)->getType() == "nontool") {
                cout << "[I" << i*9+j << "|" << table(i, j)->getName() << "|" << table(i, j)->getQuantity() << "] ";
                if (j == 8) {
                    cout << endl;
                }
            }
            else if (table(i, j)->getType() == "tool") {
                cout << "[I" << i*9+j << "|" << table(i, j)->getName() << "|" << table(i, j)->getDurability() << "] ";
                if (j == 8) {
                    cout << endl;
                }
            }
        }
    }
}
/*
Menggunakan Item. Item tool dapat digunakan dan durabilitasnya akan berkurang.
USE <INVENTORY_SLOT_ID>
USE I0
I.S. : INVENTORY_SLOT_ID berisi Item tool.
F.S. : Durability Item pada INVENTORY_SLOT_ID berkurang 1. Jika durabilitynya mencapai 0, maka item hilang dari inventory.
*/
void Inventory::use(const string slotID) {
    //check if slotID is valid
    int slot = getNumberFromString(slotID);
    int i = slot / 9;
    int j = slot % 9;
    if (table(i, j) == NULL) {
        cout << "Slot " << slotID << " is empty" << endl;
    }
    else if (table(i, j)->getType() == "tool") {
        table(i, j)->use();
        if (table(i, j)->getDurability() == 0) {
            table(i, j) = NULL;
        }
    }
    else {
        cout << "Slot " << slotID << " is not a tool" << endl;
    }
    
}

// get element from slotID
template<class T>
T& Inventory::operator[](string slotID) const {
    // extract number from slotID
    int slotID = extractNumberFromString(slotID);
    int i = slotID / 9;
    int j = slotID % 9;
    // check if slotID is valid
    if (i < 0 || i >= length || j < 0 || j >= width) {
        throw MatrixException(0);
    }
    // return element from slotID
    return (table(i, j));
}
