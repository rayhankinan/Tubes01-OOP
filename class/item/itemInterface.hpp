#ifndef ITEM_INTERFACE_HPP
#define ITEM_INTERFACE_HPP

#include <iostream>
#include <string>
using namespace std;

class Item {
    protected:
        static int numOfItem;

        int ID;
        string name;
        string type;
        int quantity;

    public:
        Item(); // default ctor
        Item(int, string, string, int); // user-defined ctor
        Item(const Item&); // cctor
        virtual ~Item(); // virtual dtor
        
        Item& operator=(const Item&); // assignment operator

        int getID() const; // ID getter
        void setID(int); // ID setter

        string getName() const; // name getter
        void setName(string); // name setter

        string getType() const; // type getter
        void setType(string); // type setter

        int getQuantity() const; // quantity getter

        static int getNumOfItem(); // numOfItem getter

        friend istream& operator>>(istream&, Item&); // input stream
        friend ostream& operator<<(ostream&, const Item&); // output stream

        virtual Item& operator+=(int) = 0; // quantity sum and assignment with integer argument
        virtual Item& operator-=(int) = 0; // quantity subtraction and assignment with integer argument
        virtual Item operator+(int) const = 0; // quantity sum with integer argument
        virtual Item operator-(int) const = 0; // quantity subtraction with integer argument

        virtual Item& operator+=(const Item&) = 0; // quantity sum and assignment with Item argument
        virtual Item& operator-=(const Item&) = 0; // quantity subtraction and assignment with Item argument
        virtual Item operator+(const Item&) const = 0; // quantity sum with Item argument
        virtual Item operator-(const Item&) const = 0; // quantity subtraction with Item argument

        virtual void input(istream&) = 0; // input method (delegated from stream)
        virtual void output(ostream&) const = 0; // output method (delegated from stream)
};

#endif