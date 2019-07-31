#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    //connessioni segnali della main window
    connect(mainW, SIGNAL(clickedNoleggia(unsigned int, unsigned int)), this, SLOT(addToRentCart(unsigned int, unsigned int)));
    connect(mainW, SIGNAL(clickedCompra(unsigned int, unsigned int)), this, SLOT(addToBuyCart(unsigned int, unsigned int)));
    connect(mainW, SIGNAL(clickedRemoveRent(unsigned int)), this, SLOT(removeR(unsigned int)));
    connect(mainW, SIGNAL(clickedRemoveBuyed(unsigned int)), this, SLOT(removeB(unsigned int)));
    connect(mainW, SIGNAL(requestDetails(unsigned int)), this, SLOT(getDetails(unsigned int)));
    //segnali arrivanti dalle inserion e modify window interne alla main window
    connect(mainW, SIGNAL(sendItemsDetails(const QStringList&)), this, SLOT(addToCatalogContainer(const QStringList&)));
    connect(mainW, SIGNAL(replaceItem(unsigned int, QStringList)), this, SLOT(replaceIntoCatalog(unsigned int, QStringList)));
    //connessioni segnali arrivanti dal modello
    connect(modello, SIGNAL(showCatalog(const QStringList)), SIGNAL(sendToMainTheCatalog(const QStringList)));
}

void Controller::replaceIntoCatalog(unsigned int index, QStringList details)
{
    modello->editItem(index,details);
}

QStringList Controller::getDetails(unsigned int index)
{
    return modello->getCatalogElement(index);
}

bool Controller::removeC(unsigned int index)
{
    return modello->removeIntoCatalog(index);
}

bool Controller::removeB(unsigned int index)
{
    return modello->removeIntoRent(index);
}

void Controller::addToCatalogContainer(const QStringList& details)
{
    modello->addIntoCatalog(details);
    modello->getAllCatalog();
}

void Controller::addToRentCart(unsigned int index, unsigned int quantity)
{
    modello->addIntoRent(index,quantity);
}

void Controller::addToBuyCart(unsigned int index, unsigned int quantity)
{
    modello->addIntoBuy(index, quantity);
}

bool Controller::removeR(unsigned int index)
{
    return modello->removeIntoBuy(index);
}


