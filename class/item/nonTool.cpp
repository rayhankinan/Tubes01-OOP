#include "nonToolInterface.hpp"

int NonTool::numOfNonTool = 0;

NonTool::NonTool() : Item() {
    this->quantity = 0;

    NonTool::numOfNonTool++;
}

NonTool::NonTool(int ID, string name, string type, int quantity) : Item(ID, name, type) {
    this->quantity = quantity;

    NonTool::numOfNonTool++;
}

NonTool::NonTool(const NonTool& NT) : Item(NT.ID, NT.name, NT.type) {
    this->quantity = NT.quantity;

    NonTool::numOfNonTool++;
}

NonTool::~NonTool() {
    NonTool::numOfNonTool--;
    // dtor Item dipanggil menggunakan fungsi virtual dtor
}

NonTool& NonTool::operator=(const NonTool& NT) {
    this->Item::operator=(NT);
    this->quantity = NT.quantity;

    return *this;
}

int NonTool::getQuantity() const {
    return this->quantity;
}

int NonTool::getDurability() const {
    throw NonToolException(4);
}

void NonTool::setQuantity(int quantity){
    this->quantity = quantity;
} 
void NonTool::setDurability(int durability){
    throw NonToolException(4);
} 

int NonTool::getNumOfNonTool() {
    return NonTool::numOfNonTool;
}

bool NonTool::isTool() {
    return false;
}

Item& NonTool::operator+=(int N) {
    if (this->quantity + N > 64) {
        throw NonToolException(0);

    } else if (this->quantity + N < 0) {
        throw NonToolException(1);

    } else {
        this->quantity += N;

        return *this;
    }
}

Item& NonTool::operator-=(int N) {
    if (this->quantity - N > 64) {
        throw NonToolException(0);
        
    } else if (this->quantity - N < 0) {
        throw NonToolException(1);

    } else {
        this->quantity -= N;

        return *this;
    }
}

Item& NonTool::operator+=(const Item &I) {
    if (this->ID != I.getID()) {
        throw NonToolException(2);

    } else if (this->quantity + I.getQuantity() > 64) {
        throw NonToolException(0);

    } else if (this->quantity + I.getQuantity() < 0) {
        throw NonToolException(1);

    } else {
        this->quantity += I.getQuantity();

        return *this;
    }
}

Item& NonTool::operator-=(const Item& I) {
    if (this->ID != I.getID()) {
        throw NonToolException(2);

    } else if (this->quantity - I.getQuantity() > 64) {
        throw NonToolException(0);

    } else if (this->quantity - I.getQuantity() < 0) {
        throw NonToolException(1);

    } else {
        this->quantity -= I.getQuantity();

        return *this;
    }
}

void NonTool::input(istream& is) {
    is >> this->ID >> this->name >> this->type;
    this->quantity = 0;
}

void NonTool::output(ostream& os) const {
    os << this->ID << ":" << this->quantity;
}

void NonTool::use() {
    throw NonToolException(3);
}

void NonTool::display() {
    this->Item::display();
    cout << "Quantity   :" << this->getQuantity() << endl;
}