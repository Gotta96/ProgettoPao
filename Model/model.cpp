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

void Model::addIntoCatalog(const QStringList e){
    DeepPtr<Item> elemento;
    if(e.first().toStdString() == "normal")
        elemento = new Normal(e.at(1).toStdString(), e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toDouble(),e.at(5)=="true"? 0:1, e.at(6)=="true"? 0:1,e.at(7)=="true"? 0:1,e.at(8)=="true"? 0:1);
    if(e.first().toStdString() == "multifunction")
        elemento = new Multifunction(e.at(1).toStdString(), e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toDouble(),e.at(5)=="true"? 0:1, e.at(6)=="true"? 0:1,e.at(7)=="true"? 0:1,e.at(8)=="true"? 0:1,e.at(9)=="true"? 0:1,e.at(10)=="true"? 0:1,e.at(11)=="true"? 0:1);
    if(e.first().toStdString() == "consumable"){
        elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="true"? 0:1,e.at(6)=="true"? 0:1);
    }
    catalogo.addInOrder(elemento);
}

void Model::addIntoRent(unsigned int i,unsigned int q){
    Item* insert = &(**(catalogo.searchAtIndex(i))) ;
    rent.insertIntoCart(insert,q);
}

void Model::addIntoBuy(unsigned int i, unsigned int q){
    Item* insert = &(**(catalogo.searchAtIndex(i)));
    buyed.insertIntoCart(insert,q);
}

void Model::editItem(const QStringList e, unsigned int i){
    DeepPtr<Item> elemento;
    if(e.first().toStdString() == "normal")
        elemento = new Normal(e.at(1).toStdString(), e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toDouble(),e.at(5)=="true"? 0:1, e.at(6)=="true"? 0:1,e.at(7)=="true"? 0:1,e.at(8)=="true"? 0:1);
    if(e.first().toStdString() == "multifunction")
        elemento = new Multifunction(e.at(1).toStdString(), e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toDouble(),e.at(5)=="true"? 0:1, e.at(6)=="true"? 0:1,e.at(7)=="true"? 0:1,e.at(8)=="true"? 0:1,e.at(9)=="true"? 0:1,e.at(10)=="true"? 0:1,e.at(11)=="true"? 0:1);
    if(e.first().toStdString() == "consumable"){
        elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="true"? 0:1,e.at(6)=="true"? 0:1);
    }

    catalogo.replace(elemento,i);
}

QString Model::getCatalogElementDetails(unsigned int i)
{

}

QString Model::getRentElementDetails(unsigned int i)
{

}

QString Model::getBuyElementDetails(unsigned int i)
{

}

QString Model::getCatalogElement(unsigned int i)
{

}

QString Model::getRentElement(unsigned int i)
{

}

QString Model::getBuyElement(unsigned int i)
{

}

unsigned int Model::getQuantityRent(unsigned int i){
    return rent.searchIntoCart((&(**(catalogo.searchAtIndex(i)))))->second;
}

unsigned int Model::getQuantityBuy(unsigned int i){
    return buyed.searchIntoCart((&(**(catalogo.searchAtIndex(i)))))->second;
}

void Model::setQuantityRent(unsigned int i)
{

}

void Model::setQuantityBuy(unsigned int i)
{

}

void Model::setIva()
{

}

void Model::setName()
{

}

QString Model::getName(){
    return clientName;
}

QString Model::getIva(){
    return clientPiva;
}

void Model::setDate()
{

}

QDate Model::getDate(){
    return preventiveDate;
}

void Model::setFilename(const QString flname)
{

}

void Model::loadData()
{

}

void Model::serializeData()
{

}
