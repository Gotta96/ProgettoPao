#include "stampante.h"

Stampante::Stampante(string v, string m, double cos, double dc, bool w, bool ds, bool col, bool use, bool ph): Item(v,m,cos,dc), wifi(w), doubleside(ds), color(col), used(use), photo(ph){}

Stampante::Stampante(const Stampante& printer): Item(printer), wifi(printer.wifi), doubleside(printer.doubleside), color(printer.color){}

Stampante::~Stampante(){}

bool Stampante::operator==(const Item& i) const{
    return dynamic_cast<const Stampante*>(&i) && Item::operator==(i) && wifi==static_cast<const Stampante*>(&i)->isWiFi() && doubleside==static_cast<const Stampante*>(&i)->isDoubleSide() && color==static_cast<const Stampante*>(&i)->isColor();
}

bool Stampante::operator!=(const Item& i) const{
    return dynamic_cast<const Stampante*>(&i) && Item::operator!=(i) && wifi!=static_cast<const Stampante*>(&i)->isWiFi() && doubleside!=static_cast<const Stampante*>(&i)->isDoubleSide() && color!=static_cast<const Stampante*>(&i)->isColor();
}

bool Stampante::isWiFi() const{
    return wifi;
}

bool Stampante::isDoubleSide() const{
    return doubleside;
}

bool Stampante::isColor() const{
    return color;
}

bool Stampante::isUsed() const{
    return used;
}

bool Stampante::isPhoto() const{
    return photo;
}

std::string Stampante::print() const{
    return Item::print() + "\n" + "WiFi: " + (wifi ? "Si" : "No");
}
