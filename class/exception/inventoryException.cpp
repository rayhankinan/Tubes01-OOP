#include "inventoryExceptionInterface.hpp"

int InventoryException::numOfInventoryException = 0;

string InventoryException::message[] = {"Inventory Penuh!", "You can't move a tool!", "Item yang ditumpuk tidak sama", "Quantity item asal tidak mencukupi", "Item tidak terdaftar"};

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