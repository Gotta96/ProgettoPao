#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/model.h"
#include "View/mainwindow.h"
#include "View/insertionwindow.h"
#include "View/modifywindow.h"
#include <QStringList>
#include <QMap>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>

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

    void replaceIntoCatalog(const unsigned int,const QStringList);


signals:


public slots:
    void addToCatalogContainer(const QStringList);

    void addToRentCart(const unsigned int,const unsigned int);
    void addToBuyCart(const unsigned int,const unsigned int);

    void removeC(const unsigned int);
    void removeR(const unsigned int);
    void removeB(const unsigned int);

    void getDetailsCatalogo(const unsigned int) const;
    void getDetailsRent(const unsigned int) const;
    void getDetailsBuyed(const unsigned int) const;

    void sendForReplace(const unsigned int,const QStringList);

    void refreshCatalog();
    void refreshRent();
    void refreshBuyed();

    void openAdd() const;
    void openModify() const;
    void openSave() const;
    void openLoad();
    void openSavePDF() const;

    void noConsumableInRent();

    void inputErrorRecived();

};

#endif // CONTROLLER_H
