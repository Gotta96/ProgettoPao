#include "controller.h"

Controller::Controller(QWidget *parent) : QWidget(parent),
                                          modello(new Model(this)),
                                          mainW(new MainWindow(this)),
                                          insertionW(new InsertionWindow(mainW)),
                                          modifyW(new ModifyWindow(mainW)){
    mainW->show();

    //connessioni segnali della main window
    connect(mainW, SIGNAL(clickedNoleggia(unsigned int, unsigned int)), this, SLOT(addToRentCart(unsigned int, unsigned int)));
    connect(mainW, SIGNAL(clickedCompra(unsigned int, unsigned int)), this, SLOT(addToBuyCart(unsigned int, unsigned int)));
    connect(mainW, SIGNAL(clickedRemoveRent(unsigned int)), this, SLOT(removeR(unsigned int)));
    connect(mainW, SIGNAL(clickedRemoveBuyed(unsigned int)), this, SLOT(removeB(unsigned int)));
    connect(mainW, SIGNAL(requestDetailsCatalog(unsigned int)), this, SLOT(getDetailsCatalogo(unsigned int)));
    connect(mainW, SIGNAL(requestDetailsRent(unsigned int)), this, SLOT(getDetailsRent(unsigned int)));
    connect(mainW, SIGNAL(requestDetailsBuyed(unsigned int)), this, SLOT(getDetailsBuyed(unsigned int)));
    connect(mainW, SIGNAL(openAddToCatalogWindow()), this, SLOT(openAdd()));
    connect(mainW, SIGNAL(requestToOpenModify()), this, SLOT(openModify()));
    connect(mainW, SIGNAL(requestRemoveIntoCatalog(unsigned int)), this, SLOT(removeC(unsigned int)));
    connect(mainW, SIGNAL(openSaveWindow()), this, SLOT(openSave()));
    connect(mainW, SIGNAL(openLoadWindow()), this, SLOT(openLoad()));
    connect(mainW, SIGNAL(openSavePDFWindow()), this, SLOT(openSavePDF()));

    connect(mainW, SIGNAL(updateSearch()), this, SLOT(refreshCatalog()));

    //connessioni segnali della insertion e della modify window
    connect(insertionW, SIGNAL(sendItemsDetails(const QStringList)), this, SLOT(addToCatalogContainer(const QStringList)));
    connect(insertionW, SIGNAL(inputError()), this, SLOT(inputErrorRecived()));
    connect(modifyW, SIGNAL(replaceItem(unsigned int, QStringList)), this, SLOT(sendForReplace(unsigned int, QStringList)));
    connect(modifyW, SIGNAL(inputError()), this, SLOT(inputErrorRecived()));

    //connessioni segnali arrivanti dal modello
    connect(modello, SIGNAL(elementAdded()), this, SLOT(refreshCatalog()));
    connect(modello, SIGNAL(rentAdded()), this, SLOT(refreshRent()));
    connect(modello, SIGNAL(buyedAdded()), this, SLOT(refreshBuyed()));
    connect(modello, SIGNAL(catalogRemoved()), this, SLOT(refreshCatalog()));
    connect(modello, SIGNAL(rentRemoved()), this, SLOT(refreshRent()));
    connect(modello, SIGNAL(buyRemoved()), this, SLOT(refreshBuyed()));
    connect(modello, SIGNAL(consumableNotRentable()), this, SLOT(noConsumableInRent()));

}

void Controller::replaceIntoCatalog(unsigned int index, QStringList details)
{
    modello->editItem(indexTranslate[index],details);
}

void Controller::openAdd()
{
    insertionW->resetForNewInsertion();
    insertionW->setModal(true);
    insertionW->show();
}

void Controller::openModify()
{
    if(mainW->isSelected()){
        modifyW->loadDataForEdit(modello->getCatalogElement(mainW->getCatalogSelected()), mainW->getCatalogSelected());
        modifyW->setModal(true);
        modifyW->show();
    }
    else
        mainW->displayNotSelection();
}

void Controller::openSave()
{
    QString nomeFile = QFileDialog::getSaveFileName(mainW,"salva","../ProgettoPao/Cataloghi","File di catalogo (*.xml)");
    if(nomeFile =="")
        modello->setFilename("catalog.xml");
    else {
        if(!nomeFile.endsWith(".xml"))
            nomeFile=nomeFile+".xml";
        modello->setFilename(nomeFile);
        mainW->displaySave(modello->serializeData());
    }
}
void Controller::openLoad()
{
    QString nomeFile = QFileDialog::getOpenFileName(mainW,"carica","../ProgettoPao/Cataloghi","File di catalogo (*.xml)");
    if(nomeFile == "")
        mainW->displayOpenError();
    else {
        if(modello->thereIsSomething())
            modello->clearTheWorkspace();
        modello->setFilename(nomeFile);
        mainW->displayLoad(modello->loadData());
        refreshCatalog();
        refreshRent();
        refreshBuyed();
    }
}

