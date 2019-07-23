#include "insertionwindow.h"

InsertionWindow::InsertionWindow(QWidget *parent) : QDialog(parent),
                                                    marca(new QLineEdit("Marca")),
                                                    modello(new QLineEdit("Modello")),
                                                    item(new QRadioButton("Prova"))
{
    QWidget *insertionWidget = new QWidget(this);
    QVBoxLayout *insertionLayout = new QVBoxLayout();

    QVBoxLayout *mainDetails = new QVBoxLayout();
    QHBoxLayout *mainAndSubMainDetails = new QHBoxLayout();

    mainDetails->addWidget(marca);
    mainDetails->addWidget(modello);

    mainAndSubMainDetails->addLayout(mainDetails);
    mainAndSubMainDetails->addWidget(item);
}
