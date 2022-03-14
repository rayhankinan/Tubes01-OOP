#ifndef MATRIX_EXCEPTION_INTERFACE
#define MATRIX_EXCEPTION_INTERFACE

#include "exceptionInterface.hpp"

class MatrixException : public Exception {
    private:
        static int numOfMatrixException;
        static string message[];

    public:
        MatrixException(int); // user-defined ctor
        MatrixException(const MatrixException&); // cctor

        static int getNumOfMatrixException();  // numOfMatrixException getter

        void displayMessage() const; // message display
};

#endif
