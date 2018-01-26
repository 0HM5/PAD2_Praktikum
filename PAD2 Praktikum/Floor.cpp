// Floor.cpp

#include "Floor.h"

void Floor::mk_abstr()const {
}

void Floor::print()const {
    if (char_ptr != nullptr) {
        cout << *char_ptr;
        return;
    }
    else if (pickup != nullptr) {
        cout << "*";
    }
    else {
        cout << ".";
        return;
    }
}

bool Floor::on_enter(Character* char_enter, Tile* from_tile) {
    char_ptr = char_enter;
    if(pickup != 0){
        char_enter -> add_item(pickup);
        pickup = 0;
    }
    return true;
}

void Floor::setPickup(Item* ground){
    pickup = ground;
}

Floor::Floor() {
    pickup = 0;
}

//Floor::Floor(const Floor& orig) : Tile(orig) {
//}

Floor::~Floor() {
    if(pickup != 0){
        delete pickup;
    }
}