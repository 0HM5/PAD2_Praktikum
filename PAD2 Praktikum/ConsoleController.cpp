// ConsoleController.cpp
#include "ConsoleController.h"

int ConsoleController::move()const {
    char input;
    int output = 5;
    bool valid_input = false;
    cout << "Enter which direction you would like to move: ";
    cin >> input;
    cin.clear();
    cin.ignore(1000, '\n');

    switch (input) {
    case '0':
        valid_input = true;
        output = 0;
        break;
    case '1': cout << "bottom left\n";
        valid_input = true;
        output = 1;
        break;
    case '2': cout << "bottom\n";
        valid_input = true;
        output = 2;
        break;
    case '3': cout << "bottom right\n";
        valid_input = true;
        output = 3;
        break;
    case '4': cout << "left\n";
        valid_input = true;
        output = 4;
        break;
    case '5': cout << "stay\n";
        valid_input = true;
        output = 5;
        break;
    case '6': cout << "right\n";
        valid_input = true;
        output = 6;
        break;
    case '7': cout << "top left\n";
        valid_input = true;
        output = 7;
        break;
    case '8': cout << "top\n";
        valid_input = true;
        output = 8;
        break;
    case '9': cout << "top right\n";
        valid_input = true;
        output = 9;
        break;
    }

    if (!valid_input) {//if the user gave a different char than a direction his character will stay on the tile he is on
        cout << "stay\n";
        return 5;
    }

    return output;
}

int ConsoleController::get_type() const{
    return 0;
}

ConsoleController::ConsoleController() : Controller(nullptr){
}

//ConsoleController::ConsoleController(const ConsoleController& orig) {
//}

ConsoleController::~ConsoleController() {
}