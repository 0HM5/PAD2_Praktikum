// StationaryController.h

#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H

#include "Controller.h"

class StationaryController : public Controller {
public:
    virtual int move()const override;
    virtual int get_type()const override;
    
    StationaryController(Character* char_to);
    StationaryController();
//    StationaryController(const StationaryController& orig);
    virtual ~StationaryController();
private:

};

#endif /* STATIONARYCONTROLLER_H */