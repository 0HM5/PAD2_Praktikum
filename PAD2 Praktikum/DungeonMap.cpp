//DungeonMap.cpp

#include "DungeonMap.h"

void DungeonMap::place(const position& pos, Character* c) {
    if (c != nullptr && pos.row < width && pos.column < height) {
        m_data[pos.row][pos.column]->set_character(c);
    }
}

position DungeonMap::findTile(Tile* t)const {
    for (unsigned int row = 0; row < width; row++) {
        for (unsigned int column = 0; column < height; column++) {
            if (m_data[row][column] == t) {
                position tmp;
                tmp.row = row;
                tmp. column = column;
                return tmp;
            }
        }
    }

    throw invalid_argument("The tile is not on the map.");
}

Tile* DungeonMap::findTile(const position& pos)const {
    if (pos.row < width && pos.column < height) {
        return m_data[pos.row][pos.column];
    }
    throw invalid_argument("The position is not on the map.");
}

position DungeonMap::findCharacter(Character* c)const {
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int column = 0; column < width; column++) {
            if (m_data[row][column]->get_char() == c) {
                position tmp;
                tmp.row = row;
                tmp. column = column;
                return tmp;
            }
        }
    }
    throw invalid_argument("The character is not on the map.");
}

void DungeonMap::print(const position& center) const {
    position target;
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int column = 0; column < width; column++) {
            target.row = row;
            target.column = column;
            m_data[row][column]->print();
            //            if (has_line_of_sight(center, target)) {
            //                m_data[row][column]->print();
            //            }
            //            else {
            //                //cout << "+";
            //
            //                cout << "#";
            //            }
        }
        cout << endl;
    }
    return;
}

bool DungeonMap::has_line_of_sight(const position& from, const position& to) const {
    int deltaX, deltaY;
    bool swaped(false);

    if (abs(static_cast<int> (to.column) - static_cast<int> (from.column)) < abs(static_cast<int> (from.row) - static_cast<int> (to.row))) {
        // oberes und unteres Dreieck vom character
        deltaX = from.row - to.row;
        deltaY = to.column - from.column;
        swaped = true;
    }
    else {
        // seitlichen Dreiecke vom character
        deltaY = from.row - to.row;
        deltaX = to.column - from.column;
    }

    if (!(deltaX == 0 && deltaY == 0)) {
        double slope = deltaY / static_cast<double> (deltaX); // Steigung der Geraden ermitteln

        int count = deltaX / abs(deltaX); // -1 bei negativem deltaX, +1 bei positiven
        for (int x(deltaX - count); x != 0; x -= count) { // Es wird nur der Bereich zwischen from-to überprüft
            int y = round(slope * x);
            if (!swaped && !m_data[from.row - y][from.column + x]->is_transparent()) //some magic
                return false;

            if (swaped && !m_data[from.row - x][from.column + y]->is_transparent()) //more magic
                return false;
        }
    }
    return true;
}

vector<position> DungeonMap::getPathTo(const position& from, const position& to) {
    vector <position> vorg;
    vector <Knoten> all_knots;

    for (unsigned int counter = 0; counter < height; counter++) { // initialise knots for all tiles
        position init_knots_pos{0, counter};
        for (unsigned int position = 0; position < width; position++) {
            init_knots_pos.column = position;
            Knoten tmp(init_knots_pos);
            all_knots.push_back(tmp);
        }
    }

    all_knots[findPosition(all_knots, to)].set_entf(0);

    sort(all_knots.begin(), all_knots.end());

    for (unsigned int counter = 0; counter < all_knots.size() - 1; counter++) {
        getAdjacent(all_knots, all_knots[counter]);
        sort(all_knots.begin(), all_knots.end());
    }

    position last = from;
    while (findVorg(vorg, all_knots, last)) {
    }

    return vorg;
}

bool DungeonMap::findVorg(vector<position>& vorg, const vector<Knoten>& all, position& to) {
    for (unsigned int counter = 0; counter < all.size(); counter++) {
        position tmp = all[counter].get_pos();
        if (tmp.row == to.row && tmp.column == to.column) {
            vorg.push_back(all[counter].get_vorg());
            to = vorg.back();
            return all[counter].has_vorg();
        }
    }
    throw invalid_argument("Something went wrong and Dijstra just died.");
}

unsigned int DungeonMap::findPosition(const vector<Knoten>& all, const position& find) {
    unsigned int size = all.size();
    position tmp;
    for (unsigned int counter = 0; counter < size; counter++) {
        tmp = all[counter].get_pos();
        if (tmp.row == find.row && tmp.column == find.column) {
            return counter;
        }
    }
    throw invalid_argument("The Position is not saved in the vector with all knots.");
}

void DungeonMap::getAdjacent(vector<Knoten>& vec, const Knoten& from) {
    unsigned int zero = 0;
    if (from.get_entf() == zero - 1) {
        return;
    }
    Knoten tmp;
    tmp.set_entf(from.get_entf() + 1);
    tmp.set_vorg(from.get_pos());
    unsigned int tmx;
    position new_pos, old_pos(from.get_pos());

    new_pos.row = old_pos.row + 1;
    new_pos.column = old_pos.column - 1;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row + 1;
    new_pos.column = old_pos.column;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row + 1;
    new_pos.column = old_pos.column + 1;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row;
    new_pos.column = old_pos.column - 1;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row;
    new_pos.column = old_pos.column;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row;
    new_pos.column = old_pos.column + 1;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row - 1;
    new_pos.column = old_pos.column - 1;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row - 1;
    new_pos.column = old_pos.column;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    new_pos.row = old_pos.row - 1;
    new_pos.column = old_pos.column + 1;
    if (pos_on_map(new_pos)) {
        tmp.set_pos(new_pos);
        tmx = findPosition(vec, new_pos);
        if (vec[tmx].get_entf() > tmp.get_entf() && findTile(new_pos)->on_enter_def()) {
            vec[tmx].set_entf(tmp.get_entf());
            vec[tmx].set_vorg(tmp.get_vorg());
        }
    }
    return;
}

