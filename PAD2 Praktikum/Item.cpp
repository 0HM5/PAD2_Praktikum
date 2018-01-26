//Item.cpp

#include "Item.h"

Item::Item() {
}

Item::~Item() {
}

void Arming_Sword::mk_abstr()const {
}

int Arming_Sword::modify_strength(const int& strength_orig)const {
    return 3;
}

int Arming_Sword::modify_stamina(const int& stamina_orig)const {
    return 0;
}

int Arming_Sword::modify_health(const int& health_orig)const {
    return 0;
}

Arming_Sword::Arming_Sword() {
}

Arming_Sword::~Arming_Sword() {
}

void Greatsword::mk_abstr()const {
}

int Greatsword::modify_strength(const int& strength_orig)const {
    return 5;
}

int Greatsword::modify_stamina(const int& stamina_orig)const {
    return -1;
}

int Greatsword::modify_health(const int& health_orig)const {
    return 0;
}

Greatsword::Greatsword() {
}

Greatsword::~Greatsword() {
}

void Club::mk_abstr()const {
}

int Club::modify_strength(const int& strength_orig)const {
    return strength_orig / 2;
}

int Club::modify_stamina(const int& stamina_orig)const {
    return 0;
}

int Club::modify_health(const int& health_orig)const {
    return 0;
}

Club::Club() {
}

Club::~Club() {
}

void Rapier_Dagger::mk_abstr()const {
}

int Rapier_Dagger::modify_strength(const int& strength_orig)const {
    return 2;
}

int Rapier_Dagger::modify_stamina(const int& stamina_orig)const {
    return 1;
}

int Rapier_Dagger::modify_health(const int& health_orig)const {
    return 0;
}

Rapier_Dagger::Rapier_Dagger() {
}

Rapier_Dagger::~Rapier_Dagger() {
}

void Gambeson::mk_abstr()const {
}

int Gambeson::modify_strength(const int& strength_orig)const {
    return 0;
}

int Gambeson::modify_stamina(const int& stamina_orig)const {
    return 1;
}

int Gambeson::modify_health(const int& health_orig)const {
    return 0;
}

Gambeson::Gambeson() {
}

Gambeson::~Gambeson() {
}

void Mail_Armour::mk_abstr()const {
}

int Mail_Armour::modify_strength(const int& strength_orig)const {
    return 0;
}

int Mail_Armour::modify_stamina(const int& stamina_orig)const {
    return 3;
}

int Mail_Armour::modify_health(const int& health_orig)const {
    return 0;
}

Mail_Armour::Mail_Armour() {
}

Mail_Armour::~Mail_Armour() {
}

void Shield::mk_abstr()const {
}

int Shield::modify_strength(const int& strength_orig)const {
    return -1;
}

int Shield::modify_stamina(const int& stamina_orig)const {
    return stamina_orig;
}

int Shield::modify_health(const int& health_orig)const {
    return 0;
}

Shield::Shield() {
}

Shield::~Shield() {
}

void Full_Plate_Armour::mk_abstr()const {
}

int Full_Plate_Armour::modify_strength(const int& strength_orig)const {
    return -2;
}

int Full_Plate_Armour::modify_stamina(const int& stamina_orig)const {
    return 6;
}

int Full_Plate_Armour::modify_health(const int& health_orig)const {
    return 0;
}

Full_Plate_Armour::Full_Plate_Armour() {
}

Full_Plate_Armour::~Full_Plate_Armour() {
}