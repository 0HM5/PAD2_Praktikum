// Floor.h

#include "Tile.h"
#include "Item.h"

#ifndef FLOOR_H
#define FLOOR_H

using namespace std;

class Floor : public Tile
{
public:
    void mk_abstr()const override;

    virtual void print()const override;
    virtual bool on_enter(Character* char_enter, Tile* from_tile)override;
    void setPickup(Item* ground);

    Floor();
    //Floor(const Floor& orig);
    virtual ~Floor();
protected:
    Item* pickup;
};

#endif /* FLOOR_H */