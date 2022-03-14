#include "exceptionInterface.hpp"

int Exception::numOfException = 0;

Exception::Exception(int ID) : ID(ID) {
    Exception::numOfException++;
}

Exception::Exception(const Exception& E) : ID(E.ID) {
    Exception::numOfException++;
}

int Exception::getNumOfException() {
    return Exception::numOfException;
}

int Exception::getID() const {
    return this->ID;
}