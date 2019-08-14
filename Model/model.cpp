#include "model.h"

Model::Model(QObject *parent) : QObject(parent),
                                preventiveDate(QDate::currentDate()),
                                catalogo(),
                                rent(),
                                buyed(),
                                filename()
{

}

void Model::removeIntoCatalog(const unsigned int i){
    catalogo.removeOneAtIndex(i);
    emit catalogRemoved();
}

void Model::removeIntoRent(const unsigned int i){
    rent.removeIntoCartAtIndex(i);
    emit rentRemoved();
}

void Model::removeIntoBuy(const unsigned int i){
    buyed.removeIntoCartAtIndex(i);
    emit buyRemoved();
}

void Model::addIntoRent(const unsigned int i, const unsigned int q){
    DeepPtr<Item> insert(catalogo.searchAtIndex(i));
    if(dynamic_cast<const Consumable*>(&(*insert)))
        emit consumableNotRentable();
    else{
        rent.insertIntoCart(insert,q);
        emit rentAdded();
    }
}

void Model::addIntoBuy(const unsigned int i, const unsigned int q){
    DeepPtr<Item> insert(catalogo.searchAtIndex(i));
    buyed.insertIntoCart(insert,q);
    emit buyedAdded();
}

bool Model::editItem(const unsigned int i, const QStringList e){
    if(e.at(0)!="null"){
        DeepPtr<Item> elemento;
        if(e.at(0) == "c"){
            elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="true"? true:false,e.at(6)=="true"? true:false, e.at(7).toStdString());
        }
        if(e.at(0) == "p"){
            if(e.at(1) == "n")
                elemento = new Normal(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? true:false, e.at(8)=="true"? true:false,e.at(9)=="true"? true:false,e.at(11)=="true"? true:false);
            if(e.at(1) == "m")
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? true:false, e.at(7)=="true"? true:false,e.at(8)=="true"? true:false,e.at(9)=="true"? true:false,e.at(10)=="true"? true:false,e.at(11)=="true"? true:false,e.at(12)=="true"? true:false);
        }
        catalogo.replaceAtIndex(elemento,i);
        return true;
    }
    return false;
}

QString Model::getCatalogElementDetails(const unsigned int ind) const{
    return QString::fromStdString((catalogo.searchAtIndex(ind))->print());
}

QString Model::getRentElementDetails(const unsigned int ind) const{
    return QString::fromStdString((rent.searchAtIndex(ind))->print());
}

QString Model::getBuyElementDetails(const unsigned int ind) const{
    return QString::fromStdString((buyed.searchAtIndex(ind))->print());
}

QStringList Model::getCatalogElement(const unsigned int ind) const{
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))){
            const Consumable * item = static_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))));
            ret.push_back("c");
            ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getVendor()));
            ret.push_back(QString::fromStdString(dynamic_cast<const Consumable*>(&(*(catalogo.searchAtIndex(ind))))->getModel()));
            ret.push_back(QString::number(item->getCost()));
            ret.push_back(QString::number(item->getSize()));
            ret.push_back((item->isRestored())? "true":"false");
            ret.push_back((item->isOriginal())? "true":"false");
            ret.push_back(QString::fromStdString(item->getColorName()));
    }
    else {
        if(dynamic_cast<const Stampante*>(&(*(catalogo.searchAtIndex(ind))))){
            ret.push_back("p");
            if(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))){
                    const Normal* item = static_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))));
                    ret.push_back("n");
                    ret.push_back(QString::fromStdString(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->getVendor()));
                    ret.push_back(QString::fromStdString(dynamic_cast<const Normal*>(&(*(catalogo.searchAtIndex(ind))))->getModel()));
                    ret.push_back(QString::number(item->getCost()));
                    ret.push_back(QString::number(item->getDaycost()));
                    ret.push_back((item->isWiFi())? "true":"false");
                    ret.push_back((item->isDoubleSide())? "true":"false");
                    ret.push_back((item->isColor())? "true":"false");
                    ret.push_back((item->isUsed())? "true":"false");
                    ret.push_back((item->isPhoto())? "true":"false");
                    ret.push_back((item->isPlotter())? "true":"false");
            }
            if(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))){
                const Multifunction* item= static_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))));
                ret.push_back("m");
                ret.push_back(QString::fromStdString(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getVendor()));
                ret.push_back(QString::fromStdString(dynamic_cast<const Multifunction*>(&(*(catalogo.searchAtIndex(ind))))->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back((item->isWiFi())? "true":"false");
                ret.push_back((item->isDoubleSide())? "true":"false");
                ret.push_back((item->isColor())? "true":"false");
                ret.push_back((item->isUsed())? "true":"false");
                ret.push_back((item->isPhoto())? "true":"false");
                ret.push_back((item->haveFax())? "true":"false");
                ret.push_back((item->haveScanner())? "true":"false");
            }
        }
        else
            ret.push_back("null");
    }
    return ret;
}

