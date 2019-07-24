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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //~MainWindow() override;

public slots:
    void updateDetails(QString info, QString imgpath);
    void updateTotals(QStringList prezzi);
    void generateRent();
    void generateBuyed();
    void destroyRent();
    void destroyBuyed();

    void catalogSelected();
    void rentSelected();
    void buySelected();

    void openModify();
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

};

#endif // MAINWINDOW_H
