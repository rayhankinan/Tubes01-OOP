#ifndef CRAFTING_TABLE_INTERFACE_HPP
#define CRAFTING_TABLE_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/toolInterface.hpp"
#include "./recipeInterface.hpp"

class CraftingTable {
private:
    // attributes
    Recipe* *recipes;
    int NumOfRecipes;
    const int MaxRecipes;
    const int row = 3;
    const int col = 3;
    Matrix<Item*> table = Matrix<Item*>(row, col);

public:
    CraftingTable(); // default ctor
    CraftingTable(int); // ctor with custom number of maxrecipes
    ~CraftingTable(); // dtor

    // get NumOfRecipes
    int getNumOfRecipes() const;
    // get MaxRecipe
    int getMaxRecipes() const;

    // craft item
    void craft(); 
    // show crafting table
    void show() const;
    // add recipe
    void addrecipe(Recipe*);
    // add item to crafting table
    void addItem(int, int, Item*);
    // move item from inv to crafting table
    void move(string slotInv, int, ...);
    // return item from crafting table to inv
    void move(string slotCraft, int, string slotInv);

};


#endif
