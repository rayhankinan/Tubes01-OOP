#include "matrixExceptionInterface.hpp"

int MatrixException::numOfMatrixException = 0;

string MatrixException::message[] = {
    "Indeks diluar batas matriks!",
    "SlotID invalid!"
};

MatrixException::MatrixException(int ID) : Exception(ID) {
    MatrixException::numOfMatrixException++;
}

MatrixException::MatrixException(const MatrixException &ME) : Exception(ME.ID) {
    MatrixException::numOfMatrixException++;
}

int MatrixException::getNumOfMatrixException() {
    return MatrixException::numOfMatrixException;
}

void MatrixException::displayMessage() const {
    cout << MatrixException::message[this->ID] << endl;
}