void Controller::openSavePDF()
{
    QString nomeFile = QFileDialog::getSaveFileName(mainW,"salva PDF","../ProgettoPao/Preventivi");
    if(nomeFile =="")
        nomeFile=("preventivo_"+modello->getDate().toString("dmy")+".xml");
    else {
        if(!nomeFile.endsWith(".pdf"))
            nomeFile=nomeFile+".pdf";
        QStringList r = modello->getAllRent();
        QStringList b = modello->getAllBuyed();
        QPdfWriter writer(nomeFile);
        QPainter painter(&writer);
        painter.setPen(Qt::black);

        painter.drawText(100,200, "Cliente: "+ mainW->getClientName());
        painter.drawText(3750,200,"Partita Iva: " + mainW->getClientPiva());
        painter.drawText(7750,200,"Data: " + modello->getDate().toString());
        painter.drawText(1200,1000,"Lista Noleggio");
        painter.drawText(6300,1000,"Lista Compere");
        int l=800 ,a1=1400;
        auto rent_it= r.begin();
        while(rent_it!=r.end()){
            painter.drawText(l,a1,*rent_it);
            rent_it++;
            a1+=300;
        }
        l=5800;
        int a2=1400;
        auto buyed_it=b.begin();
        while(buyed_it!=b.end()){
            painter.drawText(l,a2,*buyed_it);
            buyed_it++;
            a2+=300;
        }
        if(a1>a2){
            painter.drawText(950,a1+500,"Totale noleggiato: "+QString::number(modello->getAllPriceIntoRent()) + "€");
            painter.drawText(5950,a1+500,"Totale noleggiato: "+QString::number(modello->getAllPriceIntoBuy()) + "€");
        }
        else {
            painter.drawText(950,a2+500,"Totale noleggiato: "+QString::number(modello->getAllPriceIntoRent()) + "€");
            painter.drawText(5950,a2+500,"Totale noleggiato: "+QString::number(modello->getAllPriceIntoBuy()) + "€");
        }

        painter.drawText(200,13700,"Preventivo by FastPreventive, developed by Gotta's Solutions");
        painter.end();
    }
}

void Controller::noConsumableInRent()
{
    mainW->displayErrorForConsumableRent();
}

void Controller::inputErrorRecived()
{
    insertionW->displayInputError();
}

void Controller::getDetailsCatalogo(unsigned int index)
{
    mainW->displayDetails(modello->getCatalogElementDetails(indexTranslate[index]));
}

void Controller::getDetailsRent(unsigned int index)
{
    mainW->displayDetails(modello->getRentElementDetails(index));
}

void Controller::getDetailsBuyed(unsigned int index)
{
    mainW->displayDetails(modello->getBuyElementDetails(index));
}

void Controller::removeC(unsigned int index)
{
    modello->removeIntoCatalog(indexTranslate[index-1]);
    refreshCatalog();
}

void Controller::removeR(unsigned int index)
{
    modello->removeIntoRent(index);
}

void Controller::removeB(unsigned int index)
{
    modello->removeIntoBuy(index);
}

void Controller::addToCatalogContainer(const QStringList details)
{
    if(details.first()=="null")
        mainW->displayInputError();
    else {
        if(details[1]=="null")
            mainW->displayInputError();
        else{
            if(!modello->checkIfExistIntoCatalog(details))
                modello->addIntoCatalog(details);
            else{
                modello->editItem(modello->findItemIntoCatalog(details),details);
            }
        }
    }
}

void Controller::addToRentCart(unsigned int index, unsigned int quantity)
{
    if(quantity!=0)
        modello->addIntoRent(indexTranslate[index],quantity);
}

void Controller::addToBuyCart(unsigned int index, unsigned int quantity)
{
    if(quantity!=0)
        modello->addIntoBuy(indexTranslate[index], quantity);
}

void Controller::sendForReplace(unsigned int index, QStringList elem)
{
    modello->editItem(indexTranslate[index-1], elem);
    refreshCatalog();
}

void Controller::refreshCatalog()
{
    QString filter=mainW->getResearchWord();
    mainW->displayCatalog(modello->getFilteredCatalog(filter,indexTranslate));
}

void Controller::refreshRent()
{
    mainW->displayRent(modello->getAllRent());
    mainW->displayTotals(modello->getAllPriceIntoRent(), modello->getAllPriceIntoBuy());
}

void Controller::refreshBuyed()
{
    mainW->displayBuyed(modello->getAllBuyed());
    mainW->displayTotals(modello->getAllPriceIntoRent(), modello->getAllPriceIntoBuy());
}

