#include "helper.hpp"

bool isTool(Item* i){
    try {
        i->getDurability();
        return true;
    } catch (Exception&) {
        return false;
    }
}