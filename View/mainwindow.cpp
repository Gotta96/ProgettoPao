#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          name(new QLineEdit("Nome cliente",this)),
                                          iva(new QLineEdit("P.IVA",this)),
                                          find(new QLineEdit(this)),
                                          quantity(new QSpinBox(this)),
                                          date(new QDateEdit(QDate::currentDate(),this)),
                                          elements(new SmartListView(this)),
                                          rent(new SmartListView(this)),
                                          buyed(new SmartListView(this)),
                                          details(new QLabel("----Dettagli----",this)),
                                          image(new QLabel("---IMG---",this)),
                                          totrent(new QLabel("0",this)),
                                          totbuyed(new QLabel("0",this)),
                                          tot(new QLabel("0",this)){

    //Imposto che in ogni SamrtListView posso selezionare un solo elemento
    elements->setSelectionMode(QAbstractItemView::SingleSelection);
    rent->setSelectionMode(QAbstractItemView::SingleSelection);
    buyed->setSelectionMode(QAbstractItemView::SingleSelection);

    //creazione elementi base, seguo la procedura bottom up

    QWidget *mainWidget= new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QMenuBar *menu= new QMenuBar(this);
    QMenu *file = new QMenu("File",this);
    QMenu *modify = new QMenu("Modifica",this);
    QAction *modifyCatalog = new QAction("Modifica elemento catalogo",this);
    QAction *addToCatalog = new QAction("Aggiungi elemento catalogo",this);
    QAction *load = new QAction("Carica", this);
    QAction *save = new QAction("Salva file", this);
    QAction *pdf = new QAction("PDF Export", this);
    QAction *exit = new QAction("Esci", this);
//    QAction *addElementToList = new QAction("Aggiungi elemento", this);
//    QAction *removeElementToList = new QAction("Rimuovi elemento", this);
//    QAction *modifyElement = new QAction("Modifica elemento", this);
    QLabel *labname = new QLabel("Nome: ");
    QLabel *labiva = new QLabel("P.IVA: ");
    QLabel *labdate = new QLabel("Data: ");
    QLabel *labcatalog = new QLabel("Catalogo:");
    QLabel *labfind = new QLabel("Cerca: ");
    QLabel *labrent = new QLabel("Noleggio:");
    QLabel *labbuyed = new QLabel("Compra:");
    QLabel *labquantity = new QLabel("Quantita': ");
    QLabel *labtotrent = new QLabel("Totale noleggiato: ");
    QLabel *labtotbuyed = new QLabel("Totale comprato: ");
    QLabel *labtot = new QLabel("Totale: ");
    QPushButton *buttonrent = new QPushButton("Noleggia");
    QPushButton *buttonbuy = new QPushButton("Compra");
    QPushButton *buttonRemoveRent = new QPushButton("Rimuovi noleggio");
    QPushButton *buttonRemoveBuyed = new QPushButton("Rimuovi compera");
    //QPushButton *buttonfind = new QPushButton("Cerca");       //forse inutile causa aggiornamento dato da autocompletamento

    //creazione dei layout per gli elementi

    QVBoxLayout *boxresume= new QVBoxLayout();
    QVBoxLayout *boxparzialilabel = new QVBoxLayout();
    QVBoxLayout *boxparzialivalues = new QVBoxLayout();
    QHBoxLayout *boxparziali = new QHBoxLayout();
    QHBoxLayout *boxtotale = new QHBoxLayout();

    QVBoxLayout *buttonsquantity = new QVBoxLayout();
    QHBoxLayout *writequantity = new QHBoxLayout();
    QHBoxLayout *twobuttons = new QHBoxLayout();

    QHBoxLayout *twolists = new QHBoxLayout();
    QVBoxLayout *boxrent = new QVBoxLayout();
    QVBoxLayout *boxbuy = new QVBoxLayout();

    QHBoxLayout *resumedetails = new QHBoxLayout();

    QVBoxLayout *findsection = new QVBoxLayout();

    QVBoxLayout *resumeelements = new QVBoxLayout();

    QVBoxLayout *left = new QVBoxLayout();
    QVBoxLayout *right = new QVBoxLayout();

    QHBoxLayout *principal = new QHBoxLayout();

    QHBoxLayout *clientdetails = new QHBoxLayout();

    QVBoxLayout *layoutfinal = new QVBoxLayout();

    file->addAction(load);
    file->addAction(save);
    file->addAction(pdf);
    file->addAction(exit);
    menu->addMenu(file);
    modify->addAction(modifyCatalog);
    modify->addAction(addToCatalog);
    menu->addMenu(modify);

    //Layout di resume dei vari totali

    boxresume->addLayout(boxparziali);
    boxresume->addLayout(boxtotale);

    boxparziali->addLayout(boxparzialilabel);
    boxparziali->addLayout(boxparzialivalues);

    boxparzialilabel->addWidget(labtotrent);
    boxparzialilabel->addWidget(labtotbuyed);

    boxparzialivalues->addWidget(totrent);
    boxparzialivalues->addWidget(totbuyed);

    boxtotale->addWidget(labtot);
    boxtotale->addWidget(tot);

    //Layout con i due bottoni decisionali per noleggiare o comprare e di inserimento di quantità

    buttonsquantity->addLayout(writequantity);
    buttonsquantity->addLayout(twobuttons);

    writequantity->addWidget(labquantity);
    writequantity->addWidget(quantity);

    twobuttons->addWidget(buttonrent);
    twobuttons->addWidget(buttonbuy);

    //Layout con le due liste noleggiato e coprato

    twolists->addLayout(boxrent);
    twolists->addLayout(boxbuy);
    boxrent->addWidget(labrent);
    boxrent->addWidget(rent);
    boxrent->addWidget(buttonRemoveRent);
    boxbuy->addWidget(labbuyed);
    boxbuy->addWidget(buyed);
    boxbuy->addWidget(buttonRemoveBuyed);

    //Layout di resume dei vari dettagli dell'elemento selezionato

    resumedetails->addWidget(details);
    resumedetails->addWidget(image);

    //Layout della sezione di ricerca

    findsection->addWidget(labfind);
    findsection->addWidget(find);

    //Layout della parte contenente la lista degli elemnti

    resumeelements->addWidget(labcatalog);
    resumeelements->addWidget(elements);

    //Layout di sinistra della vista di principale utilizzo

    left->addLayout(resumeelements);
    left->addLayout(buttonsquantity);
    left->addLayout(findsection);

    //Layout di destra della vista di principale utilizzo

    right->addLayout(resumedetails);
    right->addLayout(twolists);
    right->addLayout(boxresume);

    //Layout vista principale

    principal->addLayout(left);
    principal->addLayout(right);

    //Layout contenente i dettagli del cliente

    clientdetails->addWidget(labname);
    clientdetails->addWidget(name);
    clientdetails->addWidget(labiva);
    clientdetails->addWidget(iva);
    clientdetails->addWidget(labdate);
    clientdetails->addWidget(date);

    //Layout finale

    layoutfinal->addLayout(clientdetails);
    layoutfinal->addLayout(principal);

    //Layout totale
    mainLayout->addWidget(menu);
    mainLayout->addLayout(layoutfinal);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

//    mainWidget->setFixedWidth(800);
//    mainWidget->setFixedHeight(600);

//    connect(modifyCatalog, SIGNAL(triggered()), SIGNAL(openModifyCatalogWindow()));
    connect(load, SIGNAL(triggered()), SIGNAL(openLoadWindow()));
    connect(save, SIGNAL(triggered()), SIGNAL(openSaveWindow()));
    connect(pdf, SIGNAL(triggered()), SIGNAL(openSavePDFWindow()));
    connect(exit, SIGNAL(triggered()), this, SLOT(closeAll()));
    connect(modifyCatalog, SIGNAL(triggered()),this, SLOT(openModify()));
    connect(addToCatalog, SIGNAL(triggered()),this, SLOT(openAdd()));
    connect(find, SIGNAL(textChanged(const QString &)),this, SIGNAL(updateSearch(const QString &)));
    connect(buttonrent, SIGNAL(clicked()), this, SLOT(generateRent()));
    connect(buttonbuy, SIGNAL(clicked()), this, SLOT(generateBuyed()));
    connect(buttonRemoveRent, SIGNAL(clicked()), this, SLOT(destroyRent()));
    connect(buttonRemoveBuyed, SIGNAL(clicked()), this, SLOT(destroyBuyed()));
    connect(elements, SIGNAL(itemSelectionChange()), this, SLOT(catalogSelected()));
    connect(rent, SIGNAL(clicked()), this, SLOT(rentSelected()));
    connect(buyed, SIGNAL(clicked()), this, SLOT(buyedSelected()));
//    connect(insWindow, SIGNAL(re_active(bool)), this, SLOT(reactiveMain()));


}

