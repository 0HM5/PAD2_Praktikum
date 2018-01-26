//Character.h

#ifndef CHARACTER_H
#define CHARACTER_H

class Controller;

#include "Item.h"
#include <iostream>
#include <vector>

using namespace std;

class Character
{
public:
    int move()const;
    char get_symbol()const;
    unsigned int get_max_hp()const;
    void show_info()const;
    void add_item(Item* to_add);
    unsigned int get_strength()const;
    unsigned int get_stamina()const;
    void change_hp(const int& change);
    int get_hp()const;
    Controller* get_cont()const;
    int get_cont_type()const;
    
    friend ostream& operator<<(ostream& os, const Character& to_output);

    Character(const char& symbol_to, const unsigned int& strength_to, const unsigned int& stamina_to, Controller* contr);
    //    Character();
    //    Character(const Character& orig);
    virtual ~Character();
protected:
    char symbol;
    unsigned int strength;
    unsigned int stamina;
    unsigned int hitpoints;
    Controller* cont;

    vector <Item*> items;
};

#endif /* CHARACTER_H */