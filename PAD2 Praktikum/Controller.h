// Controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Character.h"

using namespace std;

class Controller
{
public:
    virtual int move()const = 0;

    virtual int get_type()const = 0;
    void set_char(Character* char_to);
    Character* get_char()const;

    Controller(Character* char_to);
    //Controller();
    //Controller(const Controller& orig);
    virtual ~Controller();
protected:
    Character* char_ptr_c;
};

#endif /* CONTROLLER_H */