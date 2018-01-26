//Knoten.h

#ifndef KNOTEN_H
#define KNOTEN_H

#include <iostream>

using namespace std;

struct position {
    unsigned int column;
    unsigned int row;
};

istream& operator>>(istream& os, position& pos);

class Knoten {
public:
    position get_pos()const;
    position get_vorg()const;
    unsigned int get_entf()const;
    bool has_vorg()const;

    void set_pos(position to);
    void set_vorg(position to);
    void set_entf(unsigned int to);

    bool operator<(const Knoten& rhs)const;

    Knoten();
    Knoten(const position& to);
    Knoten(const Knoten& orig);
    virtual ~Knoten();
private:
    position pos;
    position vorg;
    unsigned int entf;
    bool h_vorg;
};

#endif /* KNOTEN_H */

