#include "../collection/matrixInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
#include "../exception/exceptionInterface.hpp"
#include "../exception/matrixExceptionInterface.hpp"
#include "../fileIO/fileInputInterface.hpp"
#include <iostream>

using namespace std;

bool isTool(Item* i){
    try {
        i->getDurability();
        return true;
    } catch (Exception&) {
        return false;
    }
}


int getItemID(FileInput FI, string name){
    FI.listOfTool();
    // search name item in list of tool and return item ID
    for (int i = 0; i < FI.listOfTool().size(); i++){
        if (FI.listOfTool()[i].getName() == name){
            return FI.listOfTool()[i].getID();
        }
    }
}

string getItemType(FileInput FI, string name){
    FI.listOfTool();
    // search name item in list of tool and return item type
    for (int i = 0; i < FI.listOfTool().size(); i++){
        if (FI.listOfTool()[i].getName() == name){
            return FI.listOfTool()[i].getType();
        }
    }
}

