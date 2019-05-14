#ifndef CARRELLO_H
#define CARRELLO_H

#include "Gerarchia/item.h"
#include <map>

using std::map;
using std::pair;


class Carrello{
private:
    map<Item*, unsigned int> cart;
public:
    Carrello();
    Carrello(const Carrello&);
    ~Carrello();

    void insertIntoCart(Item*, unsigned int);
    bool removeIntoCart(Item*);
    map<Item*, unsigned int>::iterator searchIntoCart(Item*);
    unsigned int removeQuantity(Item*, unsigned int);
    unsigned int getQuantity(Item*);
    unsigned int getTotItems();
};

#endif // CARRELLO_H
