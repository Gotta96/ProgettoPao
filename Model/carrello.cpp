#include "carrello.h"

Carrello::Carrello():cart(){}

Carrello::Carrello(const Carrello& c): cart(c.cart){}

Carrello::~Carrello(){
}

void Carrello::insertIntoCart(DeepPtr<Item> i, unsigned int q){    
    auto it=searchIntoCart(i);
        if(!(*it))
            cart.insert(i,q);
        else
            cart[i]+=q;

}

bool Carrello::removeIntoCart(DeepPtr<Item> i){
    auto it=searchIntoCart(i);
    if(cart.end()!=it){
        cart.erase(it);
        return true;
    }
    return false;
}

void Carrello::removeIntoCartAtIndex(unsigned int i){
    auto it=cart.begin();
    if(i<(uint)cart.size()){
        for(unsigned int k=0; k<i; k++)
            it++;
        cart.erase(it);
    }
}

QMap<DeepPtr<Item>,unsigned int>::iterator Carrello::searchIntoCart(DeepPtr<Item> i){
    return cart.find(i);
}

DeepPtr<Item> Carrello::searchAtIndex(unsigned int index) const
{
    auto it = cart.begin();
    for(unsigned int k=0; k<index; k++)
        it++;
    return it.key();
}

unsigned int Carrello::removeQuantity(DeepPtr<Item> i, unsigned int q){         //da sistemare, logicamente errata
    auto it=searchIntoCart(i);
    if(cart.end()!=it){
        if(it.value() > q){
            it.value()-=q;
            return it.value();
        }
    }
    return 0;
}

unsigned int Carrello::getQuantity(DeepPtr<Item> i){
    auto it=searchIntoCart(i);
    if(*it)
        return it.value();
    return 0;
}

double Carrello::getTotPriceItems(){
    double tot=0;
    double costo_tmp=0;
    for(auto it=cart.begin(); it !=cart.end(); it++){
        costo_tmp=(*(it.key())).getCost();
        tot+=it.value() * costo_tmp;
    }
    return tot;
}

double Carrello::getTotRentItems()
{
    double tot=0;
    double noleggio_tmp=0;
    for(auto it=cart.begin(); it !=cart.end(); it++){
        if(dynamic_cast<const Stampante*>(&(*(it.key())))){
            noleggio_tmp=(dynamic_cast<const Stampante*>(&(*(it.key()))))->getDaycost();
            tot+=it.value() * noleggio_tmp;
        }
    }
    return tot;
}

bool Carrello::is_empty() const
{
    return cart.empty();
}

void Carrello::clear()
{
    cart.clear();
}

QStringList Carrello::printAllCart() const
{
    QStringList ret;
    QString etichetta;
    auto it = cart.begin();
    while(it!=cart.end()){
        etichetta = (QString::fromStdString(((it.key())->getVendor()) + " " + ((it.key())->getModel()) + " "));
        if(dynamic_cast<const Consumable*>(&(*(it.key()))))
            etichetta += (QString::fromStdString(dynamic_cast<const Consumable*>(&(*(it.key())))->getColorName()));
        etichetta += QString::fromStdString("       ");
        etichetta += QString::number(it.value());
        ret.push_back(etichetta);
        ++it;
    }

    return ret;
}
