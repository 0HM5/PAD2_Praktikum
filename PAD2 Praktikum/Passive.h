// Passive.h

#include "Tile.h"

#ifndef PASSIVE_H
#define PASSIVE_H

using namespace std;

class Passive : virtual public Tile
{
public:
    void set_status(const bool& status_to);
    void toggle_status();
    bool get_status()const;

    Passive();
//    Passive(const Passive& orig);
    virtual ~Passive();
protected:
    bool status;
};

#endif /* PASSIVE_H */