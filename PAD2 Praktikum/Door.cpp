// Door.cpp

#include "Door.h"

void Door::mk_abstr()const {
}

void Door::print()const {
    if (char_ptr != 0) {
        cout << *char_ptr;
        return;
    }
    else if (!status) {
        cout << "X";
        return;
    }
    else {
        cout << "/";
        return;
    }
}

bool Door::on_enter(Character* char_enter, Tile* from_tile) {
    if (status) {
        char_ptr = char_enter;
        return true;
    }
    else {
        cout << "The destination tile cannot be entered!\n";
        system("sleep 1.5");
        return false;
    }
}

bool Door::is_transparent() const{
    if (!status) {
        return false;
    }
    else {
        return true;
    }
}

bool Door::on_enter_def() const{
    if (status) {
        return true;
    }
    else {
        return false;
    }
}

Door::Door() : Passive() {
}

Door::Door(const Door& orig) : Passive() {
}

Door::~Door() {
}