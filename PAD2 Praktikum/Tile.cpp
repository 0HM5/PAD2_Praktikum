//Tile.cpp

#include "Tile.h"

Character* Tile::get_char()const {
    return char_ptr;
}

bool Tile::hasCharacter()const {
    if (char_ptr == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void Tile::set_character(Character* char_to) {
    char_ptr = char_to;
}

void Tile::on_leave(Tile* to_tile) {
    if (to_tile->on_enter(char_ptr, to_tile)) {
        char_ptr = nullptr;
    }
}

bool Tile::on_enter(Character* char_enter, Tile* from_tile) {
    char_ptr = char_enter;
    return true;
}

bool Tile::on_enter_def()const {
    return true;
}

bool Tile::is_transparent()const {
    return true;
}

//Tile::Tile() :
//char_ptr(nullptr) {
//        type = type_to;
//        char_ptr = nullptr;
//}

Tile::Tile(){
    char_ptr = 0;
}

//Tile::Tile(const Tile& orig) {
//    
//    char_ptr = orig.get_char();
//}

Tile::~Tile() {
}