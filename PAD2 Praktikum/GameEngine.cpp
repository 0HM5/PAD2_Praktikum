//GameEngine.cpp

#include "GameEngine.h"

bool GameEngine::finished()const {
    if (is_finished) {
        return is_finished;
    }
    unsigned int size = chars.size();
    for (unsigned int counter = 0; counter < size; counter++) {
        if (chars[counter]->get_cont_type() == 0) {
            return false;
        }
    }
    return true;
}

void GameEngine::menu(const int& pos) {
    char input;
    while (1) {
        cout << "Enter what you would like to do:\n1: Return to movement.\n2: Show player Info.\n0: Exit the Program.\n";
        cin >> input;
        switch (input) {
        case '0': is_finished = true;
            return;
            break;
        case '1': return;
            break;
        case '2': chars[pos]->show_info();
            break;
        }
    }
}

void GameEngine::turn() {
    unsigned int size = chars.size();
    position old_pos;
    position new_pos;
    Tile* old_tile;
    Tile* new_tile;
    int move;
    for (unsigned int counter = 0; counter < size; counter++) {
        old_pos = map.findCharacter(chars[counter]);
        old_tile = map.findTile(old_pos);

        if (char_dies(chars[counter])) {
            continue;
        }

        move = chars[counter]->move();
        switch (move) {
        case 0: menu(counter);
            counter--;
            break;
        case 1: new_pos.row = old_pos.row + 1;
            new_pos.column = old_pos.column - 1;
            break;
        case 2: new_pos.row = old_pos.row + 1;
            new_pos.column = old_pos.column;
            break;
        case 3: new_pos.row = old_pos.row + 1;
            new_pos.column = old_pos.column + 1;
            break;
        case 4: new_pos.row = old_pos.row;
            new_pos.column = old_pos.column - 1;
            break;
        case 5: new_pos.row = old_pos.row;
            new_pos.column = old_pos.column;
            break;
        case 6: new_pos.row = old_pos.row;
            new_pos.column = old_pos.column + 1;
            break;
        case 7: new_pos.row = old_pos.row - 1;
            new_pos.column = old_pos.column - 1;
            break;
        case 8: new_pos.row = old_pos.row - 1;
            new_pos.column = old_pos.column;
            break;
        case 9: new_pos.row = old_pos.row - 1;
            new_pos.column = old_pos.column + 1;
            break;
        }
        if (finished()) {
            return;
        }
        if (move == 0) {
            continue;
        }
        new_tile = map.findTile(new_pos);
        if (move != 5) {
            if (new_tile->hasCharacter()) {
                if (!fight(new_tile->get_char(), chars[counter])) {
                }
                else {
                    system("sleep 0.5");
                    continue;
                }
            }
            old_tile->on_leave(new_tile);
            if (char_dies(chars[counter])) {
                counter--;
            }
        }
        size = chars.size();
        system("sleep 0.5");
    }
}

void GameEngine::run() {//checks if the game is still running, prints the map
    while (!finished()) {
        system("clear");
        try {
            map.print(map.findCharacter(chars[0]));
            turn();
        }
        catch (const invalid_argument& message) {
            cout << message.what() << endl;
            system("sleep 2");
        }
    }
}

bool GameEngine::fight(Character* def, Character* att) {
    while (1) {
        def->change_hp(-static_cast<int> (att->get_strength()));
        if (!char_dies(def)) {
            att->change_hp(-static_cast<int> (def->get_strength()));
        }
        else {
            return false;
        }
        if (char_dies(def)) {
            return true;
        }
    }
}

bool GameEngine::char_dies(Character* dies) {
    if (dies->get_hp() <= 0) {
        cout << "Character " << *dies << " died!\n";
        unsigned int size = chars.size();
        for (unsigned int counter = 0; counter < size; counter++) {
            if (chars[counter] == dies) {
                chars.erase(chars.begin() + counter);
                size--;
                break;
            }
        }
        map.findTile(map.findCharacter(dies))->on_enter(0, 0);
        if(dies->get_cont_type() == 0){
            Character* new_att;
            for (unsigned int counter = 0; counter < size;counter++){
                new_att = chars[counter];
                if (new_att->get_cont_type() == 0){
                    dynamic_cast<AttackController*>(conts[2])->set_attk(new_att);
                }
            }
        }
        delete dies;
        system("sleep 2");
        return true;
    }
    return false;
}

GameEngine::GameEngine(const vector<string>& data, const vector<string>& act_pass) :
map(data, act_pass) {
    is_finished = false;
    Controller* cont;
    cont = new ConsoleController();
    conts.push_back(cont);
    cont = new StationaryController();
    conts.push_back(cont);
    cont = new AttackController();
    conts.push_back(cont);

    unsigned int size = act_pass.size();
    if (size > 0) {
        string name1, name2, cont_type; //all variables needed
        unsigned int pos1_x_total(0), pos1_y_total(0), pos2_x_total(0), pos2_y_total(0), amount_space;
        char symbol;
        position pos2;
        for (unsigned int counter = 0; counter < size; counter++) {
            amount_space = 0;
            stringstream ccin(act_pass[counter]);
            unsigned int size_act = act_pass[counter].size();

            for (unsigned int counter1 = 0; counter1 < size_act; counter1++) {
                if (act_pass[counter][counter1] == ' ') {
                    amount_space++;
                }
            }

            if (amount_space == 6) {
                ccin >> name1 >> symbol >> pos1_x_total >> pos1_y_total >> name2 >> pos2;
            }
            else {
                continue;
            }

            if (name1 == "Character") {
                try {
                    if (name2 == "ConsoleController") {
                        cont = conts[0];
                    }
                    else if (name2 == "StationaryController") {
                        cont = conts[1];
                    }
                    else if (name2 == "AttackController") {
                        cont = conts[2];
                    }
                    else {
                        throw invalid_argument("not a valid controller type.");
                    }

                    Character* next_char = new Character(symbol, pos1_x_total, pos1_y_total, cont);
                    chars.push_back(next_char);
                    //position pos2{pos2_x_total, pos2_y_total};
                    map.place(pos2, chars.back());
                    if (name2 == "AttackController") {
                        dynamic_cast<AttackController*> (chars.back()->get_cont())->set_map(&map);
                        dynamic_cast<AttackController*> (chars.back()->get_cont())->set_attk(chars[0]);
                        dynamic_cast<AttackController*> (chars.back()->get_cont())->set_char(chars.back());
                    }
                }
                catch (const invalid_argument& ia) {
                    cerr << name2 << " is " << ia.what();
                    system("sleep 1.5");
                }
            }
        }
    }
}

//GameEngine::GameEngine() {
//}
//
//GameEngine::GameEngine(const GameEngine& orig) {
//}

GameEngine::~GameEngine() {
    unsigned int size = chars.size();
    for (unsigned int counter = 0; counter < size; counter++) {
        delete chars[counter];
    }

    size = conts.size();
    for (unsigned int counter = 0; counter < size; counter++) {
        delete conts[counter];
    }
}