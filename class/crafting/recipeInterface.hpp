#ifndef RECIPE_INTERFACE_HPP
#define RECIPE_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/toolInterface.hpp"

class Recipe {
private:
    // attributes
    int row;
    int col;
    int productQty;
    string productName;
    Matrix<string> configRecipe;
public:
    Recipe(); // default ctor
    Recipe(const Recipe&); // cctor
    Recipe(int, int); // parameterized ctor
    ~Recipe(); // dtor

    // getter
    int getRow() const;
    int getCol() const;
    int getProductQty() const;
    string getProductName() const;
    string getConfigElmt(int row, int col);

    // setter
    void setRow(int);
    void setCol(int);
    void setProductQty(int);
    void setProductName(string);
    void setConfigElmt(int, int, string);

    void display() const; // for testing

};


#endif
