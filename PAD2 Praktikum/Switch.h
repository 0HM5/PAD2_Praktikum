// Switch.h

#ifndef SWITCH_H
#define SWITCH_H

#include "Active.h"

using namespace std;

class Switch : public Active
{
public:
    void mk_abstr()const override;

    void print()const override;
    bool on_enter(Character* char_enter, Tile* from_tile)override;

    Switch();
//    Switch(const Switch& orig);
    virtual ~Switch();
protected:

};

#endif /* SWITCH_H */