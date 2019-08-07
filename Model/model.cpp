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

void Model::removeIntoCatalog(unsigned int i){
    catalogo.removeOneAtIndex(i);
    emit catalogRemoved();
}

void Model::removeIntoRent(unsigned int i){
    rent.removeIntoCartAtIndex(i);
    emit rentRemoved();
}

void Model::removeIntoBuy(unsigned int i){
    buyed.removeIntoCartAtIndex(i);
    emit buyRemoved();
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
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="1"? 1:0 ,e.at(7)=="1"? 1:0, e.at(8)=="1"? 1:0, e.at(9)=="1"? 1:0, e.at(10)=="1"? 1:0, e.at(11)=="1"? 1:0, e.at(12)=="1"? 1:0);
        }
//        std::cout << std::endl << elemento->print() << std::endl;
        catalogo.pushInOrder(elemento);
//        std::cout << std::endl << (*catalogo.getFirst()->info).print() << std::endl;
    }

    emit elementAdded();
}

void Model::addIntoRent(unsigned int i,unsigned int q){
    DeepPtr<Item> insert(catalogo.searchAtIndex(i));
    if(dynamic_cast<const Consumable*>(&(*insert)))
        emit consumableNotRentable();
    else{
        rent.insertIntoCart(insert,q);
        emit rentAdded();
    }
}

void Model::addIntoBuy(unsigned int i, unsigned int q){
    DeepPtr<Item> insert(catalogo.searchAtIndex(i));
    buyed.insertIntoCart(insert,q);
    emit buyedAdded();
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
    return QString::fromStdString((catalogo.searchAtIndex(ind))->print());
}

QString Model::getRentElementDetails(unsigned int ind){ //problema dovuto al fatto che ora passo l'indice relativo alla tabella rent e non più al catalogo, trovare il modo per ottenere il deeptr dell'oggetto selezionato oppure creare funzione interna al carrello
    return QString::fromStdString((rent.searchAtIndex(ind))->print());
}

QString Model::getBuyElementDetails(unsigned int ind){ //problema dovuto al fatto che ora passo l'indice relativo alla tabella rent e non più al catalogo, trovare il modo per ottenere il deeptr dell'oggetto selezionato oppure creare funzione interna al carrello
    return QString::fromStdString((buyed.searchAtIndex(ind))->print());
}

QStringList Model::getCatalogElement(unsigned int ind){      //vedere se si riesce a trasformare i vari puntatoti consumable*, normal* ecc.. in deeptr
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))){
            const Consumable * item = dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))));
            ret.push_back("c");
            ret.push_back(QString::fromStdString(item->getVendor()));
            ret.push_back(QString::fromStdString(item->getModel()));
            ret.push_back(QString::number(item->getCost()));
            ret.push_back(QString::number(item->getSize()));
            ret.push_back((item->isRestored())? "1" : "0");
            ret.push_back((item->isOriginal())? "1" : "0");
            ret.push_back(QString::fromStdString(item->getColorName()));
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(catalogo.searchAtIndex(ind))))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))){
                    const Normal* item = dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))));
                    ret.push_back("n");
                    ret.push_back(QString::fromStdString(item->getVendor()));
                    ret.push_back(QString::fromStdString(item->getModel()));
                    ret.push_back(QString::number(item->getCost()));
                    ret.push_back(QString::number(item->getDaycost()));
                    ret.push_back((item->isWiFi())? "1" : "0");
                    ret.push_back((item->isDoubleSide())? "1" : "0");
                    ret.push_back((item->isColor())? "1" : "0");
                    ret.push_back((item->isUsed())? "1" : "0");
                    ret.push_back((item->isPhoto())? "1" : "0");
                    ret.push_back((item->isPlotter())? "1" : "0");
            }
            if(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))){
                const Multifunction* item= dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))));
                ret.push_back("m");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getDaycost()));
                ret.push_back((item->isWiFi())? "1" : "0");
                ret.push_back((item->isDoubleSide())? "1" : "0");
                ret.push_back((item->isColor())? "1" : "0");
                ret.push_back((item->isUsed())? "1" : "0");
                ret.push_back((item->isPhoto())? "1" : "0");
                ret.push_back((item->haveFax())? "1" : "0");
                ret.push_back((item->haveScanner())? "1" : "0");
            }
        }
        else
            ret.push_back("null");
    }

    return ret;

}

