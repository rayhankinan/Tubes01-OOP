#include "inventoryInterface.hpp"
#include <iostream>

using namespace std;

// default ctor
Inventory::Inventory(){
    this->table = Matrix<Item*>(length, width);
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
            if (this->table(i, j)->getID() == 0) {
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
    try{
        category = getCategory(FI, name);
    }
    catch(//sesuatu){
        cout << "Item tidak ditemukan" << endl;
        return
    }
    bool found = false;
    if (category == "TOOL") {
        while (qty > 0){
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (this->table(i, j)->getID() == 0) {
                        this->table(i, j) = new Tool(getInventoryID(FI, name),name, getInventoryType(FI, name), 10);
                        qty--;
                        return;
                    }
                }
            }
            if (!found) {
                cout << "Inventory is full" << endl; //throw
            }
        }
    }
    else if(category == "NONTOOL"){
        while (qty > 0){
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (this->table(i, j)->getName() == name) {
                        try{
                            this->table(i, j)+= qty;
                            qty = 0;
                            return;
                        }
                        catch(NonToolException &e){
                            int sisa = 64 - this->table(i, j)->getQuantity();
                            this->table(i, j) += sisa;
                            qty -= sisa;
                        }
                    }
                }
            }
            if (!found) {
                cout << "Inventory is full" << endl; //throw
            }
        }
    }
}

void Inventory::discard(string slotID,  int qty){
    if(isTool(table[slotID])){
        this->table[slotID] = new Tool(0, "-", "-", 0);
    }
    else{
        try{
            this->table[slotID]-= qty;
            if (table[slotID]->getQuantity() == 0) {
                this->table[slotID] = new NonTool(0, "-", "-", 0);
            }
        }
        catch(NonToolException &e){
            e.displayMessage();
        }
    }
    
}

void Inventory::use(const string slotID){
    try{
        this->table[slotID]->use();
        if(this->table[slotID]->getDurability()==0){
            this->table[slotID] = new NonTool(0, "-", "-", 0);
        }
    }
    catch(ToolException &e){
        e.displayMessage();
    }
}

void Inventory::moveInInventory(string slotSrc, int qty, string slotTarget){
    if (isTool(this->table[slotSrc]) || isTool(this->table[slotTarget])){
        cout << "You can't move a tool!" << endl; //throw
        return;
    }
    if (this->table[slotSrc]->getID() != this->table[slotTarget]->getID()){
        cout << "Item tidak sama" << endl; //throw
        return;
    }
    if (this->table[slotSrc]->getQuantity() < qty) {
        cout << "Item tidak mencukupi" << endl; //throw
        return;
    }

    try{
        this->table[slotTarget] += qty;
        this->table[slotSrc] -= qty;
        if(this->table[slotSrc]->getQuantity()==0){
            this->table[slotSrc] = new NonTool(0, "-", "-", 0);
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

bool Inventory::isTool(Item* i){
    try {
        i->getDurability();
        return true;
    } 
    catch (Exception&) {
        return false;
    }
}


int Inventory::getInventoryID(FileIO FI, string name){
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    bool found = false;
    // search name item in list of tool and return item ID
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return listTool[i].getID();
        }
    }
    if(!found){
        //throw
    }
}

string Inventory::getInventoryType(FileIO FI, string name){
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    bool found = false;
    // search name item in list of tool and return item type
    for (int i = 0; i < listTool.size(); i++) {
        if (listTool[i].getName() == name) {
            return listTool[i].getType();
        }
    }
    if(!found){
        //throw
    }
}

string Inventory::getCategory(FileIO FI, string name){
    vector<Tool> listTool = FI.listOfTool();
    vector<NonTool> listNonTool = FI.listOfNonTool();
    bool found = false;
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
    if (!found){
        //throw
    }
}