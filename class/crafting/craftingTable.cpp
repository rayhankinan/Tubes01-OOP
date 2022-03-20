#include "craftingTableInterface.hpp"

#include <cstdarg>

// default ctor
CraftingTable::CraftingTable() : MaxRecipes(10) {
    this->recipes = new Recipe*[10];
    this->NumOfRecipes = 0;
    this->table = Matrix<Item*>(row, col);
}

// ctor with custom number of maxrecipes
CraftingTable::CraftingTable(int MaxRecipes) : MaxRecipes(MaxRecipes) {
    this->recipes = new Recipe*[this->MaxRecipes];
    this->NumOfRecipes = 0;
    this->table = Matrix<Item*>(row, col);
}

// dtor
CraftingTable::~CraftingTable() {
    delete[] this->recipes;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            delete table(i, j);
        }
    }
    this->table.~Matrix();
}

// get NumOfRecipes
int CraftingTable::getNumOfRecipes() const {
    return this->NumOfRecipes;
}

// get MaxRecipe
int CraftingTable::getMaxRecipes() const {
    return this->MaxRecipes;
}

// get table element based on slotID
Item*& CraftingTable::getElmt(string slotID) const {
    return this->table[slotID];
}
        
// set table element based on slotID
void CraftingTable::setElmt(string slotID, Item* item) {
    this->table.setElmt(slotID, item);
}

// craft item
void CraftingTable::craft() {
    // GWS FAN :V
}

// show crafting table
void CraftingTable::show() const {
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            cout << "[" << this->table(i, j) << "] ";
        }
        cout << endl;
    }
}

// add recipe
void CraftingTable::addRecipe(Recipe* r) {
    if (this->NumOfRecipes < this->MaxRecipes) {
        this->recipes[this->NumOfRecipes] = r;
        this->NumOfRecipes++;
    }
}

// add item to crafting table
void CraftingTable::addItem(int row, int col, Item* item) {
    if (0 <= row && row < this->row && 0 <= col && col < this->col){
        this->table(row, col) = item;
    }
}

// move item from inv to crafting table
/* NOT TESTED YET (waiting for inventory access) */
void CraftingTable::move(string slotInv, int n, ...) {
    va_list listSlotID;
    va_start(listSlotID, n);
    // Item* elmt = inventory.getElmt(slotInv); unable to access (waiting)
    Item* item; // for example purposes (temporary)
    for (int i = 0; i < n; i++) {
        string slotID = va_arg(listSlotID, char*);
        this->setElmt(slotID, item);
    }
    va_end(listSlotID);
}

// return item from crafting table to inv
/* NOT TESTED YET (waiting for inventory access) */
void CraftingTable::move(string slotCraft, int n, string slotInv) {
    Item* item = this->getElmt(slotCraft);
    // inventory.setElmt[slotInv, item]; unable to access (waiting)
}
