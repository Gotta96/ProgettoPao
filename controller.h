#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/model.h"
#include "View/mainwindow.h"
#include "View/modifywindow.h"
#include <QStringList>
#include <QMap>
#include <QFileDialog>

class Controller : public QWidget
{
    Q_OBJECT
private:
    Model *modello;
    MainWindow *mainW;
    InsertionWindow *insertionW;
    ModifyWindow *modifyW;
    QMap<unsigned int,unsigned int> indexTranslate;
public:
    explicit Controller(QWidget *parent = nullptr);

    void replaceIntoCatalog(unsigned int, QStringList);


signals:


public slots:
    void addToCatalogContainer(const QStringList);

    void addToRentCart(unsigned int, unsigned int);
    void addToBuyCart(unsigned int, unsigned int);

    void removeC(unsigned int);
    void removeR(unsigned int);
    void removeB(unsigned int);

    void getDetailsCatalogo(unsigned int);
    void getDetailsRent(unsigned int);
    void getDetailsBuyed(unsigned int);

    void sendForReplace(unsigned int, QStringList);

    void refreshCatalog();
    void refreshRent();
    void refreshBuyed();

    void openAdd();
    void openModify();
    void openSave();
    void openLoad();

    void noConsumableInRent();

    void inputErrorRecived();

};

#endif // CONTROLLER_H
