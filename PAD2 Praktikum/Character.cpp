//Character.cpp

#include "Character.h"
#include "Controller.h"

int Character::move()const {
    return cont->move();
}


unsigned int Character::get_max_hp()const {
    return 5;
    return 20 + get_stamina() * 5;
}

void Character::show_info()const {
    cout << " HP: " << hitpoints << "\n Stam: " << get_stamina() << "\n strength: " << get_strength() << "\n";
    return;
}

void Character::add_item(Item* to_add) {
    items.push_back(to_add);
    return;
}

unsigned int Character::get_strength()const {
    unsigned int size = items.size();
    unsigned int str = strength;
    for (unsigned int counter = 0; counter < size; counter++) {
        str = str + items[counter]->modify_strength(strength);
    }
    return str;
}

unsigned int Character::get_stamina()const {
    unsigned int size = items.size();
    unsigned int stam = stamina;
    for (unsigned int counter = 0; counter < size; counter++) {
        stam = stam + items[counter]->modify_stamina(strength);
    }
    return stam;
}

void Character::change_hp(const int& change) {
    hitpoints = hitpoints + change;
    return;
}

int Character::get_hp() const {
    return hitpoints;
}

Controller* Character::get_cont() const{
    return cont;
}

int Character::get_cont_type() const{
    return cont->get_type();
}

ostream& operator<<(ostream& os, const Character& to_output){
    os << to_output.symbol;
    return os;
}

Character::Character(const char& symbol_to, const unsigned int& strength_to, const unsigned int& stamina_to, Controller* contr) {
    symbol = symbol_to;
    strength = strength_to;
    stamina = stamina_to;
    hitpoints = get_max_hp();
    cont = contr;
}

//Character::Character() {
//    symbol = '0';
//}
//
//Character::Character(const Character& orig) {
//    symbol = orig.get_symbol();
//}

Character::~Character() {
    unsigned int size = items.size();
    for (unsigned int counter = 0; counter < size; counter++) {
        delete items[counter];
    }
}