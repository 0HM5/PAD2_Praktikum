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
        // above and below the character
        deltaX = from.row - to.row;
        deltaY = to.column - from.column;
        swaped = true;
    } else {
        // left and right of the character
        deltaY = from.row - to.row;
        deltaX = to.column - from.column;
    }

    if (!(deltaX == 0 && deltaY == 0)) {
        double slope = deltaY / static_cast<double> (deltaX); // get the slope of the straight line

        int count = deltaX / abs(deltaX); // -1 with negatice deltaX, +1 with positive
        for (int x(deltaX - count); x != 0; x -= count) { // only check the area between from and to
            int y = round(slope * x);
            if (!swaped && !m_data[from.row - y][from.column + x]->is_transparent()) //some magic
                return false;

            if (swaped && !m_data[from.row - x][from.column + y]->is_transparent()) //more magic
                return false;
        }
    }
    return true;
}

/**
 * Pathing from one point of the map to another, around walls and untriggered 
 * traps using dijkstra
 * 
 * @param from the starting point
 * @param to the point where that path should end
 * @return a vector of positions on the map which should all be visited in 
 * oreder to get to the end the fastest. The first position in the vector is 
 * visited first.
 */
vector<position> DungeonMap::getPathTo(const position& from, const position& to) {
    vector <position> pred; // all predecessors of the target position and their predecessors
    vector <Knot> all_knots; // all positions (knots) on the map, sorted by their distance from the source position

    for (unsigned int counter = 0; counter < height; counter++) { // initialise knots for all tiles
        position init_knots_pos{0, counter};
        for (unsigned int position = 0; position < width; position++) {
            init_knots_pos.column = position;
            Knot tmp(init_knots_pos);
            all_knots.push_back(tmp);
        }
    }

    all_knots[findPosition(all_knots, to)].set_distance(0); // sets the starting position
    sort(all_knots.begin(), all_knots.end());

    for (unsigned int counter = 0; counter < all_knots.size() - 1; counter++) { // check all knots until there is none which are not yet checked
        getAdjacent(all_knots, all_knots[counter]);
        sort(all_knots.begin(), all_knots.end());
    }

    position last = from; // get rid of the const qualifier
    while (findPred(pred, all_knots, last)) { // build the vector of predecessors
    }

    return pred;
}

/**
 * finds the predecessor of a knot and appends it to a vector
 * 
 * @param vorg the vector that later contains all predecessors
 * @param all the vector filled with all knots
 * @param to the target position
 * @return true if the step needs to be repeated in order to find all stops to 
 * the target. False if the vector of predecessors is complete or the target is 
 * unreachable (surrounded by walls etc.)
 */
bool DungeonMap::findPred(vector<position>& vorg, const vector<Knot>& all, position& to) {
    unsigned int tmx = findPosition(all, to);
    vorg.push_back(all[tmx].get_predecessor());
    to = vorg.back();
    return all[tmx].has_predecessor();
}

unsigned int DungeonMap::findPosition(const vector<Knot>& all, const position& find) {
    unsigned int size = all.size();
    position tmp;
    for (unsigned int counter = 0; counter < size; counter++) {
        tmp = all[counter].get_position();
        if (tmp.row == find.row && tmp.column == find.column) {
            return counter;
        }
    }

    throw invalid_argument("The Position is not saved in the vector with all knots.");
}

/**
 * Finds all the tiles adjacent to a starting tile which are on the map and not 
 * walls or untriggered traps, then calculates their distance from the starting 
 * position when crossing the current position. If this distance is shorter than 
 * the current distance, the distance and the predecessor of the position which 
 * is being checked is updated.
 * 
 * @param vec the vector conataining all possible knots
 * @param from the position of which the adjacent knots should be tested next
 */
void DungeonMap::getAdjacent(vector<Knot>& vec, const Knot& from) {
    unsigned int zero = 0; // needed in order to get the max unsigned int instead of -1 in the next step
    if (from.get_distance() == zero - 1) { // if the current knot has not yet been visited (eg. its a wall), the function is aborted
        return;
    }

    unsigned int dist = from.get_distance() + 1; // distance and predecessor of the next knots
    position predecessor = from.get_position();

    unsigned int tmp; // position of the next adjacent knot in the vector of all knots
    position new_pos, old_pos(from.get_position());

    new_pos.row = old_pos.row + 1; // calculate the new position relative to the old one
    new_pos.column = old_pos.column - 1;
    if (pos_on_map(new_pos)) { // is the new position on the map?
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) { // if the next knot has been visited and has a lower distance, is a wall or an  untriggered trap, it is skipped
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row + 1;
    new_pos.column = old_pos.column; // repeat the above for all 8 adjacent tiles
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row + 1;
    new_pos.column = old_pos.column + 1;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row;
    new_pos.column = old_pos.column - 1;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row;
    new_pos.column = old_pos.column;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row;
    new_pos.column = old_pos.column + 1;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row - 1;
    new_pos.column = old_pos.column - 1;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row - 1;
    new_pos.column = old_pos.column;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
        }
    }
    new_pos.row = old_pos.row - 1;
    new_pos.column = old_pos.column + 1;
    if (pos_on_map(new_pos)) {
        tmp = findPosition(vec, new_pos);
        if (vec[tmp].get_distance() > dist && findTile(new_pos)->on_enter_def()) {
            vec[tmp].set_distance(dist);
            vec[tmp].set_predecessor(predecessor);
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
                } else if (tiles[position] == '#') {
                    m_data[counter][position] = new Wall();
                } else {
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
                } else if (amount_space == 2) {
                    ccin >> name1 >> pos_1;
                } else if (amount_space == 6) {
                    continue;
                }

                if (name1 == "Character") {
                } else if (name1 == "Door") {

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
                        } else if (name2 == "Lever") {
                            m_data[pos_2.row][pos_2.column] = new Lever();
                        }
                        swi = findTile(pos_2);
                        dynamic_cast<Active*> (swi)->set_passive(dynamic_cast<Passive*> (door));
                    } catch (const invalid_argument& ia) {
                        cerr << "One of the positions specified in the active/passive pair #" << counter << " is not on tha map.\n";
                    }
                } else if (name1 == "Trap") {
                    delete findTile(pos_1);
                    m_data[pos_1.row][pos_1.column] = new Trap();
                } else if (amount_space == 2) {
                    Item* tmp5 = 0;
                    if (name1 == "Arming_Sword") {
                        tmp5 = new Arming_Sword;
                    } else if (name1 == "Greatsword") {
                        tmp5 = new Greatsword;
                    } else if (name1 == "Club") {
                        tmp5 = new Club;
                    } else if (name1 == "Rapier_Dagger") {
                        tmp5 = new Rapier_Dagger;
                    } else if (name1 == "Gambeson") {
                        tmp5 = new Gambeson;
                    } else if (name1 == "Mail_Armour") {
                        tmp5 = new Mail_Armour;
                    } else if (name1 == "Shield") {
                        tmp5 = new Shield;
                    } else if (name1 == "Full_Plate_Armour") {
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