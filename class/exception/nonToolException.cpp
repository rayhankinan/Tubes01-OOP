#include "nonToolExceptionInterface.hpp"

int NonToolException::numOfNonToolException = 0;

string NonToolException::message[] = {/* ISI DENGAN PESAN KESALAHAN */};

NonToolException::NonToolException(int ID) : ItemException(ID) {
    NonToolException::numOfNonToolException++;
}

NonToolException::NonToolException(const NonToolException &NTE) : ItemException(NTE.ID) {
    NonToolException::numOfNonToolException++;
}

int NonToolException::getNumOfNonToolException() {
    return NonToolException::numOfNonToolException;
}

void NonToolException::displayMessage() const {
    cout << NonToolException::message[this->Exception::ID] << endl;
}