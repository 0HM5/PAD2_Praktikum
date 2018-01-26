// Avctive.h

#ifndef ACTIVE_H
#define ACTIVE_H

#include "Tile.h"
#include "Passive.h"

using namespace std;

class Active : virtual public Tile
{
public:
    void set_activation(const bool& to_activate);
    bool get_activation()const;
    void set_passive(Passive* to_pass);


//    Active();
//    Active(const Active& orig);
    virtual ~Active();
protected:
    bool has_been_activated;
    Passive* passive_tile;
    //Tile* passive_tile;
};

#endif /* ACTIVE_H */