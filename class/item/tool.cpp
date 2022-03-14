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

int Tool::getDurability() const {
    return this->durability;
}

int Tool::getNumOfTool() {
    return Tool::numOfTool;
}

Tool& Tool::operator+=(int N) {
    if (this->durability + N > 10) {
        throw ToolException(0);

    } else if (this->durability + N < 0) {
        throw ToolException(1);

    } else {
        this->durability += N;

        return *this;
    }
}

Tool& Tool::operator-=(int N) {
    if (this->durability - N > 10) {
        throw ToolException(0);

    } else if (this->durability - N < 0) {
        throw ToolException(1);

    } else {
        this->durability -= N;

        return *this;
    }
}

Tool& Tool::operator+=(const Tool& T) {
    if (this->ID != T.getID()) {
        throw ToolException(2);

    } else if (this->durability + T.getDurability() > 10) {
        throw ToolException(0);

    } else if (this->durability + T.getDurability() < 0) {
        throw ToolException(1);

    } else {
        this->durability += T.getDurability();

        return *this;
    }
}

Tool& Tool::operator-=(const Tool& T) {
    if (this->ID != T.getID()) {
        throw ToolException(2);

    } else if (this->durability - T.getDurability() > 10) {
        throw ToolException(0);

    } else if (this->durability - T.getDurability() < 0) {
        throw ToolException(1);

    } else {
        this->durability -= T.getDurability();

        return *this;
    }
}

void Tool::input(istream& is) {
    is >> this->ID >> this->name >> this->type >> this->durability;
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