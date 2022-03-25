#include "craftingTableInterface.hpp"


// default ctor
CraftingTable::CraftingTable() {
    FileIO FIO;
    vector<Recipe> r = FIO.listOfRecipe();
    this->MaxRecipes = r.size();
    this->recipes = new Recipe[r.size()];
    this->NumOfRecipes = 0;
    this->table = Matrix<Item*>(row, col);

    // BELUM YAKIN
    // set crafting table matrix to empty items
    for (int i=0; i < this->row; i++) {
        for (int j=0; j < this->col; j++) {
            // set setiap indeks crafting table ke item null
            this->table.setElmt(i, j, NULL);
    }}
    this->setRecipes(r);
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
    delete this->getElmt(slotID);
    this->table.setElmt(slotID, item);
}

// craft item
void CraftingTable::craft(Inventory& inv) {
    bool firstCraft = true;
    while (true) {
        /* CEK bila table kosong semua
        Bila kosong crafting pada crafting pertama throw error,
        bila kosong pada crafting selanjutnya, tidak throw error tapi keluar dari method*/
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
            if (firstCraft) {
                throw CraftingException(0);
            } else {
                return;
            }
        }
        /* set pengecek apakah crafting pertama sehingga pada loop craft selanjutnya
        tidak throw error crafting table kosong */
        firstCraft = false;

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
            /* give item to inventory, min(firstDurability+secondDurability, 10) nya maksudnya durability*/
            inv.give(FirstTool, min(firstDurability+secondDurability, 10), 1);
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
            /* give item to inventory */
            inv.give(this->recipes[rightRecipe].getProductName(), this->recipes[rightRecipe].getProductQty());
        }
    }
}

