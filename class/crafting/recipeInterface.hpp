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
    Matrix<string> configRecipe = Matrix<string>(row, col);

public:
    Recipe(); // default ctor
    Recipe(const Recipe&); // cctor
    Recipe(int, int, int, string); // parameterized ctor
    ~Recipe(); // dtor

    // getter
    int getRow() const;
    int getCol() const;
    int getProductQty() const;
    string getProductName() const;

    // setter
    void setRow(int);
    void setCol(int);
    void setProductQty(int);
    void setProductName(string);
    void setConfigElmt(int, int, string);

    void printRecipe() const; // for testing

};


#endif
