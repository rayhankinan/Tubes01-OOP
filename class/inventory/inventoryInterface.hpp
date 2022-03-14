#ifndef INVENTORY_INTERFACE_HPP
#define INVENTORY_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/itemInterface.hpp"

class Inventory {
    private:
        Matrix<Item> table = Matrix<Item>(3, 9);

    public:
        Inventory(); // default ctor
};

#endif