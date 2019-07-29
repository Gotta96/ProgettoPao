#ifndef CARRELLO_H
#define CARRELLO_H

#include "Gerarchia/item.h"
#include "Model/Template/deepptr.h"
#include <map>

using std::map;
//using std::pair;


class Carrello{
private:
    map<DeepPtr<Item>, unsigned int> cart;
public:
    Carrello();
    Carrello(const Carrello&);
    ~Carrello();

    void insertIntoCart(DeepPtr<Item>, unsigned int);
    bool removeIntoCart(DeepPtr<Item>);
    bool removeIntoCartAtIndex(unsigned int i);
    map<DeepPtr<Item>, unsigned int>::iterator searchIntoCart(DeepPtr<Item>);
    unsigned int removeQuantity(DeepPtr<Item>, unsigned int);
    unsigned int getQuantity(DeepPtr<Item>);
    unsigned int getTotItems();
};

#endif // CARRELLO_H
