#ifndef CRAFTING_TABLE_INTERFACE_HPP
#define CRAFTING_TABLE_INTERFACE_HPP

#include <vector>

#include "../exception/craftingExceptionInterface.hpp"
#include "../inventory/inventoryInterface.hpp"
#include "../collection/matrixInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/toolInterface.hpp"
#include "./recipeInterface.hpp"

extern Inventory inventory;

class CraftingTable {
private:
    // attributes
    Recipe* recipes;
    int NumOfRecipes;
    const int MaxRecipes;
    const int row = 3;
    const int col = 3;
    Matrix<Item*> table;

public:
    CraftingTable(); // default ctor
    CraftingTable(int); // ctor with custom number of maxrecipes
    ~CraftingTable(); // dtor

    // get NumOfRecipes
    int getNumOfRecipes() const;
    // get MaxRecipe
    int getMaxRecipes() const;
    // get table element based on slotID
    Item*& getElmt(string) const;
        
    // set table element based on slotID
    void setElmt(string, Item*); 

    // craft item
    void craft(); 
    // show crafting table
    void show() const;
    // set recipe from FileIO::listOfRecipe()
    void setRecipes(vector<Recipe> recipes);
    // add recipe
    void addRecipe(Recipe r);
    // add item to crafting table
    void addItem(int, int, Item*);
    // move item from inv to crafting table
    void move(string slotInv, int, ...);
    // return item from crafting table to inv
    void move(string slotCraft, int, string slotInv);
    // check tool/nontool of an item
    bool isTool(Item* i);

};


#endif
