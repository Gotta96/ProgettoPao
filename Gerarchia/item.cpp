#include "item.h"

//classe base astratta Item

Item::Item(string v, string m, double c, double dc): vendor(v), model(m), cost(c), daycost(dc){}

Item::Item(const Item& i): vendor(i.vendor), model(i.model), cost(i.cost), daycost(i.daycost){}

bool Item::operator==(const Item& i) const{
    return vendor==i.getVendor() && model==i.getModel();
}

bool Item::operator!=(const Item& i) const{
    return vendor!=i.getVendor() || model!=i.getModel();
}

string Item::getVendor() const{
    return vendor;
}

string Item::getModel() const{
    return model;
}

double Item::getCost() const{
    return cost;
}

double Item::getDayCost() const{
    return daycost;
}

std::string Item::print() const{
    return "Marca: " + vendor + " Modello: " + model + " Costo: " + std::to_string(cost) + "€ Costo/giorno: " + std::to_string(daycost) + "€";
}

