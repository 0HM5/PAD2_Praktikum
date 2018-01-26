//Tile.h

#ifndef TILE_H
#define TILE_H

#include "Character.h"

using namespace std;

class Tile
{
public:
    virtual void mk_abstr()const = 0;

    virtual void print()const = 0;

    Character* get_char()const;
    bool hasCharacter()const;
    void set_character(Character* char_to);

    virtual void on_leave(Tile* to_tile);
    virtual bool on_enter(Character* char_enter, Tile* from_tile);
    virtual bool on_enter_def() const;
    virtual bool is_transparent()const;

    //Tile(const Tile& orig);
    Tile();
    virtual ~Tile();
protected:
    Character* char_ptr;
};

#endif /* TILE_H */