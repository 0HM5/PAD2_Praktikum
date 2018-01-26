// Switch.cpp

#include "Switch.h"

void Switch::mk_abstr()const {
}

void Switch::print()const {
    if (char_ptr != 0) {
        cout << *char_ptr;
        return;
    }
    else
        if (!has_been_activated) {
        cout << "?";
        return;
    }
    else {
        cout << "!";
        return;
    }
}

bool Switch::on_enter(Character* char_enter, Tile* from_tile) {
    has_been_activated = true;
    passive_tile->set_status(true);

    char_ptr = char_enter;
    return true;
}

Switch::Switch() {
}

//Switch::Switch(const Switch& orig) {
//}

Switch::~Switch() {
}