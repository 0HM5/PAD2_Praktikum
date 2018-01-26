// Active.cpp

#include "Active.h"

void Active::set_activation(const bool& to_activate) {
    has_been_activated = to_activate;
}

bool Active::get_activation()const {
    return has_been_activated;
}

void Active::set_passive(Passive* to_pass) {
    passive_tile = to_pass;
}

//Active::Active() {
//    has_been_activated = false;
//    char_ptr = 0;
//    passive_tile = 0;
//}
//
//Active::Active(const Active& orig) : Tile(orig) {
//}

Active::~Active() {
}