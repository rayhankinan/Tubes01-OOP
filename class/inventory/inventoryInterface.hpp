#ifndef INVENTORY_INTERFACE_HPP
#define INVENTORY_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/itemInterface.hpp"

class Inventory {
    private:
        static const int length = 3;
        static const int width = 9;

        Matrix<Item> table = Matrix<Item>(length, width);

    public:
        Inventory(); // default ctor
};

#endif