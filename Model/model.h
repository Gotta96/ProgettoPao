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

class Model : public QObject
{
    Q_OBJECT
private:
    QDate preventiveDate;
    QString clientName, clientPiva;
    Container<DeepPtr<Item>> catalogo;
    Carrello rent, buyed;

public:
    explicit Model(QObject *parent = nullptr);

    void removeIntoCatalog(unsigned int);
    void removeIntoRent(unsigned int);
    void removeIntoBuy(unsigned int);
    void addIntoRent(unsigned int, unsigned int);
    void addIntoBuy(unsigned int, unsigned int);
    bool editItem(unsigned int, const QStringList);
    QString getCatalogElementDetails(unsigned int);
    QString getRentElementDetails(unsigned int);
    QString getBuyElementDetails(unsigned int);
    QStringList getCatalogElement(unsigned int);
    QStringList getRentElement(unsigned int);
    QStringList getBuyElement(unsigned int);
    unsigned int getQuantityRent(unsigned int);
    unsigned int getQuantityBuy(unsigned int);
    void setQuantityRent(unsigned int, unsigned int);
    void setQuantityBuy(unsigned int, unsigned int);
    QStringList getAllCatalog();
    QStringList getFilteredCatalog(QString,QMap<unsigned int,unsigned int> &);
    QStringList getAllRent();
    QStringList getAllBuyed();

    double getAllPriceIntoRent();
    double getAllPriceIntoBuy();

    bool checkIfExistIntoCatalog(QStringList);
    unsigned int findItemIntoCatalog(QStringList);

    void setIva(QString);
    void setName(QString);
    QString getName();
    QString getIva();

    void setDate(QDate);
    QDate getDate();

public slots:

    void addIntoCatalog(const QStringList);

//    void setFilename(const QString flname);
//    void loadData();
//    void serializeData();


signals:
    void showCatalog(const QStringList);
    void rentQuantityChanged();
    void buyQuantityChanged();
    void catalogElementRemoved();
    void rentElementRemoved();
    void buyElementRemoved();
    void nameChanged();
    void quantityChanged();
//    void rentRemoveRequest();
//    void buyRemoveRequest();
//    void catalogRemoveRequest();
//    void editElementRequest();
//    void catalogAddRequest();
//    void rentAddRequest();
//    void buyAddRequest();

    void elementAdded();
    void rentAdded();
    void buyedAdded();

    void catalogRemoved();
    void rentRemoved();
    void buyRemoved();

    void consumableNotRentable();

};

#endif // MODEL_H
