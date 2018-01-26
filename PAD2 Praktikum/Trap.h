// Trap.h

#ifndef TRAP_H
#define TRAP_H

#include "Tile.h"

class Trap : public Tile
{
public:
    virtual void mk_abstr()const override;

    virtual void print()const override;

    virtual bool on_enter(Character* char_enter, Tile* from_tile)override;
    virtual bool on_enter_def()const override;
    
    Trap();
    //Trap(const Trap& orig);
    virtual ~Trap();
private:
    bool triggered;
};

#endif /* TRAP_H */