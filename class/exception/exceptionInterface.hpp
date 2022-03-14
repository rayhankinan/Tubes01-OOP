#ifndef EXCEPTION_INTERFACE_HPP
#define EXCEPTION_INTERFACE_HPP

#include <string>
#include <iostream>
using namespace std;

class Exception {
    protected:
        static int numOfException;
        static string *message;

        const int ID;

    public:
        // tidak memerlukan default ctor (tidak ada list of exception), cctor (tidak ada assignment), dan dtor (perlunya perhitungan jumlah object Exception setelah dihapus)
        Exception(int); // user-defined ctor
        Exception(const Exception&); // cctor

        static int getNumOfException(); // numOfException getter

        virtual void displayMessage() const = 0; // message display
};

#endif