#include "itemInterface.hpp"

int Item::numOfItem = 0;

Item::Item() {
    this->ID = 0;
    this->name = "-";
    this->type = "-";

    Item::numOfItem++;
}

Item::Item(int ID, string name, string type) {
    this->ID = ID;
    this->name = name;
    this->type = type;

    Item::numOfItem++;
}

Item::Item(const Item& I) {
    this->ID = I.ID;
    this->name = I.name;
    this->type = I.type;

    Item::numOfItem++;
}

Item::~Item() {
    Item::numOfItem--;
}

Item& Item::operator=(const Item& I) {
    this->ID = I.ID;
    this->name = I.name;
    this->type = I.type;

    return *this;
}

int Item::getID() const {
    return this->ID;
}

void Item::setID(int ID) {
    this->ID = ID;
}

string Item::getName() const {
    return this->name;
}

void Item::setName(string name) {
    this->name = name;
}

string Item::getType() const {
    return this->type;
}

void Item::setType(string type) {
    this->type = type;
}

int Item::getNumOfItem() {
    return Item::numOfItem;
}

istream& operator>>(istream& is, Item& I) {
    I.input(is);

    return is;
}

ostream& operator<<(ostream& os, const Item& I) {
    I.output(os);

    return os;
}

void Item::display(){
    cout << "ID         : " << this->getID() << endl;
    cout << "Name       : " << this->getName() << endl;
    cout << "Type       : " << this->getType() << endl;
}