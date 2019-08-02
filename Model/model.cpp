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
    if(e.at(0)!="null"){
        DeepPtr<Item> elemento;
        if(e.at(0) == "c"){
            elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="1"? 1:0,e.at(6)=="1"? 1:0, e.at(7).toStdString());
        }
        if(e.at(0) == "p"){
            if(e.at(1) == "n")
                elemento = new Normal(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="1"? 1:0, e.at(8)=="1"? 1:0,e.at(9)=="1"? 1:0,e.at(11)=="1"? 1:0);
            if(e.at(1) == "m")
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="1"? 1:0, e.at(7)=="1"? 1:0,e.at(8)=="1"? 1:0,e.at(9)=="1"? 1:0,e.at(10)=="1"? 1:0,e.at(11)=="1"? 1:0,e.at(12)=="1"? 1:0);
        }
//        std::cout << std::endl << elemento->print() << std::endl;
        catalogo.pushInOrder(elemento);
//        std::cout << std::endl << (*catalogo.getFirst()->info).print() << std::endl;
    }

    emit elementAdded();
}

void Model::addIntoRent(unsigned int i,unsigned int q){
    DeepPtr<Item> insert = catalogo.searchAtIndex(i);
    rent.insertIntoCart(insert,q);
}

void Model::addIntoBuy(unsigned int i, unsigned int q){
    DeepPtr<Item> insert = catalogo.searchAtIndex(i);
    buyed.insertIntoCart(insert,q);
}

bool Model::editItem(unsigned int i,const QStringList e){
    if(e.at(0)!="null"){
        DeepPtr<Item> elemento;
        if(e.at(0) == "c"){
            elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="1"? 1:0,e.at(6)=="1"? 1:0, e.at(7).toStdString());
        }
        if(e.at(0) == "p"){
            if(e.at(1) == "n")
                elemento = new Normal(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="1"? 1:0, e.at(8)=="1"? 1:0,e.at(9)=="1"? 1:0,e.at(11)=="1"? 1:0);
            if(e.at(1) == "m")
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="1"? 1:0, e.at(7)=="1"? 1:0,e.at(8)==""? 1:0,e.at(9)=="1"? 1:0,e.at(10)=="1"? 1:0,e.at(11)=="1"? 1:0,e.at(12)=="1"? 1:0);
        }
        catalogo.replaceAtIndex(elemento,i);
        return true;
    }
    return false;

}

QString Model::getCatalogElementDetails(unsigned int ind){
//    std::cout << catalogo.size() << std::endl;
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
    if(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))){
            ret.push_back("c");
            ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getVendor()));
            ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getModel()));
            ret.push_back(QString::number(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getCost()));
            ret.push_back(QString::number(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getSize()));
            ret.push_back((dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->isRestored())? "1" : "0");
            ret.push_back((dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->isOriginal())? "1" : "0");
            ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getColorName()));
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(catalogo.searchAtIndex(ind))))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))){
                    ret.push_back("n");
                    ret.push_back(QString::fromStdString(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->getVendor()));
                    ret.push_back(QString::fromStdString(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->getModel()));
                    ret.push_back(QString::number(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->getCost()));
                    ret.push_back(QString::number(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->getDaycost()));
                    ret.push_back((dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->isWiFi())? "1" : "0");
                    ret.push_back((dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->isDoubleSide())? "1" : "0");
                    ret.push_back((dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->isColor())? "1" : "0");
                    ret.push_back((dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->isUsed())? "1" : "0");
                    ret.push_back((dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->isPhoto())? "1" : "0");
                    ret.push_back((dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->isPlotter())? "1" : "0");
            }
            if(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))){
                ret.push_back("m");
                ret.push_back(QString::fromStdString(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getVendor()));
                ret.push_back(QString::fromStdString(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getModel()));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getCost()));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getDaycost()));
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->isWiFi())? "1" : "0");
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->isDoubleSide())? "1" : "0");
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->isColor())? "1" : "0");
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->isUsed())? "1" : "0");
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->isPhoto())? "1" : "0");
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->haveFax())? "1" : "0");
                ret.push_back((dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->haveScanner())? "1" : "0");
            }
        }
        else
            ret.push_back("null");
    }

    return ret;

}

QStringList Model::getRentElement(unsigned int ind){
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
        ret.push_back("c");
        ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getVendor()));
        ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getModel()));
        ret.push_back(QString::number(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getCost()));
        ret.push_back(QString::number(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getSize()));
        ret.push_back(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isRestored()? "1" : "0");
        ret.push_back(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isOriginal()? "1" : "0");
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
                ret.push_back("n");
                ret.push_back(QString::fromStdString((dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getVendor())));
                ret.push_back(QString::fromStdString((dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getModel())));
                ret.push_back(QString::number(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getCost()));
                ret.push_back(QString::number(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getDaycost()));
                ret.push_back(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isWiFi()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isDoubleSide()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isColor()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isUsed()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isPhoto()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isPlotter()? "1" : "0");

            }
            if(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
                ret.push_back("m");
                ret.push_back(QString::fromStdString((dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getVendor())));
                ret.push_back(QString::fromStdString((dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getModel())));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getCost()));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getDaycost()));
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isWiFi()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isDoubleSide()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isColor()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isUsed()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isPhoto()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->haveFax()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->haveScanner()? "1" : "0");
            }
        }
        else
            ret.push_back("null");
    }

    return ret;

}

QStringList Model::getBuyElement(unsigned int ind){
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
        ret.push_back("c");
        ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getVendor()));
        ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getModel()));
        ret.push_back(QString::number(dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getCost()));
        ret.push_back(QString::number(dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getSize()));
        ret.push_back(dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isRestored()? "1" : "0");
        ret.push_back(dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isOriginal()? "1" : "0");
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
                ret.push_back("n");
                ret.push_back(QString::fromStdString((dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getVendor())));
                ret.push_back(QString::fromStdString((dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getModel())));
                ret.push_back(QString::number(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getCost()));
                ret.push_back(QString::number(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getDaycost()));
                ret.push_back(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isWiFi()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isDoubleSide()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isColor()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isUsed()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isPhoto()? "1" : "0");
                ret.push_back(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isPlotter()? "1" : "0");

            }
            if(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))){
                ret.push_back("m");
                ret.push_back(QString::fromStdString((dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getVendor())));
                ret.push_back(QString::fromStdString((dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getModel())));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getCost()));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->getDaycost()));
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isWiFi()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isDoubleSide()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isColor()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isUsed()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->isPhoto()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->haveFax()? "1" : "0");
                ret.push_back(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind)))->first))->haveScanner()? "1" : "0");
            }
        }
        else
            ret.push_back("null");
    }

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

QStringList Model::getAllCatalog()
{
    QStringList ret;
//    std::cout << std::endl <<"ciao" << std::endl;
//    std::cout << std::endl << (*catalogo.getFirst()->info).print() << std::endl;
    auto it=catalogo.begin();
    while(it!=catalogo.end()){
        ret.push_back(QString::fromStdString((*(*it)).getVendor() + " " + (*(*it)).getModel()));
        ++it;
    }

//    std::cout << std::endl << ret.isEmpty() << std::endl;
    return ret;
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
