#include "item.h"

//classe base astratta Item

Item::Item(string v, string m, double c): vendor(v), model(m), cost(c){}

Item::Item(const Item& i): vendor(i.vendor), model(i.model), cost(i.cost){}

bool Item::operator==(const Item& i) const{
    return vendor==i.getVendor() && model==i.getModel();
}

bool Item::operator!=(const Item& i) const{
    return vendor!=i.getVendor() || model!=i.getModel();
}

bool Item::operator<(const Item& i) const{
    if(vendor<i.getVendor())
        return true;
    else{
        if(vendor==i.getVendor())
            if(model<i.getModel())
                return true;
    }
    return false;
}

bool Item::operator>(const Item& i) const{
    if(vendor>i.getVendor())
        return true;
    else{
        if(vendor==i.getVendor())
            if(model>i.getModel())
                return true;
    }
    return false;
}

//bool Item::compareBaseDetails(const Item& i) const{
//    return vendor==i.getVendor() && model==i.getModel();
//}

string Item::getVendor() const{
    return vendor;
}

string Item::getModel() const{
    return model;
}

double Item::getCost() const{
    return cost;
}

std::string Item::print() const{
    return "Marca: " + vendor + " Modello: " + model + " Costo: " + std::to_string(cost) + "€";
}

