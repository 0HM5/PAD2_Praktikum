//AttackController.h

#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include <vector>
#include "Controller.h"
#include "DungeonMap.h"

class AttackController : public Controller {
public:
    virtual int move()const override;
    virtual int get_type()const override;
    void set_attk(Character* to_att);
    void set_map(DungeonMap* dumap);
    
    AttackController(DungeonMap* dumap, Character* to_att, Character* char_to);
    AttackController();
//    AttackController(const AttackController& orig);
    virtual ~AttackController();
private:
    DungeonMap* map;
    Character* att;
};

#endif /* ATTACKCONTROLLER_H */