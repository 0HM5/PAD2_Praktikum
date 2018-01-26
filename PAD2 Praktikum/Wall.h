// Wall.h

#include "Tile.h"

#ifndef WALL_H
#define WALL_H

using namespace std;

class Wall : public Tile
{
public:
    void mk_abstr()const override;

    void print()const override;
    virtual bool on_enter(Character* char_enter, Tile* from_tile) override;
    virtual bool on_enter_def()const override;
    virtual bool is_transparent()const override;
    
    Wall();
    //Wall(const Wall& orig);
    virtual ~Wall();
protected:

};

#endif /* WALL_H */