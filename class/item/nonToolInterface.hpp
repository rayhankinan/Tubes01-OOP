#ifndef NONTOOL_INTERFACE_HPP
#define NONTOOL_INTERFACE_HPP

#include "itemInterface.hpp"

class NonTool : public Item {
    private:
        static int numOfNonTool;

    public:
        NonTool(); // default ctor
        NonTool(int, string, string, int); // user-defined ctor
        NonTool(const NonTool&); // cctor
        ~NonTool(); // dtor
        
        NonTool& operator=(const NonTool&); // assignment operator

        static int getNumOfNonTool(); // numOfNonTool getter

        Item& operator+=(int); // quantity sum and assignment with integer argument
        Item& operator-=(int); // quantity subtraction and assignment with integer argument
        Item operator+(int) const; // quantity sum with integer argument
        Item operator-(int) const; // quantity subtraction with integer argument

        Item& operator+=(const Item&); // quantity sum and assignment with Item argument
        Item& operator-=(const Item&); // quantity subtraction and assignment with Item argument
        Item operator+(const Item&) const; // quantity sum with Item argument
        Item operator-(const Item&) const; // quantity subtraction with Item argument

        void input(istream&); // input method (delegated from stream)
        void output(ostream&) const; // output method (delegated from stream)
};

#endif