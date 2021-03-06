#include "craftingExceptionInterface.hpp"

int CraftingException::numOfCraftingException = 0;

string CraftingException::errorMessages[] = {
    "Crafting table kosong!",
    "Gagal melakukan craft, periksa lagi konfigurasi!",
    "Jumlah item invalid!",
    "Slot sudah terisi item lain!",
    "Slot kosong/invalid",
};

CraftingException::CraftingException(int ID) : Exception(ID) {
    CraftingException::numOfCraftingException++;
}        

CraftingException::CraftingException(const CraftingException &CE) : Exception (CE.ID) {
    CraftingException::numOfCraftingException++;
}

int CraftingException::getNumOfCraftingException() {
    return CraftingException::numOfCraftingException;
}

void CraftingException::displayMessage() const {
    cout << CraftingException::errorMessages[this->Exception::ID] << endl;
}
