#ifndef HELPER_HPP
#define HELPER_HPP

#include "../collection/matrixInterface.hpp"
#include "../item/itemInterface.hpp"
#include "../item/nonToolInterface.hpp"
#include "../item/toolInterface.hpp"
#include "../exception/exceptionInterface.hpp"
#include "../exception/matrixExceptionInterface.hpp"
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

void setItemToNone(Item* i){
    i->setID(0);
    i->setName("");
    i->setType("");
    if(isTool(i)){
        i -= i->getDurability();
    }
    else{
        i -= i->getQuantity();
    }
}

#endif