QStringList Model::getRentElement(unsigned int ind){      //vedere se si riesce a trasformare i vari puntatoti consumable*, normal* ecc.. in deeptr
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
        const Consumable * item = dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
        ret.push_back("c");
        ret.push_back(QString::fromStdString(item->getVendor()));
        ret.push_back(QString::fromStdString(item->getModel()));
        ret.push_back(QString::number(item->getCost()));
        ret.push_back(QString::number(item->getSize()));
        ret.push_back(item->isRestored()? "1" : "0");
        ret.push_back(item->isOriginal()? "1" : "0");
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
                const Normal * item = dynamic_cast<const Normal*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
                ret.push_back("n");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back(item->isWiFi()? "1" : "0");
                ret.push_back(item->isDoubleSide()? "1" : "0");
                ret.push_back(item->isColor()? "1" : "0");
                ret.push_back(item->isUsed()? "1" : "0");
                ret.push_back(item->isPhoto()? "1" : "0");
                ret.push_back(item->isPlotter()? "1" : "0");

            }
            if(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
                const Multifunction * item = dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
                ret.push_back("m");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back(item->isWiFi()? "1" : "0");
                ret.push_back(item->isDoubleSide()? "1" : "0");
                ret.push_back(item->isColor()? "1" : "0");
                ret.push_back(item->isUsed()? "1" : "0");
                ret.push_back(item->isPhoto()? "1" : "0");
                ret.push_back(item->haveFax()? "1" : "0");
                ret.push_back(item->haveScanner()? "1" : "0");
            }
        }
        else
            ret.push_back("null");
    }

    return ret;

}

QStringList Model::getBuyElement(unsigned int ind){      //vedere se si riesce a trasformare i vari puntatoti consumable*, normal* ecc.. in deeptr
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
        const Consumable * item = dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
        ret.push_back("c");
        ret.push_back(QString::fromStdString(item->getVendor()));
        ret.push_back(QString::fromStdString(item->getModel()));
        ret.push_back(QString::number(item->getCost()));
        ret.push_back(QString::number(item->getSize()));
        ret.push_back(item->isRestored()? "1" : "0");
        ret.push_back(item->isOriginal()? "1" : "0");
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
                const Normal * item = dynamic_cast<const Normal*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
                ret.push_back("n");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back(item->isWiFi()? "1" : "0");
                ret.push_back(item->isDoubleSide()? "1" : "0");
                ret.push_back(item->isColor()? "1" : "0");
                ret.push_back(item->isUsed()? "1" : "0");
                ret.push_back(item->isPhoto()? "1" : "0");
                ret.push_back(item->isPlotter()? "1" : "0");

            }
            if(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
                const Multifunction * item = dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
                ret.push_back("m");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back(item->isWiFi()? "1" : "0");
                ret.push_back(item->isDoubleSide()? "1" : "0");
                ret.push_back(item->isColor()? "1" : "0");
                ret.push_back(item->isUsed()? "1" : "0");
                ret.push_back(item->isPhoto()? "1" : "0");
                ret.push_back(item->haveFax()? "1" : "0");
                ret.push_back(item->haveScanner()? "1" : "0");
            }
        }
        else
            ret.push_back("null");
    }

    return ret;

}

unsigned int Model::getQuantityRent(unsigned int i){
    return rent.searchIntoCart(catalogo.searchAtIndex(i)).value();
}

unsigned int Model::getQuantityBuy(unsigned int i){
    return buyed.searchIntoCart(catalogo.searchAtIndex(i)).value();
}

void Model::setQuantityRent(unsigned int ind, unsigned int q){
    rent.searchIntoCart(catalogo.searchAtIndex(ind)).value()=q;
}

void Model::setQuantityBuy(unsigned int ind, unsigned int q){
    buyed.searchIntoCart(catalogo.searchAtIndex(ind)).value()=q;
}

