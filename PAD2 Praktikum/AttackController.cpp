//AttackController.cpp

#include "AttackController.h"

int AttackController::move() const {
    position from, to;
    try {
        from = map->findCharacter(char_ptr_c);
        to = map->findCharacter(att);
    }
    catch (const invalid_argument& ia) {
        return 5;
    }

    vector<position> to_visit = map->getPathTo(from, to);

    if (to_visit.empty()) {
        return 5;
    }

    position next = to_visit[0];

    if (next.row == from.row + 1 && next.column == from.column - 1) {
        return 1;
    }
    else if (next.row == from.row + 1 && next.column == from.column) {
        return 2;
    }
    else if (next.row == from.row + 1 && next.column == from.column + 1) {
        return 3;
    }
    else if (next.row == from.row && next.column == from.column - 1) {
        return 4;
    }
    else if (next.row == from.row && next.column == from.column) {
        return 5; // no idea why that would be the case
    }
    else if (next.row == from.row && next.column == from.column + 1) {
        return 6;
    }
    else if (next.row == from.row - 1 && next.column == from.column - 1) {
        return 7;
    }
    else if (next.row == from.row - 1 && next.column == from.column) {
        return 8;
    }
    else if (next.row == from.row - 1 && next.column == from.column + 1) {
        return 9;
    }
    throw invalid_argument("The next position for the attk controller cannot be interpreted.");
}

void AttackController::set_attk(Character* to_att) {
    att = to_att;
}

void AttackController::set_map(DungeonMap* dumap) {
    map = dumap;
}

int AttackController::get_type() const {
    return 2;
}

AttackController::AttackController(DungeonMap* dumap, Character* to_att, Character* char_to) : Controller(char_to) {
    map = dumap;
    att = to_att;
}

AttackController::AttackController() : Controller(nullptr) {
}

//AttackController::AttackController(const AttackController& orig) {
//}

AttackController::~AttackController() {
}