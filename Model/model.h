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

    void removeIntoCatalog(unsigned int);
    void removeIntoRent(unsigned int);
    void removeIntoBuy(unsigned int);
    void addIntoRent(unsigned int, unsigned int);
    void addIntoBuy(unsigned int, unsigned int);
    bool editItem(unsigned int, const QStringList);
    QString getCatalogElementDetails(unsigned int) const;
    QString getRentElementDetails(unsigned int) const;
    QString getBuyElementDetails(unsigned int) const;
    QStringList getCatalogElement(unsigned int) const;
    QStringList getRentElement(unsigned int) const;
    QStringList getBuyElement(unsigned int) const;
    unsigned int getQuantityRent(unsigned int) const;
    unsigned int getQuantityBuy(unsigned int) const;
    void setQuantityRent(unsigned int, unsigned int);
    void setQuantityBuy(unsigned int, unsigned int);
    QStringList getAllCatalog() const;
    QStringList getFilteredCatalog(QString,QMap<unsigned int,unsigned int> &) const;
    QStringList getAllRent() const;
    QStringList getAllBuyed() const;

    double getAllPriceIntoRent() const;
    double getAllPriceIntoBuy() const;

    bool checkIfExistIntoCatalog(QStringList) const;
    unsigned int findItemIntoCatalog(QStringList) const;

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