bool DungeonMap::pos_on_map(position& check) {
    if (check.row >= height) {
        return false;
    }
    if (check.column >= width) {
        return false;
    }
    return true;
}

DungeonMap::DungeonMap(const unsigned int& height_to, const unsigned int& width_to) {
    height = height_to;
    width = width_to;

    m_data = new Tile**[height];

    for (unsigned int counter = 0; counter < height; counter++) {
        m_data[counter] = new Tile* [width];
        for (unsigned int y = 0; y < width; y++) {
            m_data[counter][y] = nullptr;
        }
    }
}

DungeonMap::DungeonMap(const vector <string>& data, const vector<string>& act_pass) {
    height = data.size();
    width = data[0].size();

    m_data = new Tile**[height];

    for (unsigned int counter = 0; counter < height; counter++) { // initialise all tiles with nullptr
        m_data[counter] = new Tile* [width];
        for (unsigned int position = 0; position < width; position++) {
            m_data[counter][position] = nullptr;
        }
    }

    {
        string tiles;
        unsigned int size = data.size();

        for (unsigned int counter = 0; counter < size; counter++) { //check for each tile which char is in the vector and create tiles accordingly
            tiles = data[counter];
            for (unsigned int position = 0; position < width; position++) {
                if (tiles[position] == '.') {
                    m_data[counter][position] = new Floor();
                }
                else if (tiles[position] == '#') {
                    m_data[counter][position] = new Wall();
                }
                else {
                    throw std::runtime_error("Invalid Tile Char. u dick");
                }
            }
        }
    }
    {
        unsigned int size = act_pass.size();
        if (size > 0) {
            string name1, name2; //all variables needed
            unsigned int pos1_x_total(0), pos1_y_total(0), pos2_x_total(0), pos2_y_total(0);
            position pos_1, pos_2;
            for (unsigned int counter = 0; counter < size; counter++) {
                stringstream ccin(act_pass[counter]);

                unsigned int size_act = act_pass[counter].size();
                unsigned int amount_space = 0;
                for (unsigned int counter1 = 0; counter1 < size_act; counter1++) {
                    if (act_pass[counter][counter1] == ' ') {
                        amount_space++;
                    }
                }

                if (amount_space == 5) {
                    ccin >> name1 >> pos_1 >> name2 >> pos_2;
                }
                else if (amount_space == 2) {
                    ccin >> name1 >> pos_1;
                }else if(amount_space == 6){
                    continue;
                }

                if (name1 == "Character") {
                }
                else if (name1 == "Door") {

                    Tile* old1;
                    Tile* old2;
                    Tile* door;
                    Tile* swi;

                    old1 = findTile(pos_1);
                    delete old1;
                    m_data[pos_1.row][pos_1.column] = new Door();
                    door = findTile(pos_1);

                    try {
                        old2 = findTile(pos_2);
                        delete old2;
                        if (name2 == "Switch") {
                            m_data[pos_2.row][pos_2.column] = new Switch();
                        }
                        else if (name2 == "Lever") {
                            m_data[pos_2.row][pos_2.column] = new Lever();
                        }
                        swi = findTile(pos_2);
                        dynamic_cast<Active*> (swi)->set_passive(dynamic_cast<Passive*> (door));
                    }
                    catch (const invalid_argument& ia) {
                        cerr << "One of the positions specified in the active/passive pair #" << counter << " is not on tha map.\n";
                    }
                }
                else if (name1 == "Trap") {
                    delete findTile(pos_1);
                    m_data[pos_1.row][pos_1.column] = new Trap();
                }
                else if (amount_space == 2) {
                    Item* tmp5 = 0;
                    if (name1 == "Arming_Sword") {
                        tmp5 = new Arming_Sword;
                    }
                    else if (name1 == "Greatsword") {
                        tmp5 = new Greatsword;
                    }
                    else if (name1 == "Club") {
                        tmp5 = new Club;
                    }
                    else if (name1 == "Rapier_Dagger") {
                        tmp5 = new Rapier_Dagger;
                    }
                    else if (name1 == "Gambeson") {
                        tmp5 = new Gambeson;
                    }
                    else if (name1 == "Mail_Armour") {
                        tmp5 = new Mail_Armour;
                    }
                    else if (name1 == "Shield") {
                        tmp5 = new Shield;
                    }
                    else if (name1 == "Full_Plate_Armour") {
                        tmp5 = new Full_Plate_Armour;
                    }
                    if (tmp5 != 0) {
                        dynamic_cast<Floor*> (findTile(pos_1))->setPickup(dynamic_cast<Item*> (tmp5));
                    }
                }
            }
        }
    }
}

//DungeonMap::DungeonMap(){
//}

//DungeonMap::DungeonMap(const DungeonMap& orig) {
//}

DungeonMap::~DungeonMap() {
    for (int position = 0; position < height; position++) {
        for (int counter = 0; counter < width; counter++)
            delete m_data[position][counter];

        delete[] m_data[position];
    }
    delete[] m_data;
}