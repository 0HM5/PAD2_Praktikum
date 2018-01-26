//Item.h

#ifndef ITEM_H
#define ITEM_H

class Item {
public:
    virtual void mk_abstr()const = 0;

    virtual int modify_strength(const int& strength_orig)const = 0;
    virtual int modify_stamina(const int& stamina_orig)const = 0;
    virtual int modify_health(const int& health_orig)const = 0;

    Item();
    virtual ~Item();
protected:

};

#endif /* ITEM_H */

#ifndef Arming_Sword_H
#define Arming_Sword_H

class Arming_Sword : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Arming_Sword();
    virtual ~Arming_Sword();
private:

};

#endif /* Arming_Sword_H */

#ifndef Greatsword_H
#define Greatsword_H

class Greatsword : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Greatsword();
    virtual ~Greatsword();
private:

};

#endif /* Greatsword_H */

#ifndef Club_H
#define Club_H

class Club : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Club();
    virtual ~Club();
private:

};

#endif /* Club_H */

#ifndef Rapier_Dagger_H
#define Rapier_Dagger_H

class Rapier_Dagger : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Rapier_Dagger();
    virtual ~Rapier_Dagger();
private:

};

#endif /* Rapier_Dagger_H */

#ifndef Gambeson_H
#define Gambeson_H

class Gambeson : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Gambeson();
    virtual ~Gambeson();
private:

};

#endif /* Gambeson_H */

#ifndef Mail_Armour_H
#define Mail_Armour_H

class Mail_Armour : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Mail_Armour();
    virtual ~Mail_Armour();
private:

};

#endif /* Mail_Armour_H */

#ifndef Shield_H
#define Shield_H

class Shield : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Shield();
    virtual ~Shield();
private:

};

#endif /* Shield_H */

#ifndef Full_Plate_Armour_H
#define Full_Plate_Armour_H

class Full_Plate_Armour : public Item {
public:
    virtual void mk_abstr()const override;

    virtual int modify_strength(const int& strength_orig)const override;
    virtual int modify_stamina(const int& stamina_orig)const override;
    virtual int modify_health(const int& health_orig)const override;

    Full_Plate_Armour();
    virtual ~Full_Plate_Armour();
private:

};

#endif /* Full_Plate_Armour_H */