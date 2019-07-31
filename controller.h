#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Model/model.h"
#include "View/mainwindow.h"
#include "View/insertionwindow.h"
#include "View/modifywindow.h"
#include <QStringList>

class Controller : public QObject
{
    Q_OBJECT
private:
    Model *modello;
    MainWindow *mainW;
    InsertionWindow *insertionW;

public:
    explicit Controller(QObject *parent = nullptr);

    void replaceIntoCatalog(unsigned int, QStringList);

    QStringList getDetails(unsigned int);

    bool removeC(unsigned int);
    bool removeR(unsigned int);
    bool removeB(unsigned int);

    void addToCatalogContainer(const QStringList&);
    void addToRentCart(unsigned int, unsigned int);
    void addToBuyCart(unsigned int, unsigned int);


signals:

    void sendToMainTheCatalog(const QStringList);

public slots:


};

#endif // CONTROLLER_H
