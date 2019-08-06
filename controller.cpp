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

    //connessioni segnali della insertion e della modify window
    connect(insertionW, SIGNAL(sendItemsDetails(const QStringList)), this, SLOT(addToCatalogContainer(const QStringList)));
    connect(modifyW, SIGNAL(replaceItem(unsigned int, QStringList)), this, SLOT(sendForReplace(unsigned int, QStringList)));

    //connessioni segnali arrivanti dal modello
    connect(modello, SIGNAL(elementAdded()), this, SLOT(refreshCatalog()));
    connect(modello, SIGNAL(rentAdded()), this, SLOT(refreshRent()));
    connect(modello, SIGNAL(buyedAdded()), this, SLOT(refreshBuyed()));
    connect(modello, SIGNAL(catalogRemoved()), this, SLOT(refreshCatalog()));
    connect(modello, SIGNAL(rentRemoved()), this, SLOT(refreshRent()));
    connect(modello, SIGNAL(buyRemoved()), this, SLOT(refreshBuyed()));
}

void Controller::replaceIntoCatalog(unsigned int index, QStringList details)
{
    modello->editItem(index,details);
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

void Controller::getDetailsCatalogo(unsigned int index)
{
    mainW->displayDetails(modello->getCatalogElementDetails(index));
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
    modello->removeIntoCatalog(index);
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
        modello->addIntoRent(index,quantity);
}

void Controller::addToBuyCart(unsigned int index, unsigned int quantity)
{
    if(quantity!=0)
        modello->addIntoBuy(index, quantity);
}

void Controller::sendForReplace(unsigned int index, QStringList elem)
{
    modello->editItem(index, elem);
    refreshCatalog();
}

void Controller::refreshCatalog()
{
    mainW->displayCatalog(modello->getAllCatalog());
}

void Controller::refreshRent()
{
    mainW->displayRent(modello->getAllRent());
}

void Controller::refreshBuyed()
{
    mainW->displayBuyed(modello->getAllBuyed());
}