QStringList Model::getRentElement(const unsigned int ind)const{
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
        const Consumable * item = dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
        ret.push_back("c");
        ret.push_back(QString::fromStdString(item->getVendor()));
        ret.push_back(QString::fromStdString(item->getModel()));
        ret.push_back(QString::number(item->getCost()));
        ret.push_back(QString::number(item->getSize()));
        ret.push_back(item->isRestored()? "true":"false");
        ret.push_back(item->isOriginal()? "true":"false");
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
                ret.push_back(item->isWiFi()? "true":"false");
                ret.push_back(item->isDoubleSide()? "true":"false");
                ret.push_back(item->isColor()? "true":"false");
                ret.push_back(item->isUsed()? "true":"false");
                ret.push_back(item->isPhoto()? "true":"false");
                ret.push_back(item->isPlotter()? "true":"false");

            }
            if(dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
                const Multifunction * item = dynamic_cast<const Multifunction*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
                ret.push_back("m");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back(item->isWiFi()? "true":"false");
                ret.push_back(item->isDoubleSide()? "true":"false");
                ret.push_back(item->isColor()? "true":"false");
                ret.push_back(item->isUsed()? "true":"false");
                ret.push_back(item->isPhoto()? "true":"false");
                ret.push_back(item->haveFax()? "true":"false");
                ret.push_back(item->haveScanner()? "true":"false");
            }
        }
        else
            ret.push_back("null");
    }
    return ret;
}

QStringList Model::getBuyElement(const unsigned int ind)const{
    QStringList ret;
    if(dynamic_cast<const Consumable*>(&(*(rent.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
        const Consumable * item = dynamic_cast<const Consumable*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
        ret.push_back("c");
        ret.push_back(QString::fromStdString(item->getVendor()));
        ret.push_back(QString::fromStdString(item->getModel()));
        ret.push_back(QString::number(item->getCost()));
        ret.push_back(QString::number(item->getSize()));
        ret.push_back(item->isRestored()? "true":"false");
        ret.push_back(item->isOriginal()? "true":"false");
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
                ret.push_back(item->isWiFi()? "true":"false");
                ret.push_back(item->isDoubleSide()?"true":"false");
                ret.push_back(item->isColor()? "true":"false");
                ret.push_back(item->isUsed()? "true":"false");
                ret.push_back(item->isPhoto()? "true":"false");
                ret.push_back(item->isPlotter()? "true":"false");

            }
            if(dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()))){
                const Multifunction * item = dynamic_cast<const Multifunction*>(&(*(buyed.searchIntoCart(catalogo.searchAtIndex(ind))).key()));
                ret.push_back("m");
                ret.push_back(QString::fromStdString(item->getVendor()));
                ret.push_back(QString::fromStdString(item->getModel()));
                ret.push_back(QString::number(item->getCost()));
                ret.push_back(QString::number(item->getDaycost()));
                ret.push_back(item->isWiFi()? "true":"false");
                ret.push_back(item->isDoubleSide()? "true":"false");
                ret.push_back(item->isColor()? "true":"false");
                ret.push_back(item->isUsed()? "true":"false");
                ret.push_back(item->isPhoto()? "true":"false");
                ret.push_back(item->haveFax()? "true":"false");
                ret.push_back(item->haveScanner()? "true":"false");
            }
        }
        else
            ret.push_back("null");
    }
    return ret;
}
unsigned int Model::getQuantityRent(const unsigned int i) const{
    return rent.searchIntoCart(catalogo.searchAtIndex(i)).value();
}

unsigned int Model::getQuantityBuy(const unsigned int i)const{
    return buyed.searchIntoCart(catalogo.searchAtIndex(i)).value();
}

void Model::setQuantityRent(const unsigned int ind, const unsigned int q){
    DeepPtr<Item> tmp=catalogo.searchAtIndex(ind);
    rent.setQuantity(tmp,q);
}

void Model::setQuantityBuy(const unsigned int ind, const unsigned int q){
    DeepPtr<Item> tmp=catalogo.searchAtIndex(ind);
    buyed.setQuantity(tmp,q);
}

QStringList Model::getAllCatalog() const
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

QStringList Model::getFilteredCatalog(const QString filter, QMap<unsigned int, unsigned int> &indexMapper) const
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

QStringList Model::getAllRent() const
{
    return rent.printAllCart();
}

