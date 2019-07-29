#include "model.h"

Model::Model(QObject *parent) : QObject(parent),
                                preventiveDate(QDate::currentDate()),
                                clientName(""),
                                clientPiva(""),
                                catalogo(),
                                rent(),
                                buyed()
{

}

bool Model::removeIntoCatalog(unsigned int i){
    return catalogo.removeOneAtIndex(i);
}

bool Model::removeIntoRent(unsigned int i){
    return rent.removeIntoCartAtIndex(i);
}

bool Model::removeIntoBuy(unsigned int i){
    return buyed.removeIntoCartAtIndex(i);
}

bool Model::addIntoCatalog(const QStringList e){
    if(e.at(0)!="null"){
        DeepPtr<Item> elemento;
        if(e.at(0) == "c"){
            elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="true"? 0:1,e.at(6)=="true"? 0:1, e.at(7).toStdString());
        }
        if(e.at(0) == "p"){
            if(e.at(1) == "n")
                elemento = new Normal(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? 0:1, e.at(8)=="true"? 0:1,e.at(9)=="true"? 0:1,e.at(11)=="true"? 0:1);
            if(e.at(1) == "m")
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? 0:1, e.at(7)=="true"? 0:1,e.at(8)=="true"? 0:1,e.at(9)=="true"? 0:1,e.at(10)=="true"? 0:1,e.at(11)=="true"? 0:1,e.at(12)=="true"? 0:1);
        }
        catalogo.pushInOrder(elemento);
        return true;
    }
    return false;
}

void Model::addIntoRent(unsigned int i,unsigned int q){
    DeepPtr<Item> insert = catalogo.searchAtIndex(i);
    rent.insertIntoCart(insert,q);
}

void Model::addIntoBuy(unsigned int i, unsigned int q){
    DeepPtr<Item> insert = catalogo.searchAtIndex(i);
    buyed.insertIntoCart(insert,q);
}

bool Model::editItem(const QStringList e, unsigned int i){
    if(e.at(0)!="null"){
        DeepPtr<Item> elemento;
        if(e.at(0) == "c"){
            elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="true"? 0:1,e.at(6)=="true"? 0:1, e.at(7).toStdString());
        }
        if(e.at(0) == "p"){
            if(e.at(1) == "n")
                elemento = new Normal(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? 0:1, e.at(8)=="true"? 0:1,e.at(9)=="true"? 0:1,e.at(11)=="true"? 0:1);
            if(e.at(1) == "m")
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? 0:1, e.at(7)=="true"? 0:1,e.at(8)=="true"? 0:1,e.at(9)=="true"? 0:1,e.at(10)=="true"? 0:1,e.at(11)=="true"? 0:1,e.at(12)=="true"? 0:1);
        }
        catalogo.replaceAtIndex(elemento,i);
        return true;
    }
    return false;

}

QString Model::getCatalogElementDetails(unsigned int ind){
    return QString::fromStdString((catalogo.searchAtIndex(ind))->print());
}

QString Model::getRentElementDetails(unsigned int ind){
    return QString::fromStdString(rent.searchIntoCart(catalogo.searchAtIndex(ind))->first->print());
}

QString Model::getBuyElementDetails(unsigned int ind){
    return QString::fromStdString(buyed.searchIntoCart(catalogo.searchAtIndex(ind))->first->print());
}

QStringList Model::getCatalogElement(unsigned int ind){         //da rivedere assieme al return index
    QStringList ret;
    ret.push_back(QString::fromStdString(catalogo.searchAtIndex(ind)->print()));
    return ret;
}

QStringList Model::getRentElement(unsigned int ind){
    QStringList ret;
    ret.push_back(QString::fromStdString(rent.searchIntoCart(catalogo.searchAtIndex(ind))->first->getVendor()));
    ret.push_back(QString::fromStdString(rent.searchIntoCart(catalogo.searchAtIndex(ind))->first->getModel()));
    return ret;
}

QStringList Model::getBuyElement(unsigned int ind){
    QStringList ret;
    ret.push_back(QString::fromStdString(buyed.searchIntoCart(catalogo.searchAtIndex(ind))->first->getVendor()));
    ret.push_back(QString::fromStdString(buyed.searchIntoCart(catalogo.searchAtIndex(ind))->first->getModel()));
    return ret;
}

unsigned int Model::getQuantityRent(unsigned int i){
    return rent.searchIntoCart(catalogo.searchAtIndex(i))->second;
}

unsigned int Model::getQuantityBuy(unsigned int i){
    return buyed.searchIntoCart(catalogo.searchAtIndex(i))->second;
}

void Model::setQuantityRent(unsigned int ind, unsigned int q){
    rent.searchIntoCart(catalogo.searchAtIndex(ind))->second=q;
}

void Model::setQuantityBuy(unsigned int ind, unsigned int q){
    buyed.searchIntoCart(catalogo.searchAtIndex(ind))->second=q;
}

void Model::setIva(QString i){
    clientPiva=i;
}

void Model::setName(QString n){
    clientName=n;
}

QString Model::getName(){
    return clientName;
}

QString Model::getIva(){
    return clientPiva;
}

void Model::setDate(QDate d){
    preventiveDate=d;
}

QDate Model::getDate(){
    return preventiveDate;
}

//void Model::setFilename(const QString flname)
//{

//}

////void Model::loadData()
//{

//}

//void Model::serializeData()
//{

//}
