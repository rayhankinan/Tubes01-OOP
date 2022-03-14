#ifndef ITEM_INTERFACE_HPP
#define ITEM_INTERFACE_HPP

#include <iostream>
#include <string>
using namespace std;

class Item {
    private:
        static int numOfItem;

        int ID;
        string name;
        string type;
        int quantity;

    public:
        Item(); // default ctor
        Item(int, string, string, int); // user-defined ctor
        Item(const Item&); // cctor
        ~Item(); // dtor
        Item& operator=(const Item&); // assignment operator

        int getID() const; // ID getter
        void setID(int); // ID setter

        string getName() const; // name getter
        void setName(string); // name setter

        string getType() const; // type getter
        void setType(string); // type setter

        int getQuantity() const; // quantity getter
        Item& operator++(); // quantity prefix increment
        Item& operator--(); // quantity prefix decrement
        Item operator++(int); // quantity postfix increment
        Item operator--(int); // quantity postfix decrement

        static int getNumOfItem(); // numOfItem getter

        friend istream& operator>>(istream&, Item&); // input stream
        friend ostream& operator<<(ostream&, const Item&); // output stream

        virtual void input(istream&) = 0; // input method (delegated from stream)
        virtual void output(ostream&) const = 0; // output method (delegated from stream)
};

#endif