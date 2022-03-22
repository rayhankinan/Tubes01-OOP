#include "craftingTableInterface.hpp"

#include <cstdarg>

// default ctor
CraftingTable::CraftingTable() : MaxRecipes(10) {
    this->recipes = new Recipe[10];
    this->NumOfRecipes = 0;
    this->table = Matrix<Item*>(row, col);

    // BELUM YAKIN
    // set crafting table matrix to empty items
    for (int i=0; i < this->row; i++) {
        for (int j=0; j < this->col; j++) {
            // set setiap indeks crafting table ke item null
            this->table.setElmt(i, j, NULL);
    }}
}

// ctor with custom number of maxrecipes
CraftingTable::CraftingTable(int MaxRecipes) : MaxRecipes(MaxRecipes) {
    this->recipes = new Recipe[this->MaxRecipes];
    this->NumOfRecipes = 0;
    this->table = Matrix<Item*>(row, col);

    // BELUM YAKIN
    // set crafting table matrix to empty items
    for (int i=0; i < this->row; i++) {
        for (int j=0; j < this->col; j++) {
            // set setiap indeks crafting table ke item null
            this->table.setElmt(i, j, NULL);
    }}
}

// dtor
CraftingTable::~CraftingTable() {
    delete[] this->recipes;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            delete table(i, j);
    }}
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
    /* CEK bila table kosong semua */
    bool empty = true;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            if (this->table(i,j) != NULL) {
                empty = false;
                break;
            }
        }
    }
    if (empty) {
        throw CraftingException(0);
    }

    /* OPSI PERTAMA CRAFTING: 
    Craft dua item tool dengan jenis sama
    dengan durability x dan y menjadi satu item tool sama dengan durability
    min(x+y,10) 
    
    Kalau ada lebih dari dua tool di crafting table haram,
    kalau ada dua tool yang berbeda haram,
    kalau ada nontool haram*/
    int toolcount = 0;  // hitung jumlah tool di crafting table
    string FirstTool;
    int firstDurability, secondDurability;
    bool twotools = false;
    
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            if (this->table(i,j) == NULL) {     // skip slot yg tidak berisi
                continue;
            } else {
                // cek apakah tool
                if (isTool(this->table(i,j))) {
                    toolcount++;
                    if (toolcount == 1) {
                        FirstTool = this->table(i,j)->getName();    // get ID of first tool
                        firstDurability = this->table(i,j)->getDurability();
                    } else if (toolcount == 2) {
                        // cek apakah id tool kedua sama dengan pertama
                        if (this->table(i,j)->getName() != FirstTool) {
                            break;
                        } else {
                            secondDurability = this->table(i,j)->getDurability();
                            twotools = true;
                        }
                    } else {    // terdapat lebih dari 2 tool di crafting table
                        twotools = false;
                        break;
                    }

                } else {    // di crafting table ada item yang tidak tool
                    twotools = false;
                    break;
                }
            }
        }
    }
    if (twotools) {     // jika format kedua tool sudah benar dan ditambahkan ke inventory
        // clear crafting table
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                if (this->table(i,j) != NULL) {
                    // delete item tool yang telah digunakan pada crafting table
                    delete this->table(i, j);
                    this->table(i, j) = NULL;
                }
        }}
        /* give item to inventory
        AGAK BINGUNG GES GIMANA NAMBAHIN DURABILITY NYA 
        min(firstDurability+secondDurability, 10) nya maksudnya durability*/
        // inventory.give(FirstTool, 1, min(firstDurability+secondDurability, 10));
        return;
    } // Bila tidak ketemu dua tools cek opsi kedua crafting
    /* OPSI KEDUA CRAFTING: 
    Craft item dari resep yang ada
    - dapat dengan resep submatriks kurang dari 3x3
    - resep dapat direfleksikan pada sumbu-y
    - tidak harus item, tapi tipe yang sama */
    // cek dulu apakah semua item di crafting table adalah nontool
    bool nonToolCheck = true;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            if ((this->table(i,j)) != NULL && (this->table(i,j))->isTool()) {
                throw CraftingException(1);
            }
        }
    }
    bool recipeFound = false;   // check if current recipe matches
    int iterRecipe = 0, rightRecipe, offsetRow, offsetCol, currentRow, currentCol, rightOffsetRow, rightOffsetCol;
    // iterate through all recipe
    while (iterRecipe < this->NumOfRecipes && !recipeFound) {       // iterate through all recipes
        rightRecipe = iterRecipe;
        offsetRow=0;
        while (offsetRow <= this->row - this->recipes[iterRecipe].getRow() && !recipeFound) { // give row offset for submatrix
            offsetCol=0;
            while (offsetCol <= this->row - this->recipes[iterRecipe].getCol() && !recipeFound) { // give column offset for submatrix
                rightOffsetRow = offsetRow; rightOffsetCol = offsetCol;

                // check recipe for particular submatrix NOT INVERTED
                bool currentRecipe = true;
                currentRow = 0;
                while (currentRow < this->row && currentRecipe) {
                    currentCol = 0;
                    while (currentCol < this->col && currentRecipe) {
                        // check recipe for submatrix
                        string name, type;
                        if (this->table(currentRow, currentCol) == NULL) {
                            name = "-";
                            type = "-";
                        }
                        else {
                            name = this->table(currentRow,currentCol)->getName();
                            type = this->table(currentRow,currentCol)->getType();
                        }
                        if (offsetRow <= currentRow && currentRow <= offsetRow+this->recipes[iterRecipe].getRow()-1 && offsetCol <= currentCol && currentCol <= offsetCol+this->recipes[iterRecipe].getCol()-1) {
                            //check if current slot matches name or type of slot recipe
                            string recipeNameType = this->recipes[iterRecipe].getConfigElmt(currentRow-offsetRow, currentCol-offsetCol);
                            if (name != recipeNameType && type != recipeNameType) {
                                currentRecipe = false;
                            } 
                        // check if slot empty di luar submatrix
                        } else {
                            if (this->table(currentRow,currentCol) != NULL) {
                                currentRecipe = false;
                        }}
                        currentCol++;
                    }
                    currentRow++;
                }
                // if non inverted recipe is right
                if (currentRecipe) {
                    recipeFound = true;
                    break;
                } else {
                    // check recipe for particular submatrix INVERTED
                    currentRecipe = true;
                    currentRow = 0;
                    while (currentRow < this->row && currentRecipe) {
                        currentCol = 0;
                        while (currentCol < this->col && currentRecipe) {
                            string name, type;
                            if (this->table(currentRow, currentCol) == NULL) {
                                name = "-";
                                type = "-";
                            }
                            else {
                                name = this->table(currentRow,currentCol)->getName();
                                type = this->table(currentRow,currentCol)->getType();
                            }
                            // check recipe for submatrix
                            if (offsetRow <= currentRow && currentRow <= offsetRow+this->recipes[iterRecipe].getRow()-1 && offsetCol <= currentCol && currentCol <= offsetCol+this->recipes[iterRecipe].getCol()-1) {
                                //check if current slot matches name or type of slot recipe
                                string recipeNameType = this->recipes[iterRecipe].getConfigElmt((currentRow-offsetRow), this->recipes[iterRecipe].getCol()-1-(currentCol-offsetCol));
                                if (name != recipeNameType && type != recipeNameType) {
                                    currentRecipe = false;
                                } 
                            // check if slot empty di luar submatrix
                            } else {
                                if (this->table(currentRow,currentCol) != NULL) {
                                    currentRecipe = false;
                            }}
                            currentCol++;
                        }
                        currentRow++;
                    }
                    if (currentRecipe) {
                        recipeFound = true;
                        break;
                    }
                }
                offsetCol++;
            }
            offsetRow++;
        }
        iterRecipe++;
    }
    if (!recipeFound) { // bila tidak bisa crafting
        throw CraftingException(1);
    } else {
        // give item hasil craft
        // mencoba handling untuk multiple crafting item
        // get rightRecipe, rightOffsetRow, rightOffsetCol
        for (int i = rightOffsetRow; i < rightOffsetRow + this->recipes[rightRecipe].getRow(); i++) {
            for (int j = rightOffsetCol; j < rightOffsetCol + this->recipes[rightRecipe].getCol(); j++) {
                // bila quantity di crafting table hanya 1, remove
                if (this->table(i, j) != NULL) {
                    if (this->table(i,j)->getQuantity() == 1) {
                        delete this->table(i, j);
                        this->table(i, j) = NULL;
                    } else {
                        // bila quantity di crafting table hanya > 1, quantity 
                        this->table(i, j)->setQuantity(this->table(i,j)->getQuantity() - 1);
                    }
                }
            }
        }
        /* give item to inventory
        AGAK BINGUNG GES GIMANA GIVE NYA NENTUIN TOOL AMA NONTOOL
        10 nya maksudnya durability buat tool*/
        // inventory.give(this->recipes[rightRecipe].getProductName(), this->recipes[rightRecipe].getProductQty(), 10);
    }
}

