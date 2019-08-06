#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/model.h"
#include "View/mainwindow.h"
#include "View/modifywindow.h"
#include <QStringList>

class Controller : public QWidget
{
    Q_OBJECT
private:
    Model *modello;
    MainWindow *mainW;
    InsertionWindow *insertionW;
    ModifyWindow *modifyW;

public:
    explicit Controller(QWidget *parent = nullptr);

    void replaceIntoCatalog(unsigned int, QStringList);

signals:

//    void sendToMainTheCatalog(const QStringList);

public slots:
    void addToCatalogContainer(const QStringList);

    void addToRentCart(unsigned int, unsigned int);
    void addToBuyCart(unsigned int, unsigned int);

    void removeC(unsigned int);
    void removeR(unsigned int);
    void removeB(unsigned int);

    void getDetails(unsigned int);

    void sendForReplace(unsigned int, QStringList);

    void refreshCatalog();
    void refreshRent();
    void refreshBuyed();

    void openAdd();
    void openModify();

};

#endif // CONTROLLER_H
