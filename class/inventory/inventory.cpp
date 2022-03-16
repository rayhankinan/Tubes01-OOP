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
            table.setElement(i, j, inv.table.getElement(i, j));
        }
    }
}
// dtor for inventory
Inventory::~Inventory() {
    // delete all items in table
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            delete table.getElement(i, j);
        }
    }
}

// add item to inventory, use exception handling
void Inventory::give(Item* item, const int qty){
    // check if item is tool or non-tool
    if (dynamic_cast<Tool*>(item) != NULL) {
        // if item is tool, check if there is enough space
        if (table.getElement(0, 0) == NULL) {
            // if there is no space, throw exception
            throw MatrixException(0);
        }
        // if there is space, add item to first empty slot
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table.getElement(i, j) == NULL) {
                    table.setElement(i, j, item);
                    return;
                }
            }
        }
    } else {
        // if item is non-tool, check if there is enough space
        if (table.getElement(1, 0) == NULL) {
            // if there is no space, throw exception
            throw MatrixException(0);
        }
        // if there is space, add item to first empty slot
        for (int i = 1; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (table.getElement(i, j) == NULL) {
                    table.setElement(i, j, item);
                    return;
                }
            }
        }
    }
}