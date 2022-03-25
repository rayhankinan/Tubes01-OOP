#ifndef CRAFTING_TABLE_INTERFACE_HPP
#define CRAFTING_TABLE_INTERFACE_HPP

#include <vector>

#include "../exception/craftingExceptionInterface.hpp"
#include "../inventory/inventoryInterface.hpp"
#include "../collection/matrixInterface.hpp"
#include "../fileIO/fileIOInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/toolInterface.hpp"
#include "./recipeInterface.hpp"

class CraftingTable {
private:
    // attributes
    Recipe* recipes;
    int NumOfRecipes;
    int MaxRecipes;
    const int row = 3;
    const int col = 3;
    Matrix<Item*> table;

public:
    CraftingTable(); // default ctor
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
    void craft(Inventory&); 
    // show crafting table
    void show() const;
    // set recipe from FileIO::listOfRecipe()
    void setRecipes(vector<Recipe>);
    // add recipe
    void addRecipe(Recipe);
    // add item to crafting table
    void addItem(int, int, Item*);
    // move item from inv to crafting table
    void move(Inventory&, string, int, vector<string>);
    // return item from crafting table to inv
    void move(Inventory&, string, int, string);
    // check tool/nontool of an item
    bool isTool(Item*);

    void peek(string) const; // display recipe

};


#endif
