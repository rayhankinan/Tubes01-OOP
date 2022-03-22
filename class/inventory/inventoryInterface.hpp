#ifndef INVENTORY_INTERFACE_HPP
#define INVENTORY_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
#include "../exception/exceptionInterface.hpp"
#include "../exception/matrixExceptionInterface.hpp"
#include "../exception/nonToolExceptionInterface.hpp"
#include "../exception/toolExceptionInterface.hpp"
#include "../exception/inventoryExceptionInterface.hpp"
#include "../fileIO/fileIOInterface.hpp"

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
        
        void show() const;

        // menambahkan item ke inventory sebanyak qty
        void give(string name, int qty);

        // menghapus item dari inventory sebanyak qty
        void discard(string slotID, int qty);

        // menggunakan item tool dari inventory
        void use(const string slotID);

        // Menumpuk item. Dua buah item nontool yang sama dapat ditumpuk
        void moveInInventory(string slotSrc, int qty, string slotTarget);
        
        // get table element based on slotID
        Item*& getElmt(string);
            
        // set table element based on slotID
        void setElmt(string, Item*);

        bool isTool(Item*);

        int getInventoryID(FileIO, string);

        string getInventoryType(FileIO, string);

        string getCategory(FileIO, string);




};

#endif