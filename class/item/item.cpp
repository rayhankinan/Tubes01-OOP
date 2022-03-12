#include "itemInterface.hpp"

int Item::numOfItem = 0;

Item::Item() {
    this->ID = 0;
    this->name = "";
    this->type = "";
    this->quantity = 0;

    Item::numOfItem++;
}

Item::Item(int ID, string name, string type, int quantity) {
    this->ID = ID;
    this->name = name;
    this->type = type;
    this->quantity = quantity;

    Item::numOfItem++;
}

Item::Item(const Item& I) {
    this->ID = I.ID;
    this->name = I.name;
    this->type = I.type;
    this->quantity = quantity;

    Item::numOfItem++;
}

Item::~Item() {
    Item::numOfItem--;
}

Item& Item::operator=(const Item& I) {
    this->ID = I.ID;
    this->name = I.name;
    this->type = I.type;
    this->quantity = quantity;

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

int Item::getQuantity() const {
    return this->quantity;
}

Item& Item::operator++() {
    ++this->quantity;
    return *this;
}

Item& Item::operator--() {
    --this->quantity;
    return *this;
}

Item Item::operator++(int) {
    this->quantity++;

    return *this;
}

Item Item::operator--(int) {
    this->quantity--;

    return *this;
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