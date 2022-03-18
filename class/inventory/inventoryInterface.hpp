#ifndef INVENTORY_INTERFACE_HPP
#define INVENTORY_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
#include "../exception/exceptionInterface.hpp"
#include "../exception/matrixExceptionInterface.hpp"

class Inventory {
    private:
        static const int length = 3;
        static const int width = 9;

        // create Matrix of pointers to items
        Matrix<Item*> table = Matrix<Item*>(length, width);

    public:
        Inventory(); // default ctor
        Inventory(const Inventory&); // cctor
        ~Inventory(); // dtor
        template<class T>
        
        void show() const;
        // menambahkan item ke inventory sebanyak qty
        void give(Item*, const int qty);
        // menghapus item dari inventory sebanyak qty
        void discard(Item*, const int qty);
        // menggunakan item tool dari inventory
        void use(const string slotID);

};

#endif