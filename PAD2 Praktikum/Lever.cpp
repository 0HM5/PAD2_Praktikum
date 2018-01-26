// Lever.cpp
#include "Lever.h"

void Lever::mk_abstr()const {
}

void Lever::print()const {
    if (char_ptr != 0) {
        cout << *char_ptr;
        return;
    }
    else
        if (!has_been_activated) {
        cout << "1";
        return;
    }
    else {
        cout << "2";
        return;
    }
}

bool Lever::on_enter(Character* char_enter, Tile* from_tile) {
    passive_tile->toggle_status();
    char_ptr = char_enter;
    return true;
}

bool Lever::on_enter_def()const {
    return true;
}

Lever::Lever() {
}

//Lever::Lever(const Lever& orig) {
//}

Lever::~Lever() {
}