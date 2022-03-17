#include "craftingTableInterface.hpp"

// default ctor
CraftingTable::CraftingTable() {

}

// dtor
CraftingTable::~CraftingTable() {

}

// craft item
void CraftingTable::craft() {
    // GWS FAN :V
}

// show crafting table
void CraftingTable::show() const {
    
}

// add item to crafting table
void CraftingTable::addItem(int row, int col, Item* item) {
    if (0 <= row && row < this->row && 0 <= col && col < this->col){
        this->table(row, col) = item;
    }
}

// move item from inv to crafting table
void CraftingTable::move(string slotInv, int, ...) {

}

// return item from crafting table to inv
void CraftingTable::move(string slotCraft, int, string slotInv) {

}
