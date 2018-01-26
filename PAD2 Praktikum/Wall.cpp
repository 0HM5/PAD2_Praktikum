// Wall.cpp

#include "Wall.h"
#include "Tile.h"

void Wall::mk_abstr()const {
}

void Wall::print()const {
    cout << "#";
}

bool Wall::on_enter(Character* char_enter, Tile* from_tile) {
    cout << "The destination tile cannot be entered!\n";
    system("sleep 1.5");
    return false;
}

bool Wall::on_enter_def()const {
    return false;
}

bool Wall::is_transparent() const{
    return false;
}

Wall::Wall() {
}

//Wall::Wall(const Wall& orig) : Tile(orig) {
//}

Wall::~Wall() {
}