#include "toolExceptionInterface.hpp"

int ToolException::numOfToolException = 0;

string ToolException::message[] = {"Durability tool tidak boleh melebihi 10!", "Durability tool tidak boleh kurang dari 0!", "ID item tidak sama!", "Tool tidak bisa digunakan! Durability item 0.", "Tool tidak mempunyai atribut quantity!"};

ToolException::ToolException(int ID) : ItemException(ID) {
    ToolException::numOfToolException++;
}

ToolException::ToolException(const ToolException &TE) : ItemException(TE.ID) {
    ToolException::numOfToolException++;
}

int ToolException::getNumOfToolException() {
    return ToolException::numOfToolException;
}

void ToolException::displayMessage() const {
    cout << ToolException::message[this->Exception::ID] << endl;
}