#ifndef INVENTORY_EXCEPTION_INTERFACE_HPP
#define INVENTORY_EXCEPTION_INTERFACE_HPP

#include "exceptionInterface.hpp"

class InventoryException : public Exception {
    private:
        static int numOfInventoryException;
        static string message[];
    public:
        InventoryException(int); // user-defined ctor
        InventoryException(const InventoryException&); // cctor

        static int getNumOfInventoryException();  // numOfInventoryException getter

        void displayMessage() const; // message display
};

#endif 