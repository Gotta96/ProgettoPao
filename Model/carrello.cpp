#include "carrello.h"

Carrello::Carrello():cart(){}

Carrello::Carrello(const Carrello& c): cart(c.cart){}

Carrello::~Carrello(){

}

void Carrello::insertIntoCart(Item * i, unsigned int q){
    auto it=searchIntoCart(i);
    if(cart.end()!=it){
        it->second+=q;
    }
    cart[i]=q;
}

bool Carrello::removeIntoCart(Item* i){
    auto it=searchIntoCart(i);
    if(cart.end()!=it){
        cart.erase(it);
        return true;
    }
    return false;
}

bool Carrello::removeIntoCartAtIndex(unsigned int i){
    auto it=cart.begin();
    if(i<cart.size()){
        for(unsigned int k=0; k<i; k++)
            it++;
        cart.erase(it);
        return true;
    }
     return false;
}

map<Item*,unsigned int>::iterator Carrello::searchIntoCart(Item * i){
    return cart.find(i);
}

unsigned int Carrello::removeQuantity(Item * i, unsigned int q){
    auto it=searchIntoCart(i);
    if(cart.end()!=it){
        if(it->second > q){
            it->second-=q;
            return it->second;
        }
    }
    return 0;
}

unsigned int Carrello::getQuantity(Item * i){
    auto it=searchIntoCart(i);
    if(it!=cart.end())
        return it->second;
    return 0;
}

unsigned int Carrello::getTotItems(){
    unsigned int tot=0;
    for(auto it=cart.begin(); it !=cart.end(); it++){
        tot+=it->second;
    }
    return tot;
}