void MainWindow::updateDetails(QString info, QString ){
    details->setText(info);
    //finire di impostare l'immagine
}

void MainWindow::updateTotals(QStringList prezzi){
    totrent->setText(prezzi[0]);
    totbuyed->setText(prezzi[1]);
    tot->setText(prezzi[0]+prezzi[1]);
}

void MainWindow::addToCatalog(QStringList e){
//    QString prova;
//    prova=e.first();
//    elements->;
}

void MainWindow::generateRent()
{
    emit clickedNoleggia(elements->getIndex(),quantity->value());
}

void MainWindow::generateBuyed()
{
    emit clickedCompra(elements->getIndex(),quantity->value());
}

void MainWindow::destroyRent()
{
    emit clickedRemoveRent(rent->getIndex());
}

void MainWindow::destroyBuyed()
{
    emit clickedRemoveBuyed(buyed->getIndex());
}

void MainWindow::catalogSelected()
{
    rent->unSelectIndex();
    buyed->unSelectIndex();
}

void MainWindow::rentSelected()
{
    elements->unSelectIndex();
    buyed->unSelectIndex();
}

void MainWindow::buySelected()
{
    elements->unSelectIndex();
    rent->unSelectIndex();
}

void MainWindow::openModify()
{

}

void MainWindow::openAdd()
{
    insWindow = new InsertionWindow(this);
    insWindow->show();
    //this->setEnabled(false);
}

//void MainWindow::reactiveMain()
//{
//    if(!insWindow)
//        this->setEnabled(true);
//}

void MainWindow::closeAll()
{
    this->close();
}
