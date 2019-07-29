#include "consumable.h"

Consumable::Consumable(string v, string m , double cos, unsigned int s, bool rest, bool origin, string col): Item(v,m,cos), size(s), restore(rest), original(origin), color(col){}

Consumable::Consumable(const Consumable& c): Item(c), size(c.getSize()), restore(c.isRestored()), original(c.isOriginal()){}

Consumable *Consumable::clone() const{
    return new Consumable(*this);
}

Consumable::~Consumable(){};

bool Consumable::operator==(const Item& i) const{
    return dynamic_cast<const Consumable*>(&i) && Item::operator==(i) && size==(static_cast<const Consumable*>(&i))->getSize() && restore==(static_cast<const Consumable*>(&i))->isRestored() && original==static_cast<const Consumable*>(&i)->isOriginal();
}

bool Consumable::operator!=(const Item& i) const{
    return dynamic_cast<const Consumable*>(&i) && Item::operator!=(i) && size!=(static_cast<const Consumable*>(&i))->getSize() && restore!=(static_cast<const Consumable*>(&i))->isRestored() && original!=static_cast<const Consumable*>(&i)->isOriginal();
}

unsigned int Consumable::getSize() const{
    return size;
}

bool Consumable::isRestored() const{
    return restore;
}

bool Consumable::isOriginal() const{
    return original;
}

std::string Consumable::getColorName() const{
    return color;
}
