#ifndef INSERTIONWINDOW_H
#define INSERTIONWINDOW_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QWidget>
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
//#include <QString>

class InsertionWindow : public QDialog
{
    Q_OBJECT

private:
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

public slots:
    void showPrinter();
    void showConsumable();
    void showNormal();
    void showMultifunction();
    void confirm();
    void dimiss();      //implementare la riattivazione della finestra padre

signals:
    void activePrinter();
    void activeConsumable();
    void activeNormalDetails();
    void activeMultifunctionDetails();
    void sendItemsDetails(const QStringList&);
//    void re_active(bool);

};

#endif // INSERTIONWINDOW_H
