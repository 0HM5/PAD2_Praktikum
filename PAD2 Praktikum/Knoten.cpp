//Knoten.cpp

#include "Knoten.h"
#include "Active.h"

istream& operator>>(istream& is, position& dt) {
    is >> dt.row >> dt.column;
    return is;
}

position Knoten::get_pos()const {
    return pos;
}

position Knoten::get_vorg()const {
    return vorg;
}

unsigned int Knoten::get_entf()const {
    return entf;
}

bool Knoten::has_vorg() const {
    return h_vorg;
}

void Knoten::set_pos(position to) {
    pos = to;
}

void Knoten::set_vorg(position to) {
    vorg = to;
    h_vorg = true;
}

void Knoten::set_entf(unsigned int to) {
    entf = to;
}

Knoten::Knoten(const position& to) {
    pos = to;
    vorg = pos;
    entf = 0 - 1;
    h_vorg = false;
}

bool Knoten::operator<(const Knoten& rhs)const {
    return entf < rhs.get_entf();
}

Knoten::Knoten() {
    entf = 0 - 1;
    h_vorg = false;
    position tmp {0,0};
    pos = tmp;
    vorg = pos;
}

Knoten::Knoten(const Knoten& orig) {
    pos = orig.pos;
    vorg = orig.vorg;
    entf = orig.entf;
    h_vorg = orig.h_vorg;
}

Knoten::~Knoten() {
}