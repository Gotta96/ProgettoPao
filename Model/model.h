#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "Gerarchia/normal.h"
#include "Gerarchia/multifunction.h"
#include "Gerarchia/consumable.h"
#include "Model/Template/container.h"
#include "Model/Template/deepptr.h"
#include "QDate"
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

public slots:
    bool removeIntoCatalog(unsigned int i);
    bool removeIntoRent(unsigned int i);
    bool removeIntoBuy(unsigned int i);
    void addIntoCatalog(const QStringList e);
    void addIntoRent(unsigned int i,unsigned int q);
    void addIntoBuy(unsigned int i,unsigned int q);
    void editItem(const QStringList e, unsigned int i);
    QString getCatalogElementDetails(unsigned int i);
    QString getRentElementDetails(unsigned int i);
    QString getBuyElementDetails(unsigned int i);
    QString getCatalogElement(unsigned int i);
    QString getRentElement(unsigned int i);
    QString getBuyElement(unsigned int i);
    unsigned int getQuantityRent(unsigned int i);
    unsigned int getQuantityBuy(unsigned int i);
    void setQuantityRent(unsigned int i);
    void setQuantityBuy(unsigned int i);

    void setIva();
    void setName();
    QString getName();
    QString getIva();

    void setDate();
    QDate getDate();

    void setFilename(const QString flname);
    void loadData();
    void serializeData();


signals:
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

};

#endif // MODEL_H
