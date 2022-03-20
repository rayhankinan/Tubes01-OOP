#include "inventoryExceptionInterface.hpp"

int InventoryException::numOfInventoryException = 0;

string InventoryException::message[] = {"ID item tidak sama!"};

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