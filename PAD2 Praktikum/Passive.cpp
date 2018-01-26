// Passive.cpp

#include "Passive.h"

bool Passive::get_status() const {
    return status;
}

void Passive::set_status(const bool& status_to) {
    status = status_to;
}

void Passive::toggle_status(){
    status = !status;
}

Passive::Passive() {
    char_ptr = 0;
    status = false;
}

//Passive::Passive(const Passive& orig) : Tile(orig) {
//}

Passive::~Passive() {
}