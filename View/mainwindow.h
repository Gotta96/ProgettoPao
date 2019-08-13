#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QMenuBar>
#include <QSpinBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QString>
#include "View/smartlistview.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineEdit *name, *iva, *find;
    QSpinBox *quantity;
    QDateEdit *date;
    SmartListView *elements, *rent, *buyed;
    QLabel *details, *totrent, *totbuyed;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //~MainWindow() override;

    void displayCatalog(const QStringList);
    void displayRent(const QStringList);
    void displayBuyed(const QStringList);
    void displayInputError();
    void displayNotSelection();
    void displayDetails(const QString);
    void displayTotals(double, double);
    void displayErrorForConsumableRent();
    void displayOpenError();
    void displayIvaError();
    void displayLoad(QString);
    void displaySave(QString);

    bool isSelected() const;
    unsigned int getCatalogSelected() const;

    const QString getResearchWord() const;

    QString getClientName() const;
    QString getClientPiva()const;

public slots:
    void updateDetails(QString info);
    void generateRent();
    void generateBuyed();
    void destroyRent();
    void destroyBuyed();

    void catalogSelected(int);
    void rentSelected(int);
    void buyedSelected(int);

    void removeRequest();

signals:
    void openAddToCatalogWindow();
    void requestToOpenModify();
    void requestRemoveIntoCatalog(unsigned int);
    void openLoadWindow();
    void openSaveWindow();
    void openSavePDFWindow();
    void updateSearch();
    void clickedNoleggia(unsigned int i, unsigned int q);
    void clickedCompra(unsigned int i, unsigned int q);
    void clickedRemoveRent(unsigned int i);
    void clickedRemoveBuyed(unsigned int i);
    void requestDetailsCatalog(unsigned int);
    void requestDetailsRent(unsigned int);
    void requestDetailsBuyed(unsigned int);

};

#endif // MAINWINDOW_H
