#ifndef ITEM_EXCEPTION_HPP
#define ITEM_EXCEPTION_HPP

#include "exceptionInterface.hpp"

class ItemException : public Exception {
    protected:
        static int numOfItemException;

    public:
        // tidak memerlukan default ctor (tidak ada list of exception), cctor (tidak ada assignment), dan dtor (perlunya perhitungan jumlah object Exception setelah dihapus)
        ItemException(int); // user-defined ctor
        ItemException(const ItemException&); // cctor

        static int getNumOfItemException(); // numOfItemException getter
};

#endif