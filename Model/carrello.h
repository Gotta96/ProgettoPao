#ifndef CARRELLO_H
#define CARRELLO_H

#include "Gerarchia/item.h"
#include "Model/Template/deepptr.h"
#include "Model/Gerarchia/item.h"
#include "Model/Gerarchia/consumable.h"
#include <QMap>

using std::map;
//using std::pair;


class Carrello{
private:
    QMap<DeepPtr<Item>, unsigned int> cart;
public:
    Carrello();
    Carrello(const Carrello&);
    ~Carrello();

    void insertIntoCart(DeepPtr<Item>, unsigned int);
    bool removeIntoCart(DeepPtr<Item>);
    void removeIntoCartAtIndex(unsigned int i);
    QMap<DeepPtr<Item>, unsigned int>::iterator searchIntoCart(DeepPtr<Item>);
    DeepPtr<Item> searchAtIndex(unsigned int) const;
    unsigned int removeQuantity(DeepPtr<Item>, unsigned int);
    unsigned int getQuantity(DeepPtr<Item>);
    unsigned int getTotItems();
//    QMap<DeepPtr<Item>,unsigned int> getCart() const;
//    DeepPtr<Item> getOnlyItem(QMap<DeepPtr<Item>, unsigned int>::const_iterator);

    QStringList printAllCart() const;
};

#endif // CARRELLO_H
