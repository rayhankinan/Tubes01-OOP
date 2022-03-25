#include "inventoryExceptionInterface.hpp"

int InventoryException::numOfInventoryException = 0;

string InventoryException::message[] = {"Inventory Penuh!", "Kamu tidak bisa memindahkan tool", "Item yang ditumpuk tidak sama", "Quantity item asal tidak mencukupi", "Item tidak terdaftar", "Slot kosong", "Pindah 1 item saja!", "Quantity harus lebih dari 0", "Quantity salah", "Recipe tidak tersedia", "Quantity Tool hanya 1"};

InventoryException::InventoryException(int ID) : Exception(ID) {
    InventoryException::numOfInventoryException++;
}

InventoryException::InventoryException(const InventoryException &IE) : Exception(IE.ID) {
    InventoryException::numOfInventoryException++;
}

int InventoryException::getNumOfInventoryException() {
    return InventoryException::numOfInventoryException;
}

void InventoryException::displayMessage() const {
    cout << InventoryException::message[this->Exception::ID] << endl;
}