// Door.h

#include <iostream>
#include "Passive.h"

#ifndef DOOR_H
#define DOOR_H

using namespace std;

class Door : public Passive
{
public:
    void mk_abstr()const override;

    void print()const override;

    virtual bool on_enter(Character* char_enter, Tile* from_tile)override;
    virtual bool on_enter_def()const override;
    virtual bool is_transparent()const override;
    
    Door();
    Door(const Door& orig);
    virtual ~Door();
protected:

};
#endif /* DOOR_H */