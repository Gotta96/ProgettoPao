#ifndef INSERTIONWINDOW_H
#define INSERTIONWINDOW_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStringList>

class InsertionWindow : public QDialog
{
    Q_OBJECT

protected:
    QLineEdit *marca, *modello, *cost, *daycost, *size, *colorName;
    QCheckBox *restore, *original, *scanner, *fax, *wifi, *doubleside, *color, *used, *photo, *plotter;
    QRadioButton *consumable, *printer, *normale, *multifunction;

    QGroupBox *itemBaseDetails;
    QGroupBox *elementSelectionBox;
    QGroupBox *consumableDetails;
    QGroupBox *typeSelectionBox;
    QGroupBox *printerDetails;
    QGroupBox *normalDetails ;
    QGroupBox *multifunctionDetails;

public:
    explicit InsertionWindow(QWidget *parent = nullptr);

    void resetForNewInsertion();

public slots:
    void showPrinter();
    void showConsumable();
    void showNormal();
    void showMultifunction();
    virtual void confirm();
    void dimiss();

signals:
    void activePrinter();
    void activeConsumable();
    void activeNormalDetails();
    void activeMultifunctionDetails();
    void sendItemsDetails(const QStringList);

};

#endif // INSERTIONWINDOW_H
