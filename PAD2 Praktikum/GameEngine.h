//GameEngine.h

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "DungeonMap.h"
#include "Character.h"
#include "ConsoleController.h"
#include "StationaryController.h"
#include "AttackController.h"

using namespace std;

class GameEngine
{
public:
    bool finished()const;
    void turn();
    void run();
    void menu(const int& pos);
    bool fight(Character* def, Character* att);
    bool char_dies(Character* dies);

    GameEngine(const vector<string>& data, const vector<string>& act_pass);
    //    GameEngine();
    //    GameEngine(const GameEngine& orig);
    virtual ~GameEngine();
private:
    bool is_finished;
    DungeonMap map;
    vector <Character*> chars;
    vector <Controller*> conts;
};

#endif /* GAMEENGINE_H */