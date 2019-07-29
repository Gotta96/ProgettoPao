#include "insertionwindow.h"

InsertionWindow::InsertionWindow(QWidget *parent) : QDialog(parent),
                                                    marca(new QLineEdit("",this)),
                                                    modello(new QLineEdit("",this)),
                                                    cost(new QLineEdit("",this)),
                                                    daycost(new QLineEdit("",this)),
                                                    size(new QLineEdit("",this)),
                                                    colorName(new QLineEdit("",this)),
                                                    restore(new QCheckBox("Rigenerata",this)),
                                                    original(new QCheckBox("Originale",this)),
                                                    scanner(new QCheckBox("Scanner",this)),
                                                    fax(new QCheckBox("Fax",this)),
                                                    wifi(new QCheckBox("Wify",this)),
                                                    doubleside(new QCheckBox("Fronte-Retro",this)),
                                                    color(new QCheckBox("Colori",this)),
                                                    used(new QCheckBox("Usato",this)),
                                                    photo(new QCheckBox("Forografie",this)),
                                                    plotter(new QCheckBox("Plotter",this)),
                                                    consumable(new QRadioButton("Cartuccia",this)),
                                                    printer(new QRadioButton("Stampante",this)),
                                                    normale(new QRadioButton("Normale",this)),
                                                    multifunction(new QRadioButton("Multifunzione",this)),
                                                    itemBaseDetails(new QGroupBox("Dettagli di base della stampante",this)),
                                                    elementSelectionBox(new QGroupBox("Seleziona prodotto",this)),
                                                    consumableDetails(new QGroupBox("Dettagli cartuccia",this)),
                                                    typeSelectionBox(new QGroupBox("Tipo di stampante",this)),
                                                    printerDetails(new QGroupBox("Dettagli stampante",this)),
                                                    normalDetails(new QGroupBox("Dettagli stampante normale",this)),
                                                    multifunctionDetails(new QGroupBox("Dettagli stampante multifunzione",this))
{
    QVBoxLayout *mainInsertionLayout = new QVBoxLayout();
    QGridLayout *grid= new QGridLayout();

    QPushButton *ok = new QPushButton("Conferma");
    QPushButton *no = new QPushButton("Annulla");

    QLabel *vendorLabel = new QLabel("Marca: ");
    QLabel *modelLabel = new QLabel("Modello: ");
    QLabel *costLabel = new QLabel("Prezzo (€): ");
    QLabel *dayCostLabel = new QLabel("Prezzo al giorno (€): ");
    QLabel *colorNameLabel = new QLabel("Colore: ");
    QLabel *sizeLabel = new QLabel("Dimensione: ");

    QHBoxLayout *vendorLayout = new QHBoxLayout();
    QHBoxLayout *modelLayout = new QHBoxLayout();
    QHBoxLayout *costLayout = new QHBoxLayout();
    QHBoxLayout *dayCostLayout = new QHBoxLayout();
    QHBoxLayout *colorNameLayout = new QHBoxLayout();
    QHBoxLayout *sizeLayout = new QHBoxLayout();

    QVBoxLayout *normalLayout = new QVBoxLayout();
    QVBoxLayout *multifunctionLayout = new QVBoxLayout();
    QVBoxLayout *consumableLayout = new QVBoxLayout();
    QVBoxLayout *itemBaseLayout = new QVBoxLayout();
    QVBoxLayout *elementLayout = new QVBoxLayout();
    QVBoxLayout *typeLayout = new QVBoxLayout();
    QVBoxLayout *printerLayout = new QVBoxLayout();

    vendorLayout->addWidget(vendorLabel);
    vendorLayout->addWidget(marca);

    modelLayout->addWidget(modelLabel);
    modelLayout->addWidget(modello);

    costLayout->addWidget(costLabel);
    costLayout->addWidget(cost);

    dayCostLayout->addWidget(dayCostLabel);
    dayCostLayout->addWidget(daycost);

    colorNameLayout->addWidget(colorNameLabel);
    colorNameLayout->addWidget(colorName);

    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(size);


    normalLayout->addWidget(plotter);

    multifunctionLayout->addWidget(scanner);
    multifunctionLayout->addWidget(fax);

    consumableLayout->addLayout(sizeLayout);
    consumableLayout->addLayout(colorNameLayout);
    consumableLayout->addWidget(restore);
    consumableLayout->addWidget(original);

    itemBaseLayout->addLayout(vendorLayout);
    itemBaseLayout->addLayout(modelLayout);
    itemBaseLayout->addLayout(costLayout);

    elementLayout->addWidget(consumable);
    elementLayout->addWidget(printer);

    printerLayout->addLayout(dayCostLayout);
    printerLayout->addWidget(wifi);
    printerLayout->addWidget(doubleside);
    printerLayout->addWidget(color);
    printerLayout->addWidget(used);
    printerLayout->addWidget(photo);

    typeLayout->addWidget(normale);
    typeLayout->addWidget(multifunction);

    itemBaseDetails->setLayout(itemBaseLayout);
    elementSelectionBox->setLayout(elementLayout);
    consumableDetails->setLayout(consumableLayout);
    typeSelectionBox->setLayout(typeLayout);
    printerDetails->setLayout(printerLayout);
    normalDetails->setLayout(normalLayout);
    multifunctionDetails->setLayout(multifunctionLayout);

    consumableDetails->setVisible(false);
    typeSelectionBox->setVisible(false);
    printerDetails->setVisible(false);
    normalDetails->setVisible(false);
    multifunctionDetails->setVisible(false);

    grid->addWidget(itemBaseDetails, 0,0);
    grid->addWidget(elementSelectionBox,0,1);
    grid->addWidget(typeSelectionBox,0,2);
    grid->addWidget(printerDetails,1,0);
    grid->addWidget(normalDetails,1,1);
    grid->addWidget(multifunctionDetails,1,1);
    grid->addWidget(consumableDetails,0,3);
    grid->addWidget(ok,2,1);
    grid->addWidget(no,2,0);

    itemBaseDetails->setFixedWidth(300);
    elementSelectionBox->setFixedWidth(300);
    consumableDetails->setFixedWidth(300);
    typeSelectionBox->setFixedWidth(300);
    printerDetails->setFixedWidth(300);
    normalDetails->setFixedWidth(300);
    multifunctionDetails->setFixedWidth(300);

    mainInsertionLayout->addLayout(grid);
    setLayout(mainInsertionLayout);
    setWindowTitle("Inserimento dati");

    connect(printer,SIGNAL(clicked()), this, SLOT(showPrinter()));
    connect(consumable,SIGNAL(clicked()), this, SLOT(showConsumable()));
    connect(normale,SIGNAL(clicked()), this, SLOT(showNormal()));
    connect(multifunction,SIGNAL(clicked()), this, SLOT(showMultifunction()));
    connect(ok, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(no, SIGNAL(clicked()), this, SLOT(dimiss()));
}

void InsertionWindow::showPrinter()
{
    itemBaseDetails->setVisible(false);
    elementSelectionBox->setVisible(false);
    consumableDetails->setVisible(false);
    typeSelectionBox->setVisible(false);
    printerDetails->setVisible(false);
    normalDetails->setVisible(false);
    multifunctionDetails->setVisible(false);

    itemBaseDetails->setVisible(true);
    elementSelectionBox->setVisible(true);
    typeSelectionBox->setVisible(true);

    if(printer->isChecked()){
        normale->setAutoExclusive(true);
        multifunction->setCheckable(true);

        normale->setEnabled(true);
        multifunction->setEnabled(true);
    }

    restore->setChecked(false);
    original->setChecked(false);
    size->setText("");
    colorName->setText("");
}

void InsertionWindow::showConsumable()
{
    itemBaseDetails->setVisible(false);
    elementSelectionBox->setVisible(false);
    consumableDetails->setVisible(false);
    typeSelectionBox->setVisible(false);
    printerDetails->setVisible(false);
    normalDetails->setVisible(false);
    multifunctionDetails->setVisible(false);

    itemBaseDetails->setVisible(true);
    elementSelectionBox->setVisible(true);
    consumableDetails->setVisible(true);

    if(consumable->isChecked()){
        normale->setAutoExclusive(false);
        multifunction->setCheckable(false);

        normale->setEnabled(false);
        multifunction->setEnabled(false);

        normale->setChecked(false);
        normale->setChecked(false);
    }

    scanner->setChecked(false);
    fax->setChecked(false);
    wifi->setChecked(false);
    doubleside->setChecked(false);
    color->setChecked(false);
    used->setChecked(false);
    photo->setChecked(false);
    plotter->setChecked(false);

    daycost->setText("");

    this->adjustSize();
}

void InsertionWindow::showNormal()
{
    itemBaseDetails->setVisible(false);
    elementSelectionBox->setVisible(false);
    consumableDetails->setVisible(false);
    typeSelectionBox->setVisible(false);
    printerDetails->setVisible(false);
    normalDetails->setVisible(false);
    multifunctionDetails->setVisible(false);

    itemBaseDetails->setVisible(true);
    elementSelectionBox->setVisible(true);
    normalDetails->setVisible(true);
    printerDetails->setVisible(true);
    typeSelectionBox->setVisible(true);

    scanner->setChecked(false);
    fax->setChecked(false);

    doubleside->setText("Fronte-retro (no in normale)");
    photo->setText("Fotografie (no in normale)");
    doubleside->setChecked(false);
    photo->setChecked(false);
    doubleside->setEnabled(false);
    photo->setEnabled(false);

}

void InsertionWindow::showMultifunction()
{
    itemBaseDetails->setVisible(false);
    elementSelectionBox->setVisible(false);
    consumableDetails->setVisible(false);
    typeSelectionBox->setVisible(false);
    printerDetails->setVisible(false);
    normalDetails->setVisible(false);
    multifunctionDetails->setVisible(false);

    itemBaseDetails->setVisible(true);
    elementSelectionBox->setVisible(true);
    multifunctionDetails->setVisible(true);
    printerDetails->setVisible(true);
    typeSelectionBox->setVisible(true);

    plotter->setChecked(false);

    doubleside->setText("Fronte-retro");
    photo->setText("Fotografie");
    doubleside->setChecked(false);
    photo->setChecked(false);
    doubleside->setEnabled(true);
    photo->setEnabled(true);

}

void InsertionWindow::confirm()
{
    QStringList *tmp = new QStringList();
    if(consumable->isChecked())
        tmp->push_back("c");
    else{
        if(printer->isChecked()){
            tmp->push_back("p");
            if(normale->isChecked())
                tmp->push_back("n");
            else {
                if(multifunction->isChecked())
                    tmp->push_back("m");
                else
                    tmp->push_back("null");
            }
        }
    }

    tmp->push_back(marca->text());
    tmp->push_back(modello->text());
    tmp->push_back(cost->text());
    if(consumable->isChecked()){
        tmp->push_back(size->text());
        tmp->push_back(restore->isChecked()? "1":"0");
        tmp->push_back(original->isChecked()? "1":"0");
        tmp->push_back(colorName->text());
    }
    else {
        tmp->push_back(daycost->text());
        tmp->push_back(wifi->isChecked()? "1":"0");
        tmp->push_back(doubleside->isChecked()? "1":"0");
        tmp->push_back(color->isChecked()? "1":"0");
        tmp->push_back(used->isChecked()? "1":"0");
        tmp->push_back(photo->isChecked()? "1":"0");
        if(normale->isChecked()){
            tmp->push_back(plotter->isChecked()? "1":"0");
        }
        else {
            if(multifunction->isChecked())
            tmp->push_back(scanner->isChecked()? "1":"0");
            tmp->push_back(fax->isChecked()? "1":"0");
        }
    }
    emit sendItemsDetails(*tmp);
}

void InsertionWindow::dimiss()
{
//    SLOT(reactiveMain());
    this->close();
}



