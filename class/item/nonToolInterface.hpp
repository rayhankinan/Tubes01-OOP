#ifndef NONTOOL_INTERFACE_HPP
#define NONTOOL_INTERFACE_HPP

#include "itemInterface.hpp"
#include "../exception/nonToolExceptionInterface.hpp"

class NonTool : public Item {
    private:
        static int numOfNonTool;

        int quantity;

    public:
        NonTool(); // default ctor
        NonTool(int, string, string, int); // user-defined ctor
        NonTool(const NonTool&); // cctor
        ~NonTool(); // dtor
        
        NonTool& operator=(const NonTool&); // assignment operator

        int getQuantity() const; // quantity getter
        int getDurability() const; // durability getter
        void setQuantity(int); // quantity setter
        void setDurability(int); // durability setter

        static int getNumOfNonTool(); // numOfNonTool getter

        bool isTool();

        Item& operator+=(int); // quantity sum and assignment with integer argument
        Item& operator-=(int); // quantity subtraction and assignment with integer argument

        Item& operator+=(const Item&); // quantity sum and assignment with Item argument
        Item& operator-=(const Item&); // quantity subtraction and assignment with Item argument

        void input(istream&); // input method (delegated from stream)
        void output(ostream&) const; // output method (delegated from stream)

        void use(); // use item
        void display(); // display
};

#endif