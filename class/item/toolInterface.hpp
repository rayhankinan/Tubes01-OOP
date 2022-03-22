#ifndef TOOL_INTERFACE_HPP
#define TOOL_INTERFACE_HPP

#include "itemInterface.hpp"
#include "../exception/toolExceptionInterface.hpp"

class Tool : public Item {
    private:
        static int numOfTool;
        
        int durability;

    public:
        Tool(); // default ctor
        Tool(int, string, string, int); // user-defined ctor
        Tool(const Tool&); // cctor
        ~Tool(); // dtor

        Tool& operator=(const Tool&); // operator assignment

        int getQuantity() const; // quantity getter
        int getDurability() const; // durability getter
        void setQuantity(int); // quantity setter
        void setDurability(int); // durability setter

        static int getNumOfTool(); // numOfTool getter

        bool isTool();

        Item& operator+=(int); // durability sum and assignment with integer argument
        Item& operator-=(int); // durability subtraction and assignment with integer argument

        Item& operator+=(const Item&); // durability sum and assignment with Item argument
        Item& operator-=(const Item&); // durability subtraction and assignment with Item argument

        void input(istream&); // input method (delegated from stream)
        void output(ostream&) const; // output method (delegated from stream)

        void use(); // use item
        void display(); // display tool
};

#endif