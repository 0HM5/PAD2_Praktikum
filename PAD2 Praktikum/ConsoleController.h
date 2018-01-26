// ConsoleController.h

#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H

#include <iostream>
#include "Controller.h"

using namespace std;

class ConsoleController : public Controller
{
public:
    virtual int move()const override;
    virtual int get_type()const override;
    
    ConsoleController();
    //ConsoleController(const ConsoleController& orig);
    virtual ~ConsoleController();
private:

};

#endif /* CONSOLECONTROLLER_H */