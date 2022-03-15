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

        static int getNumOfNonTool(); // numOfNonTool getter

        NonTool& operator+=(int); // quantity sum and assignment with integer argument
        NonTool& operator-=(int); // quantity subtraction and assignment with integer argument

        NonTool& operator+=(const NonTool&); // quantity sum and assignment with Item argument
        NonTool& operator-=(const NonTool&); // quantity subtraction and assignment with Item argument

        void input(istream&); // input method (delegated from stream)
        void output(ostream&) const; // output method (delegated from stream)

        void use(); // use item
};

#endif