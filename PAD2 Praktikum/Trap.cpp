
#include "Trap.h"
#include "Character.h"

// Trap.cpp

void Trap::mk_abstr() const {
}

void Trap::print() const {
    if (char_ptr != 0) {
        cout << *char_ptr;
    }
    else if (!triggered) {
        cout << ".";
    }
    else {
        cout << "T";
    }
}

bool Trap::on_enter(Character* char_enter, Tile* from_tile) {
    if (char_enter == 0) {
        char_ptr = 0;
        return true;
    }
    char_ptr = char_enter;
    if (!triggered) {
        char_ptr->change_hp(-20);
        triggered = true;
    }
    return true;
}

bool Trap::on_enter_def() const {
    if (!triggered) {
        return false;
    }
    return true;
}

Trap::Trap() {
    triggered = false;
}

//Trap::Trap(const Trap& orig) {
//}

Trap::~Trap() {
}