#include "recipeInterface.hpp"


// default ctor (max-sized configRecipe w/ empty contents)
Recipe::Recipe() {
    this->row = 3;
    this->col = 3;
    this->productQty = 0;
    this->productName = "-";
    this->configRecipe = Matrix<string>(3, 3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            this->setConfigElmt(i, j, "-");
        }
    }
}

// cctor
Recipe::Recipe(const Recipe& r) {
    this->row = r.row;
    this->col = r.col;
    this->productQty = r.productQty;
    this->productName = r.productName;
    this->configRecipe = Matrix<string>(r.row, r.col);
    for (int i = 0; i < r.row; i++){
        for (int j = 0; j < r.col; j++){
            string elmt = r.configRecipe(i, j);
            this->setConfigElmt(i, j, elmt);
        }
    }
}

// parameterized ctor (configRecipe contents not initialized)
Recipe::Recipe(int row, int col, int productQty, string productName) {
    this->row = row;
    this->col = col;
    this->productQty = productQty;
    this->productName = productName;
    this->configRecipe = Matrix<string>(row, col);
}

// dtor
Recipe::~Recipe() {
    this->configRecipe.~Matrix();
}

// getter
int Recipe::getRow() const {
    return this->row;
}

int Recipe::getCol() const {
    return this->col;
}

int Recipe::getProductQty() const {
    return this->productQty;
}

string Recipe::getProductName() const {
    return this->productName;
}

// setter
void Recipe::setRow(int row) {
    this->row = row;
}

void Recipe::setCol(int col) {
    this->col = col;
}

void Recipe::setProductQty(int productQty) {
    this->productQty = productQty;
}

void Recipe::setProductName(string productName) {
    this->productName = productName;
}

void Recipe::setConfigElmt(int row, int col, string elmt) {
    if (0 <= row && row < this->row && 0 <= col && col < this->col){
        this->configRecipe(row, col) = elmt;
    }
}

// for testing
void Recipe::printRecipe() const {
    cout << "Row: " << this->row << endl;
    cout << "Col: " << this->col << endl;
    cout << "Product Name: " << this->productName << endl;
    cout << "Product Qty: " << this->productQty << endl;
    cout << "Configuration:" << endl;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            cout << this->configRecipe(i, j) << " ";
        }
        cout << endl;
    }
}