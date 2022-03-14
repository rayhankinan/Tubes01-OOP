#ifndef ITEM_EXCEPTION_INTERFACE_HPP
#define ITEM_EXCEPTION_INTERFACE_HPP

#include "exceptionInterface.hpp"

class ItemException : public Exception {
    protected:
        static int numOfItemException;

    public:
        ItemException(int); // user-defined ctor
        ItemException(const ItemException&); // cctor

        static int getNumOfItemException(); // numOfItemException getter
};

#endif