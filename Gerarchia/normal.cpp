#include "normal.h"

Normal::Normal(string v, string m, double cos, double dc, bool w, bool ds, bool col, bool pl): Stampante(v,m,cos,dc,w,ds,col), plotter(pl){}

Normal::Normal(const Normal& n): Stampante(n), plotter(n.plotter){}

Normal *Normal::clone() const{
    return new Normal(*this);
}

Normal::~Normal(){}

bool Normal::operator==(const Item& i) const{
    return dynamic_cast<const Normal*>(&i) && Stampante::operator==(i) && plotter==(static_cast<const Normal*>(&i))->isPlotter();
}

bool Normal::operator!=(const Item& i) const{
    return dynamic_cast<const Normal*>(&i) && Stampante::operator!=(i) && plotter!=(static_cast<const Normal*>(&i))->isPlotter();
}

bool Normal::isPlotter() const{
    return plotter;
}