// show crafting table
void CraftingTable::show() const {
    for (int i = 0; i < this->row; i++) {
        cout << "\t\t\t\t\t";
        for (int j = 0; j < this->col; j++) {
            if (this->table(i, j) == NULL) {
                cout << "\t[C" << i*3+j << "|0]\t";
                if (j == 2) {
                    cout << endl;
                }
            }
            else {
                if (this->table(i,j)->isTool()){
                    cout << "\t[C" << i*3+j << "|" << this->table(i, j)->getID() << "|" << this->table(i, j)->getDurability() << "]";
                    if (j == 2) {
                        cout << endl;
                    }
                }
                else{
                    cout << "\t[C" << i*3+j << "|" << this->table(i, j)->getID() << "|" << this->table(i, j)->getQuantity() << "]";
                    if (j == 2) {
                        cout << endl;
                    }
                }
            }
        }
    }
    cout << endl;
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
void CraftingTable::move(Inventory& inv, string slotInv, int n, vector<string> slotCrafts) {
    Item* item = inv.getElmt(slotInv);
    // kalau slotInv kosong (gaada item), throw
    if (item == NULL) {
        throw CraftingException(4);
    }
    // check jumlah item di slot inv harus cukup alias >= n (nontool only)
    if (!(item->isTool())) {
        if (item->getQuantity() < n) {
            throw CraftingException(2);
        } 
    }

    int toGive = 1; // default qty yg dipindahkan adalah 1
    int inSlotDest = 0; // default item di slot destination

    // kasus memindahkan 1 barang ke 1 slot craft 
    if (slotCrafts.size() == 1) {
        // menentukan quantity item yang dipindahkan (default 1)
        if (n > 1) {
            // exception (tool tidak bisa ditumpuk di slotcraft)
            if (item->isTool()) {
                throw CraftingException(2);
            }
            toGive = n;
        }
        // gaboleh ngisi crafting table yang uda ada isi
        Item* destSlot = this->getElmt(slotCrafts[0]);
        if (destSlot != NULL) {
            if (destSlot->isTool()) {
                throw CraftingException(3);
            }
            else {
                if ((destSlot->getName() != item->getName() || destSlot->getType() != item->getType())) {
                    throw CraftingException(3);
                }
                else {
                    inSlotDest = destSlot->getQuantity();
                }
            }
        }
        
        // mengisi slot crafting untuk tool
        if (item->isTool()) {
            this->setElmt(slotCrafts[0], (new Tool(item->getID(), item->getName(), item->getType(), item->getDurability())));
        }
        // mengisi slot crafting untuk non-tool (bisa ditumpuk, multiple crafting support)
        else {
            this->setElmt(slotCrafts[0], (new NonTool(item->getID(), item->getName(), item->getType(), inSlotDest + toGive)));
        }
        // mengosongkan/mengurangi item inventory
        if (item->isTool() || item->getQuantity() - toGive == 0) {
            inv.setElmt(slotInv, NULL);
        }
        else {
            inv.setElmt(slotInv, (new NonTool(item->getID(), item->getName(), item->getType(), (item->getQuantity() - toGive))));
        }
    }

    // kasus memindahkan n barang ke n slot craft
    else {
        // check keselarasan jumlah item yang dipindah dengan jumlah slot crafting
        if (n != slotCrafts.size()) {
            throw CraftingException(2);
        }
        // mengisi slot crafting untuk tool
        if (item->isTool()) {
            for (int i = 0; i < n; i++) {
                // gaboleh ngisi crafting table yang uda ada isi
                if (this->getElmt(slotCrafts[i]) != NULL) {
                    throw CraftingException(3);
                }
                this->setElmt(slotCrafts[i], (new Tool(item->getID(), item->getName(), item->getType(), item->getDurability())));
            }
        }
        // mengisi slot crafting untuk non-tool
        else {
            for (int i = 0; i < n; i++) {
                // gaboleh ngisi crafting table yang uda ada isi
                Item* destSlot = this->getElmt(slotCrafts[i]);
                if (destSlot != NULL) {
                    if (!destSlot->isTool()) {
                        if ((destSlot->getName() != item->getName() || destSlot->getType() != item->getType())) {
                            throw CraftingException(3);
                        }
                        else {
                            inSlotDest = destSlot->getQuantity();
                        }
                    }
                }
                this->setElmt(slotCrafts[i], (new NonTool(item->getID(), item->getName(), item->getType(), inSlotDest + toGive)));
                inSlotDest = 0;
            }
        }
        // mengosongkan/mengurangi item inventory
        if (item->isTool() || item->getQuantity() - n == 0) {
            inv.setElmt(slotInv, NULL);
        }
        else {
            inv.setElmt(slotInv, (new NonTool(item->getID(), item->getName(), item->getType(), (item->getQuantity() - n))));
        }
    }
}

// return item from crafting table to inv
void CraftingTable::move(Inventory& inv, string slotCraft, int n, string slotInv) {
    Item* item = this->getElmt(slotCraft);
    // kalau slotCraft kosong (gaada item), throw
    if (item == NULL) {
        throw CraftingException(2);
    }
    // N-nya cuma boleh 1 sesuai di spesifikasi
    int toGive = 1;
    int inSlotDest = 0; // default assumption isi item di slot tujuan
    // asumsi default item di slot tujuan adalah 0
    Item* destSlot = inv.getElmt(slotInv);
        if (destSlot != NULL) {
            if (destSlot->isTool()) {
                throw CraftingException(3);
            }
            else {
                if ((destSlot->getName() != item->getName() || destSlot->getType() != item->getType())) {
                    throw CraftingException(3);
                }
                else {
                    inSlotDest = destSlot->getQuantity();
                }
            }
        }
    // mengisi slot inventory untuk tool
    if (item->isTool()) {
        inv.setElmt(slotInv, (new Tool(item->getID(), item->getName(), item->getType(), item->getDurability())));
    }
    // mengisi slot inventory untuk non-tool
    else {
        inv.setElmt(slotInv, (new NonTool(item->getID(), item->getName(), item->getType(), inSlotDest + toGive)));
    }
    // mengosongkan/mengurangi item di crafting table
    if (item->isTool() || item->getQuantity() - toGive == 0) {
        this->setElmt(slotCraft, NULL);
    }
    else {
        this->setElmt(slotCraft, (new NonTool(item->getID(), item->getName(), item->getType(), (item->getQuantity() - toGive))));
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

// get recipe configuration
void CraftingTable::peek(string item) const {
    Recipe* r = this->recipes;

    for (int i = 0; i < this->getNumOfRecipes(); i++)
    {
        if (r[i].getProductName() == item) {
            r[i].display();
            cout << endl;
            return;
        }
    }
    cout << "RECIPE NOT FOUND" << endl << endl;
    return;
}
