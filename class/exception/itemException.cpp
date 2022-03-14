#include "itemExceptionInterface.hpp"

int ItemException::numOfItemException = 0;

ItemException::ItemException(int ID) : Exception(ID) {
    ItemException::numOfItemException++;
}

ItemException::ItemException(const ItemException& IE) : Exception(IE.ID) {
    ItemException::numOfItemException++;
}

int ItemException::getNumOfItemException() {
    return ItemException::numOfItemException;
}