// show crafting table
void CraftingTable::show() const {
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            Item* item = (this->table(i, j));
            string var;
            if (item == NULL) {
                var = "-";
            }
            else {
                var = (item->getName());
            }
            cout << "[" << var << "] ";
        }
        cout << endl;
    }
}

// set recipe from FileIO::listOfRecipe()
void CraftingTable::setRecipes(vector<Recipe> r) {
    this->NumOfRecipes = 0;
    if (r.size() <= getMaxRecipes()) {
        for (int i = 0; i < r.size(); i++) {
            this->recipes[i] = r[i];
            this->NumOfRecipes++;
        }
    }
}

// add recipe
void CraftingTable::addRecipe(Recipe r) {
    if (this->NumOfRecipes < this->MaxRecipes) {
        this->recipes[this->NumOfRecipes] = r;
        this->NumOfRecipes++;
    }
}

// add item to crafting table
void CraftingTable::addItem(int row, int col, Item* item) {
    this->table.setElmt(row, col, item);
}

// move item from inv to crafting table
/* NOT TESTED YET (waiting for inventory access) */
void CraftingTable::move(string slotInv, int n, ...) {
    va_list listSlotCraft;
    va_start(listSlotCraft, n);
    // check jumlah item di slot inv, harus >= n (unable to access inv, waiting)
    /*
    Item* item = inventory.getElmt(slotInv);
    if (item.quantity < n) {
        throw CraftingException(2);
    } 
    */
    Item* item; // for example purposes (temporary)
    for (int i = 0; i < n; i++) {
        string slotCraft = va_arg(listSlotCraft, char*);
        // kalo ternyata gaboleh ngisi crafting table yang uda ada isi:
        /* 
        if (this->getElmt(slotCraft) != NULL) {
            throw CraftingException(3);
        }
        */
        this->setElmt(slotCraft, item);
    }
    va_end(listSlotCraft);
}

// return item from crafting table to inv
// NOT TESTED YET (waiting for inventory access)
void CraftingTable::move(string slotCraft, int n, string slotInv) {
    // kalo ternyata N-nya boleh lebih dari 1 --> paramnya ganti jadi ellipsis (rombak)
    /*
    if (item == NULL || item->getQuantity() < n) { // tambahin juga: OR inventory tidak kosong (isinya item jenis beda/isinya jenis sama tp penuh)
        throw CraftingException(2);
    }
    */

    Item* item = this->getElmt(slotCraft);
    // asumsi sementara kayak di spek (N-nya cuma boleh 1)
    if (item == NULL || n != 1) {
        throw CraftingException(2);
    }
    else {
        // inventory.setElmt[slotInv, item]; unable to access (waiting)
        this->setElmt(slotCraft, NULL);
    }
}

// check tool/nontool of an item
bool CraftingTable::isTool(Item* i){
    try {
        i->getDurability();
        return true;
    } 
    catch (Exception&) {
        return false;
    }
}
