#include "toolExceptionInterface.hpp"

int ToolException::numOfToolException = 0;

string ToolException::message[] = {/* ISI DENGAN PESAN KESALAHAN */};

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