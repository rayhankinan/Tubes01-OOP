#include "craftingTableInterface.hpp"

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

// craft item
void CraftingTable::craft() {
    // GWS FAN :V
}

// show crafting table
void CraftingTable::show() const {
    
}

// add recipe
void CraftingTable::addrecipe(Recipe* r) {
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
void CraftingTable::move(string slotInv, int, ...) {

}

// return item from crafting table to inv
void CraftingTable::move(string slotCraft, int, string slotInv) {

}
