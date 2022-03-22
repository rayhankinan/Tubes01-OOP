#include "inventoryInterface.hpp"
#include <iostream>

using namespace std;

// default ctor and fill with default item constructor
Inventory::Inventory(){
    this->table = Matrix<Item*>(length, width);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            this->table.setELmt(i, j, NULL);
        }
    }
} 

// copy constructor
Inventory::Inventory(const Inventory &inv) {
    // create Matrix of pointers to items
    this->table = Matrix<Item*>(length, width);
    // copy table
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            this->table(i, j) = inv.table(i, j);
        }
    }
}

// dtor
Inventory::~Inventory(){
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            delete table(i, j);
        }
    }
    this->table.~Matrix();
}

void Inventory::show() const{
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (this->table(i, j) == NULL) {
                cout << "\t[I" << i*9+j << "|0]\t";
                if (j == 8) {
                    cout << endl;
                }
            }
            else {
                try{
                    cout << "\t[I" << i*9+j << "|" << this->table(i, j)->getID() << "|" << this->table(i, j)->getDurability() << "]";
                    if (j == 8) {
                        cout << endl;
                    }
                }
                catch(const NonToolException &e){
                    cout << "\t[I" << i*9+j << "|" << this->table(i, j)->getID() << "|" << this->table(i, j)->getQuantity() << "]";
                    if (j == 8) {
                        cout << endl;
                    }
                }
            }
        }
    }
}

void Inventory::give(string name, int qty){
    FileIO FI;
    string category;
    category = getCategory(FI, name);
    bool found = false;
    if (category == "TOOL") {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (qty > 0){
                    if (this->table(i, j) == NULL) {
                        this->table(i, j) = new Tool(getInventoryID(FI, name),name, getInventoryType(FI, name), 10);
                        qty--;
                    }
                }
            }
        }
        if (qty > 0) {
            throw InventoryException(0); //throw
        }
    
    }
    else if(category == "NONTOOL"){
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (qty > 0){
                    if (this->table(i,j) != NULL && this->table(i, j)->getName() == name) {
                        try{
                            this->table(i, j)+= qty;
                            qty = 0;
                            return;
                        }
                        catch(NonToolException &e){
                            int sisa = 64 - this->table(i, j)->getQuantity();
                            this->table(i, j) += sisa;
                            qty -= sisa;
                            if (qty = 0) {
                                return;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (qty > 0) {
                    if (this->table(i, j) == NULL) {
                        this->table(i, j) = new NonTool(getInventoryID(FI, name),name, getInventoryType(FI, name), qty > 64 ? 64 : qty);
                        qty -= 64;
                    }
                }
            }
        }
        if (qty > 0) {
            throw InventoryException(0); //throw
        }
        
    }
}

void Inventory::discard(string slotID,  int qty){
    if(table[slotID] == NULL){
        throw InventoryException(5);
    }
    if((table[slotID])->isTool()){
        this->table[slotID] = NULL;
    }
    else if(!(table[slotID])->isTool()){
        try{
            this->table[slotID]-= qty;
            if (table[slotID]->getQuantity() == 0) {
                this->table[slotID] = NULL;
            }
        }
        catch(NonToolException &e){
            e.displayMessage();
        }
    }
    
}

void Inventory::use(const string slotID){
    if(table[slotID] == NULL){
        throw InventoryException(5);
    }
    if(table[slotID]){
        throw InventoryException(5);
    }
    try{
        this->table[slotID]->use();
        if(this->table[slotID]->getDurability()==0){
            this->table[slotID] = NULL;
        }
    }
    catch(ToolException &e){
        e.displayMessage();
    }
}

void Inventory::moveInInventory(string slotSrc, int qty, string slotTarget){
    if(table[slotSrc] == NULL || table[slotTarget] == NULL){
        throw InventoryException(5);
    }
    if (this->table[slotSrc]->isTool() || this->table[slotTarget]->isTool()){
        throw InventoryException(1);
    }
    if (this->table[slotSrc]->getID() != this->table[slotTarget]->getID()){
        throw InventoryException(2);
    }
    if (this->table[slotSrc]->getQuantity() < qty) {
        throw InventoryException(3);
    }

    try{
        this->table[slotTarget] += qty;
        this->table[slotSrc] -= qty;
        if(this->table[slotSrc]->getQuantity()==0){
            this->table[slotSrc] = NULL;
        }
    }
    catch(NonToolException &e){
        e.displayMessage();
    }

}


 // get table element based on slotID
Item*& Inventory::getElmt(string slotID) {
    return this->table[slotID];
}

void Inventory::setElmt(string slotID, Item* item){
    this->table[slotID] = item;
}

int Inventory::getInventoryID(FileIO FI, string name){
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    // search name item in list of tool and return item ID
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return listTool[i].getID();
        }
    }
    throw InventoryException(4);
}

string Inventory::getInventoryType(FileIO FI, string name){
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    // search name item in list of tool and return item type
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return listTool[i].getType();
        }
    }
    throw InventoryException(4);
}

string Inventory::getCategory(FileIO FI, string name){
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    // search name item in list of tool and return item category
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return "TOOL";
        }
    }
    // search name item in list of non tool and return item category
    for (int i = 0; i < listNonTool.size(); i++) {
        if (listNonTool[i].getName() == name) {
            return "NONTOOL";
        }
    }
    throw InventoryException(4);
}