bool Model::checkIfExistIntoCatalog(QStringList d)
{
    DeepPtr<Item> elemento;
    if(d.at(0)!="null"){
        if(d.at(0) == "c"){
            elemento = new Consumable(d.at(1).toStdString(),d.at(2).toStdString(),d.at(3).toDouble(),d.at(4).toUInt(),d.at(5)=="1"? 1:0,d.at(6)=="1"? 1:0, d.at(7).toStdString());
        }
        if(d.at(0) == "p"){
            if(d.at(1) == "n")
                elemento = new Normal(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="1"? 1:0, d.at(8)=="1"? 1:0,d.at(9)=="1"? 1:0,d.at(11)=="1"? 1:0);
            if(d.at(1) == "m")
                elemento = new Multifunction(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="1"? 1:0 ,d.at(7)=="1"? 1:0, d.at(8)=="1"? 1:0, d.at(9)=="1"? 1:0, d.at(10)=="1"? 1:0, d.at(11)=="1"? 1:0, d.at(12)=="1"? 1:0);
        }
    }
    return catalogo.searchIntoList(elemento);
}

unsigned int Model::findItemIntoCatalog(QStringList d)
{
    DeepPtr<Item> elemento;
    if(d.at(0)!="null"){
        if(d.at(0) == "c"){
            elemento = new Consumable(d.at(1).toStdString(),d.at(2).toStdString(),d.at(3).toDouble(),d.at(4).toUInt(),d.at(5)=="1"? 1:0,d.at(6)=="1"? 1:0, d.at(7).toStdString());
        }
        if(d.at(0) == "p"){
            if(d.at(1) == "n")
                elemento = new Normal(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="1"? 1:0, d.at(8)=="1"? 1:0,d.at(9)=="1"? 1:0,d.at(11)=="1"? 1:0);
            if(d.at(1) == "m")
                elemento = new Multifunction(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="1"? 1:0 ,d.at(7)=="1"? 1:0, d.at(8)=="1"? 1:0, d.at(9)=="1"? 1:0, d.at(10)=="1"? 1:0, d.at(11)=="1"? 1:0, d.at(12)=="1"? 1:0);
        }
    }

    return catalogo.getIndex(elemento);
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
    QString etichetta;
    auto it=catalogo.begin();
    if(!catalogo.is_empty()){
        while(it!=catalogo.end()){
            etichetta = (QString::fromStdString((*(*it)).getVendor() + " " + (*(*it)).getModel()) + " ");
            if(dynamic_cast<const Consumable*>(&(*(*it))))
                etichetta += (QString::fromStdString(dynamic_cast<const Consumable*>(&(*(*it)))->getColorName()));
            ret.push_back(etichetta);
            ++it;
        }
    }

    return ret;
}

QStringList Model::getFilteredCatalog(QString filter, QMap<unsigned int, unsigned int> &indexMapper)
{
    QStringList ret;
    QString etichetta;
    QRegExp regex(filter,Qt::CaseInsensitive, QRegExp::Wildcard);
    auto it=catalogo.begin();
    unsigned int count=0;
    if(!catalogo.is_empty()){
        while(it!=catalogo.end()){
            etichetta = (QString::fromStdString((*(*it)).getVendor() + " " + (*(*it)).getModel()) + " ");
            if(etichetta.contains(regex)){
                indexMapper.insert((uint)ret.count(),count);
                if(dynamic_cast<const Consumable*>(&(*(*it))))
                    etichetta += (QString::fromStdString(dynamic_cast<const Consumable*>(&(*(*it)))->getColorName()));
                ret.push_back(etichetta);
            }
            count++;
            ++it;
        }
    }

    return ret;
}

QStringList Model::getAllRent()
{
    return rent.printAllCart();
}

QStringList Model::getAllBuyed()
{
    return buyed.printAllCart();
}

double Model::getAllPriceIntoRent()
{
    return rent.getTotRentItems();
}

double Model::getAllPriceIntoBuy()
{
    return buyed.getTotPriceItems();
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
