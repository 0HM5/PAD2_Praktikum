// Lever.h

#ifndef LEVER_H
#define LEVER_H

#include "Active.h"

using namespace std;

class Lever : public Active {
public:
    void mk_abstr()const override;

    virtual void print()const override;
    virtual bool on_enter(Character* char_enter, Tile* from_tile)override;
    virtual bool on_enter_def()const override;

    Lever();
    //    Lever(const Lever& orig);
    virtual ~Lever();
private:

};

#endif /* LEVER_H */