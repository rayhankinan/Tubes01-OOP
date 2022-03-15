#include "toolInterface.hpp"

int Tool::numOfTool = 0;

Tool::Tool() : Item() {
    this->durability = 0;

    Tool::numOfTool++;
}

Tool::Tool(int ID, string name, string type, int durability) : Item(ID, name, type) {
    this->durability = durability;

    Tool::numOfTool++;
}

Tool::Tool(const Tool& T) : Item(T.ID, T.name, T.type) {
    this->durability = T.durability;

    Tool::numOfTool++;
}

Tool::~Tool() {
    Tool::numOfTool--;
    // dtor Item dipanggil menggunakan fungsi virtual dtor
}

Tool& Tool::operator=(const Tool& T) {
    this->Item::operator=(T);
    this->durability = durability;

    return *this;
}

int Tool::getQuantity() const {
    throw ToolException(4);
}

int Tool::getDurability() const {
    return this->durability;
}

int Tool::getNumOfTool() {
    return Tool::numOfTool;
}

Item& Tool::operator+=(int N) {
    if (this->durability + N > 10) {
        throw ToolException(0);

    } else if (this->durability + N < 0) {
        throw ToolException(1);

    } else {
        this->durability += N;

        return *this;
    }
}

Item& Tool::operator-=(int N) {
    if (this->durability - N > 10) {
        throw ToolException(0);

    } else if (this->durability - N < 0) {
        throw ToolException(1);

    } else {
        this->durability -= N;

        return *this;
    }
}

Item& Tool::operator+=(const Item& I) {
    if (this->ID != I.getID()) {
        throw ToolException(2);

    } else if (this->durability + I.getDurability() > 10) {
        throw ToolException(0);

    } else if (this->durability + I.getDurability() < 0) {
        throw ToolException(1);

    } else {
        this->durability += I.getDurability();

        return *this;
    }
}

Item& Tool::operator-=(const Item& I) {
    if (this->ID != I.getID()) {
        throw ToolException(2);

    } else if (this->durability - I.getDurability() > 10) {
        throw ToolException(0);

    } else if (this->durability - I.getDurability() < 0) {
        throw ToolException(1);

    } else {
        this->durability -= I.getDurability();

        return *this;
    }
}

void Tool::input(istream& is) {
    is >> this->ID >> this->name >> this->type;
    this->durability = 10;
}

void Tool::output(ostream& os) const {
    os << this->ID << ":" << this->durability;
}

void Tool::use() {
    if (this->durability <= 0) {
        throw ToolException(3);
    } else {
        this->durability--;
    }
}