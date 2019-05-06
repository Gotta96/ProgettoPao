#include "multifunction.h"

Multifunction::Multifunction(string v, string m, double cos, double dc, bool w, bool ds, bool col,bool use, bool ph, bool scan, bool fa): Stampante (v,m,cos,dc,w,ds,col,use,ph), scanner(scan), fax(fa){}

Multifunction::Multifunction(const Multifunction& m): Stampante(m), scanner(m.haveScanner()), fax(m.haveFax()){}

Multifunction *Multifunction::clone() const{
    return new Multifunction(*this);
}

Multifunction::~Multifunction(){}

bool Multifunction::operator==(const Item& i) const{
    return dynamic_cast<const Multifunction*>(&i) && Stampante::operator==(i) && scanner==(static_cast<const Multifunction*>(&i))->haveScanner() && fax==(static_cast<const Multifunction*>(&i))->haveFax();
}

bool Multifunction::operator!=(const Item& i) const{
    return dynamic_cast<const Multifunction*>(&i) && Stampante::operator!=(i) && scanner!=(static_cast<const Multifunction*>(&i))->haveScanner() && fax!=(static_cast<const Multifunction*>(&i))->haveFax();
}

bool Multifunction::haveScanner() const{
    return scanner;
}

bool Multifunction::haveFax() const{
    return fax;
}

