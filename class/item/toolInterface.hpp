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

        int getDurability() const; // durability getter

        static int getNumOfTool(); // numOfTool getter

        Tool& operator+=(int); // durability sum and assignment with integer argument
        Tool& operator-=(int); // durability subtraction and assignment with integer argument

        Tool& operator+=(const Tool&); // durability sum and assignment with Item argument
        Tool& operator-=(const Tool&); // durability subtraction and assignment with Item argument

        void input(istream&); // input method (delegated from stream)
        void output(ostream&) const; // output method (delegated from stream)

        void use(); // use item
};

#endif