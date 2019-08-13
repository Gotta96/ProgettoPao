#ifndef CARRELLO_H
#define CARRELLO_H

#include "Model/Template/deepptr.h"
#include "Model/Gerarchia/item.h"
#include "Model/Gerarchia/consumable.h"
#include "Model/Gerarchia/stampante.h"
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
    QMap<DeepPtr<Item>, unsigned int>::const_iterator searchIntoCart(DeepPtr<Item>) const;
    DeepPtr<Item> searchAtIndex(unsigned int) const;
    unsigned int removeQuantity(DeepPtr<Item>, unsigned int);
    unsigned int getQuantity(DeepPtr<Item>) const;
    double getTotPriceItems() const;
    double getTotRentItems() const;
    void setQuantity(DeepPtr<Item>, unsigned int);
    bool is_empty() const;
    void clear();

    QStringList printAllCart() const;
};

#endif // CARRELLO_H
