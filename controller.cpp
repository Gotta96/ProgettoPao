#include "controller.h"

Controller::Controller(QWidget *parent) : QWidget(parent),
                                          modello(new Model(this)),
                                          mainW(new MainWindow(this)),
                                          insertionW(new InsertionWindow(mainW))
{
    mainW->show();

    connect(insertionW, SIGNAL(sendItemsDetails(const QStringList)), this, SLOT(addToCatalogContainer(const QStringList)));

    //connessioni segnali della main window
    connect(mainW, SIGNAL(clickedNoleggia(unsigned int, unsigned int)), this, SLOT(addToRentCart(unsigned int, unsigned int)));
    connect(mainW, SIGNAL(clickedCompra(unsigned int, unsigned int)), this, SLOT(addToBuyCart(unsigned int, unsigned int)));
    connect(mainW, SIGNAL(clickedRemoveRent(unsigned int)), this, SLOT(removeR(unsigned int)));
    connect(mainW, SIGNAL(clickedRemoveBuyed(unsigned int)), this, SLOT(removeB(unsigned int)));
    connect(mainW, SIGNAL(requestDetails(unsigned int)), this, SLOT(getDetails(unsigned int)));
    connect(mainW, SIGNAL(openAddToCatalogWindow()), this, SLOT(openAdd()));
    //segnali arrivanti dalle inserion e modify window interne alla main window
    connect(mainW, SIGNAL(requestDetailsForEdit()), this, SLOT(getDetailsForEdit()));
    connect(mainW, SIGNAL(requestForReplace(unsigned int, QStringList)), this, SLOT(sendForReplace(unsigned int, QStringList)));
    //connessioni segnali arrivanti dal modello
//    connect(modello, SIGNAL(showCatalog(const QStringList)), SIGNAL(sendToMainTheCatalog(const QStringList)));
    connect(modello, SIGNAL(elementAdded()), this, SLOT(refreshCatalog()));
}

void Controller::replaceIntoCatalog(unsigned int index, QStringList details)
{
    modello->editItem(index,details);
}

void Controller::openAdd()
{
    insertionW->setModal(true);
    insertionW->show();
}

void Controller::getDetails(unsigned int index)
{
    mainW->displayDetails(modello->getCatalogElementDetails(index));
}

void Controller::removeC(unsigned int index)
{
    modello->removeIntoCatalog(index);
}

void Controller::removeB(unsigned int index)
{
    modello->removeIntoRent(index);
}

void Controller::addToCatalogContainer(const QStringList details)
{
    if(details.first()=="null")
        mainW->displayInputError();
    else {
        if(details[1]=="null")
            mainW->displayInputError();
        else{
            modello->addIntoCatalog(details);
            std::cout << modello->getAllCatalog().first().toStdString();
        }
    }
}

void Controller::addToRentCart(unsigned int index, unsigned int quantity)
{
    modello->addIntoRent(index,quantity);
}

void Controller::addToBuyCart(unsigned int index, unsigned int quantity)
{
    modello->addIntoBuy(index, quantity);
}

void Controller::sendForReplace(unsigned int index, QStringList elem)
{
    modello->editItem(index, elem);
    refreshCatalog();
}

void Controller::getDetailsForEdit()
{
    mainW->openModify(modello->getCatalogElement(mainW->getCatalogSelected()), mainW->getCatalogSelected());
}

void Controller::refreshCatalog()
{
    mainW->displayCatalog(modello->getAllCatalog());
}

void Controller::removeR(unsigned int index)
{
    modello->removeIntoBuy(index);
}