QStringList Model::getAllBuyed() const
{
    return buyed.printAllCart();
}

double Model::getAllPriceIntoRent() const
{
    return rent.getTotRentItems();
}

double Model::getAllPriceIntoBuy()const
{
    return buyed.getTotPriceItems();
}

bool Model::checkIfExistIntoCatalog(const QStringList d) const
{
    DeepPtr<Item> elemento;
    if(d.at(0)!="null"){
        if(d.at(0) == "c"){
            elemento = new Consumable(d.at(1).toStdString(),d.at(2).toStdString(),d.at(3).toDouble(),d.at(4).toUInt(),d.at(5)=="true"? true:false,d.at(6)=="true"? true:false, d.at(7).toStdString());
        }
        if(d.at(0) == "p"){
            if(d.at(1) == "n")
                elemento = new Normal(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="true"? true:false, d.at(8)=="true"? true:false,d.at(9)=="true"? true:false,d.at(11)=="true"? true:false);
            if(d.at(1) == "m")
                elemento = new Multifunction(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="true"? true:false ,d.at(7)=="true"? true:false, d.at(8)=="true"? true:false, d.at(9)=="true"? true:false, d.at(10)=="true"? true:false, d.at(11)=="true"? true:false, d.at(12)=="true"? true:false);
        }
    }
    return catalogo.searchIntoList(elemento);
}

unsigned int Model::findItemIntoCatalog(const QStringList d) const
{
    DeepPtr<Item> elemento;
    if(d.at(0)!="null"){
        if(d.at(0) == "c"){
            elemento = new Consumable(d.at(1).toStdString(),d.at(2).toStdString(),d.at(3).toDouble(),d.at(4).toUInt(),d.at(5)=="true"? true:false,d.at(6)=="true"? true:false, d.at(7).toStdString());
        }
        if(d.at(0) == "p"){
            if(d.at(1) == "n")
                elemento = new Normal(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="true"? true:false, d.at(8)=="1"? true:false,d.at(9)=="1"? true:false,d.at(11)=="1"? true:false);
            if(d.at(1) == "m")
                elemento = new Multifunction(d.at(2).toStdString(), d.at(3).toStdString(),d.at(4).toDouble(),d.at(5).toDouble(),d.at(6)=="true"? true:false ,d.at(7)=="true"? true:false, d.at(8)=="true"? true:false, d.at(9)=="true"? true:false, d.at(10)=="true"? true:false, d.at(1)=="true"? true:false, d.at(12)=="true"? true:false);
        }
    }
    return catalogo.getIndex(elemento);
}

bool Model::thereIsSomething() const
{
    return !catalogo.is_empty() || !rent.is_empty() || !buyed.is_empty();
}

void Model::clearTheWorkspace()
{
    catalogo = Container<DeepPtr<Item>>();
    rent = Carrello();
    buyed = Carrello();
}

void Model::setDate(const QDate d){
    preventiveDate=d;
}

QDate Model::getDate() const{
    return preventiveDate;
}

void Model::addIntoCatalog(const QStringList e){
    if(e.at(0)!="null"){
        DeepPtr<Item> elemento;
        if(e.at(0) == "c"){
            elemento = new Consumable(e.at(1).toStdString(),e.at(2).toStdString(),e.at(3).toDouble(),e.at(4).toUInt(),e.at(5)=="true"? true:false,e.at(6)=="true"? true:false, e.at(7).toStdString());
        }
        if(e.at(0) == "p"){
            if(e.at(1) == "n")
                elemento = new Normal(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? true:false, e.at(8)=="true"? true:false,e.at(9)=="true"? true:false,e.at(11)=="true"? true:false);
            if(e.at(1) == "m")
                elemento = new Multifunction(e.at(2).toStdString(), e.at(3).toStdString(),e.at(4).toDouble(),e.at(5).toDouble(),e.at(6)=="true"? true:false ,e.at(7)=="true"? true:false, e.at(8)=="true"? true:false, e.at(9)=="true"? true:false, e.at(10)=="true"? true:false, e.at(11)=="true"? true:false, e.at(12)=="true"? true:false);
        }
        catalogo.pushInOrder(elemento);
    }

    emit elementAdded();
}

void Model::setFilename(const QString flname)
{
    filename=flname;
}

QString Model::loadData()
{
    if(!XmlIO::readItems(filename,catalogo))
        return "Errore in caricamento";
    else
        return "Caricamento avvenuto con successo";
}

QString Model::serializeData()
{
    if(!XmlIO::writeItems(catalogo, filename))
        return "Errore nel salvataggio dei dati";
    else
        return "Salvataggio avvenuto con successo";
}
