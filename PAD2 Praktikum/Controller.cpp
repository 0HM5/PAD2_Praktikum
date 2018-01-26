// Controller.cpp

#include "Controller.h"

void Controller::set_char(Character* char_to) {
    char_ptr_c = char_to;
}

Character* Controller::get_char()const {
    return char_ptr_c;
}

Controller::Controller(Character* char_to) {
    char_ptr_c = char_to;
}

//Controller::Controller() {
//    char_ptr_c = 0;
//}
//
//Controller::Controller(const Controller& orig) {
//}

Controller::~Controller() {
}