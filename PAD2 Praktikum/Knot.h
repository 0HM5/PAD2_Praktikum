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

class Knot {
public:
    position get_position()const;
    position get_predecessor()const;
    unsigned int get_distance()const;
    bool has_predecessor()const;

    void set_position(position to);
    void set_predecessor(position to);
    void set_distance(unsigned int to);

    bool operator<(const Knot& rhs)const;

    Knot();
    Knot(const position& to);
    Knot(const Knot& orig);
    virtual ~Knot();
private:
    position pos;
    position pred;
    unsigned int dist;
    bool has_pred;
};

#endif /* KNOTEN_H */

