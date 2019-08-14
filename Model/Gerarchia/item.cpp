#include "item.h"

//classe base astratta Item

Item::Item(string v, string m, double c): vendor(v), model(m), cost(c){}

Item::Item(const Item& i): vendor(i.vendor), model(i.model), cost(i.cost){}

bool Item::operator==(const Item& i) const{
    return caseUnsensitiveMatch(vendor, i.getVendor()) && caseUnsensitiveMatch(model,i.getModel());
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

bool Item::caseUnsensitiveMatch(std::string s1, std::string s2)
{
    if(s1.length()!=s2.length())
            return false;
        else {
            bool ok=true;
            auto it1=s1.begin();
            auto it2=s2.begin();
            while(ok && it1!=s1.end() && it2!=s2.end()){
                if(std::tolower(*it1)!=std::tolower(*it2))
                    ok =false;
                it1++;
                it2++;
            }
            return ok;
        }
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

std::string Item::print() const{
    return "Marca: " + vendor + "   Modello: " + model + "\n" + "Costo: " + std::to_string(cost) + "€" + "\n";
}

