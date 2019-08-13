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

    void replaceIntoCatalog(unsigned int, QStringList);


signals:


public slots:
    void addToCatalogContainer(const QStringList);

    void addToRentCart(unsigned int, unsigned int);
    void addToBuyCart(unsigned int, unsigned int);

    void removeC(unsigned int);
    void removeR(unsigned int);
    void removeB(unsigned int);

    void getDetailsCatalogo(unsigned int) const;
    void getDetailsRent(unsigned int) const;
    void getDetailsBuyed(unsigned int) const;

    void sendForReplace(unsigned int, QStringList);

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
