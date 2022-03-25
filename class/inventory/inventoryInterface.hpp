#ifndef INVENTORY_INTERFACE_HPP
#define INVENTORY_INTERFACE_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
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

        // menambahkan tool hasil crafting
        void give(string name, int dur, int qty);

        // menghapus item dari inventory sebanyak qty
        void discard(string slotID, int qty);

        // menggunakan item tool dari inventory
        void use(const string slotID);

        // Menumpuk item. Dua buah item nontool yang sama dapat ditumpuk
        void moveInInventory(string slotSrc, int qty, string slotTarget);

        // EXPORT
        void EXPORT(string);

        // peek item and recipes
        void peek(string);

        // get table element based on slotID
        Item*& getElmt(string);
            
        // set table element based on slotID
        void setElmt(string, Item*);

        //get table element based on name
        int getInventoryID(string);

        string getInventoryType(string);

        string getCategory(string);




};

#endif