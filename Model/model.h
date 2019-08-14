#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDate>
#include <QMap>
#include "Gerarchia/item.h"
#include "Gerarchia/normal.h"
#include "Gerarchia/multifunction.h"
#include "Gerarchia/consumable.h"
#include "Gerarchia/stampante.h"
#include "Model/Template/container.h"
#include "Model/Template/deepptr.h"
#include "Model/carrello.h"
#include "xmlio.h"

class Model : public QObject
{
    Q_OBJECT
private:
    QDate preventiveDate;
    Container<DeepPtr<Item>> catalogo;
    Carrello rent, buyed;

    QString filename;

public:
    explicit Model(QObject *parent = nullptr);

    void removeIntoCatalog(const unsigned int);
    void removeIntoRent(const unsigned int);
    void removeIntoBuy(const unsigned int);

    void addIntoRent(const unsigned int,const unsigned int);
    void addIntoBuy(const unsigned int,const unsigned int);

    bool editItem(const unsigned int,const QStringList);

    QString getCatalogElementDetails(const unsigned int) const;
    QString getRentElementDetails(const unsigned int) const;
    QString getBuyElementDetails(const unsigned int) const;

    QStringList getCatalogElement(const unsigned int) const;
    QStringList getRentElement(const unsigned int) const;
    QStringList getBuyElement(const unsigned int) const;

    unsigned int getQuantityRent(const unsigned int) const;
    unsigned int getQuantityBuy(const unsigned int) const;

    void setQuantityRent(const unsigned int,const unsigned int);
    void setQuantityBuy(const unsigned int,const unsigned int);

    QStringList getAllCatalog() const;
    QStringList getFilteredCatalog(const QString,QMap<unsigned int,unsigned int> &) const;
    QStringList getAllRent() const;
    QStringList getAllBuyed() const;

    double getAllPriceIntoRent() const;
    double getAllPriceIntoBuy() const;

    bool checkIfExistIntoCatalog(const QStringList) const;

    unsigned int findItemIntoCatalog(const QStringList) const;

    bool thereIsSomething() const;
    void clearTheWorkspace();

    void setDate(QDate);
    QDate getDate() const;

public slots:

    void addIntoCatalog(const QStringList);

    void setFilename(const QString flname);
    QString loadData();
    QString serializeData();


signals:
    void showCatalog(const QStringList);
    void rentQuantityChanged();
    void buyQuantityChanged();
    void catalogElementRemoved();
    void rentElementRemoved();
    void buyElementRemoved();
    void nameChanged();
    void quantityChanged();

    void elementAdded();
    void rentAdded();
    void buyedAdded();

    void catalogRemoved();
    void rentRemoved();
    void buyRemoved();

    void consumableNotRentable();

};

#endif // MODEL_H
