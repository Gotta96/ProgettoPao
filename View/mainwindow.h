#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListView>
#include <QLabel>
#include <QDateEdit>
#include <QMenuBar>
#include <QSpinBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QString>
#include "View/smartlistview.h"
#include "View/insertionwindow.h"
#include "View/modifywindow.h"
#include <QStringListModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineEdit *name, *iva, *find;
    QSpinBox *quantity;
    QDateEdit *date;
    SmartListView *elements, *rent, *buyed;
    QLabel *details, *image, *totrent, *totbuyed, *tot;

    InsertionWindow *insWindow;

    ModifyWindow *modWindow;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //~MainWindow() override;

    void displayCatalog(const QStringList);

public slots:
    void updateDetails(QString info, QString imgpath);
    void updateTotals(QStringList prezzi);
//    void addToCatalog(QStringList);
    void generateRent();
    void generateBuyed();
    void destroyRent();
    void destroyBuyed();

    void catalogSelected(const QModelIndex& index);
    void rentSelected(const QModelIndex&);
    void buyedSelected(const QModelIndex&);

    void openModify(QStringList,unsigned int);
    void openAdd();

signals:
//    void openModifyCatalogWindow();
//    void openAddToCatalogWndow();
    void openLoadWindow();
    void openSaveWindow();
    void openSavePDFWindow();
    void updateSearch(const QString &text);
    void clickedNoleggia(unsigned int i, unsigned int q);
    void clickedCompra(unsigned int i, unsigned int q);
    void clickedRemoveRent(unsigned int i);
    void clickedRemoveBuyed(unsigned int i);
    void requestDetails(unsigned int);
};

#endif // MAINWINDOW_H
