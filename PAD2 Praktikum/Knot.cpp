//Knoten.cpp

#include "Knot.h"
#include "Active.h"

istream& operator>>(istream& is, position& dt) {
    is >> dt.row >> dt.column;
    return is;
}

position Knot::get_position()const {
    return pos;
}

position Knot::get_predecessor()const {
    return pred;
}

unsigned int Knot::get_distance()const {
    return dist;
}

bool Knot::has_predecessor() const {
    return has_pred;
}

void Knot::set_position(position to) {
    pos = to;
}

void Knot::set_predecessor(position to) {
    pred = to;
    has_pred = true;
}

void Knot::set_distance(unsigned int to) {
    dist = to;
}

Knot::Knot(const position& to) {
    pos = to;
    pred = pos;
    dist = 0 - 1;
    has_pred = false;
}

bool Knot::operator<(const Knot& rhs)const {
    return dist < rhs.get_distance();
}

Knot::Knot() {
    dist = 0 - 1;
    has_pred = false;
    position tmp {0,0};
    pos = tmp;
    pred = pos;
}

Knot::Knot(const Knot& orig) {
    pos = orig.pos;
    pred = orig.pred;
    dist = orig.dist;
    has_pred = orig.has_pred;
}

Knot::~Knot() {
}