#include "inventoryInterface.hpp"
#include <iostream>

using namespace std;

Inventory::Inventory(){} // default ctor
Inventory::Inventory(const Inventory&){} // cctor
Inventory::~Inventory(){} // dtor

void Inventory::show() const{}
// menambahkan item ke inventory sebanyak qty
void Inventory::give(Item*, const int qty){}
// menghapus item dari inventory sebanyak qty
void Inventory::discard(Item*, const int qty){}
// menggunakan item tool dari inventory
void Inventory::use(const string slotID){}
