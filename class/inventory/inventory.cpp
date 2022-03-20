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
                cout << "[I" << i*9+j << "|empty] ";
                if (j == 8) {
                    cout << endl;
                }
            }
            else {
                if(isTool(table(i, j))){
                    cout << "[I" << i*9+j << "|" << this->table(i, j)->getName() << "|" << this->table(i, j)->getDurability() << "] ";
                    if (j == 8) {
                        cout << endl;
                    }
                }
                else{
                    cout << "[I" << i*9+j << "|" << this->table(i, j)->getName() << "|" << this->table(i, j)->getQuantity() << "] ";
                    if (j == 8) {
                        cout << endl;
                    }
                }
            }
        }
    }
}

// Menambahkan Item ke Inventory. Sejumlah Item dengan jenis yang sama akan ditambahkan ke slot inventory:
// Berisi item nontool dengan jenis yang sama
// Memiliki quantity < 64 (tidak penuh)
// Apabila tidak ditemukan slot yang memenuhi syarat tersebut, item ditambahkan pada slot kosong. Penambahan item dilakukan dari ID inventory terkecil.
void Inventory::give(string name, const int qty){
    bool found = false;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (this->table(i, j)->getName() == name) {
                try{
                    this->table(i, j)+= qty;
                    found = true;
                    return;
                }
                catch(NonToolException &e){
                    e.displayMessage();
                }
            }
        }
    }
    if(!found) {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (this->table(i, j)->getID() == 0) {
                    // this->table(i, j) = new NonTool(id ,name, type, qty); menunggu get id dari item.txt
                    try{
                        this->table(i, j)+= qty;
                        found = true;
                        return;
                    }
                    catch(NonToolException &e){
                        e.displayMessage();
                    }
                }
            }
        }
        if(!found){
            cout << "Inventory is full" << endl;
        }
    }
}

// menghapus item dari inventory sebanyak qty
// Membuang item di slot inventory dengan kuantitas yang diberikan. Gagal bila kuantitas item lebih kecil dari item yang dijadikan masukan perintah.
// DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>
// DISCARD I0 32
// I.S. : Kuantitas item lebih besar sama dengan item pada ITEM_QTY.
// F.S. : Item pada inventory slot INVENTORY_SLOT_ID berkurang sebanyak ITEM_QTY. Hapus item pada slot bila item pada INVENTORY_SLOT_ID = 0.
void Inventory::discard(string slotID, const int qty){
    try{
        this->table[slotID]-=qty;
        try {
            if (this->table[slotID]->getQuantity() == 0) { //nontool
                this->table[slotID] = new NonTool(0, "-", "-", 0);
            }
        }
        catch (const NonToolException &e) { //tool
            if (this->table[slotID]->getDurability() == 0){
                this->table[slotID] = new Tool(0, "-", "-", 0);
            }
        }
    }
    catch(const NonToolException &e){
        e.displayMessage();
    }
    catch(const ToolException &e){
        e.displayMessage();
    }
}

// menggunakan item tool dari inventory
// USE <INVENTORY_SLOT_ID>
// USE I0
// I.S. : INVENTORY_SLOT_ID berisi Item tool.
// F.S. : Durability Item pada INVENTORY_SLOT_ID berkurang 1. Jika durabilitynya mencapai 0, maka item hilang dari inventory.
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

// // Menumpuk Item. Dua buah item non tool yang sama pada inventory dapat ditumpuk.
// Menumpuk Item. Dua buah item non tool yang sama pada inventory dapat ditumpuk.
// MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>
// MOVE I0 1 I1
// I.S. :
// Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak Qty1.
// Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty2.
// F.S. :
// Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak 0 (item hilang / habis), jika memungkinkan.
// Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty1 + Qty2, namun maksimal sebanyak 64.
void Inventory::moveInInventory(string slotSrc, int qty, string slotTarget){
    if(!isTool(this->table[slotSrc]) && !isTool(this->table[slotTarget])){
        if (this->table[slotSrc]->getID() == this->table[slotTarget]->getID()){
            if (this->table[slotSrc]->getQuantity() >= qty) {
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
            else{
                cout << "Item tidak mencukupi" << endl;
            }
        }
        else{
            cout << "Item tidak sama" << endl;
        }
    }
    else{
        cout << "You can't move a tool!" << endl;
    }
}


 // get table element based on slotID
Item*& Inventory::getElmt(string slotID) const{
    return this->table[slotID];
}

void Inventory::setElmt(string slotID, Item* item){
    this->table[slotID] = item;
}