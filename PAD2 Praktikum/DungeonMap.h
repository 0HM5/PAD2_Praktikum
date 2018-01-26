//DungeonMap.h

#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H

#include <cmath>
#include <sstream>
#include <algorithm>
#include "Floor.h"
#include "Wall.h"
#include "Switch.h"
#include "Door.h"
#include "Trap.h"
#include "Lever.h"
#include "Item.h"
#include "Knoten.h"

using namespace std;

class DungeonMap
{
public:
    void place(const position& pos, Character* c);
    position findTile(Tile* t)const;
    Tile* findTile(const position& pos)const;
    position findCharacter(Character* c)const;
    void print(const position& center)const;
    bool has_line_of_sight(const position& from, const position& to)const;
    
    vector<position> getPathTo(const position& from, const position& to);
    
    
    DungeonMap(const unsigned int& height_to, const unsigned int& width_to);
    DungeonMap(const vector <string>& data, const vector<string>& act_pass);
    //DungeonMap();
    //DungeonMap(const DungeonMap& orig);
    virtual ~DungeonMap();
private:
    void getAdjacent(vector<Knoten>& vec, const Knoten& from);
    bool findVorg(vector<position>& vorg, const vector<Knoten>& all, position& to);
    unsigned int findPosition(const vector<Knoten>& all, const position& find);
    bool pos_on_map(position& check);
    
    unsigned int height;
    unsigned int width;
    Tile*** m_data;
};

#endif /* DUNGEONMAP_H */