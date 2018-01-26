// StationaryController.cpp

#include "StationaryController.h"

int StationaryController::move() const {
    return 5;
}

int StationaryController::get_type() const{
    return 1;
}

StationaryController::StationaryController(Character* char_to) : Controller(nullptr) {
    char_ptr_c = char_to;
}

StationaryController::StationaryController() : Controller(nullptr) {
}

//StationaryController::StationaryController(const StationaryController& orig) {
//}

StationaryController::~StationaryController() {
}