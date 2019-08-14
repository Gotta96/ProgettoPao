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
                                          totrent(new QLabel("0€",this)),
                                          totbuyed(new QLabel("0€",this)){

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
    QAction *addToCatalog = new QAction("Aggiungi elemento catalogo",this);
    QAction *modifyCatalog = new QAction("Modifica elemento catalogo",this);
    QAction *removeIntoCatalog = new QAction("Rimuovi elemento catalogo",this);
    QAction *load = new QAction("Carica file", this);
    QAction *save = new QAction("Salva file", this);
    QAction *pdf = new QAction("PDF Export", this);
    QAction *exit = new QAction("Esci", this);
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
    QLabel *labLogo = new QLabel();
    QPushButton *buttonrent = new QPushButton("Noleggia");
    QPushButton *buttonbuy = new QPushButton("Compra");
    QPushButton *buttonRemoveRent = new QPushButton("Rimuovi noleggio");
    QPushButton *buttonRemoveBuyed = new QPushButton("Rimuovi compera");

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

    QPixmap imgLogo(QString(":/images/definitivo.jpg"));
    labLogo->setPixmap(imgLogo);

    file->addAction(load);
    file->addAction(save);
    file->addAction(pdf);
    file->addAction(exit);
    menu->addMenu(file);
    modify->addAction(addToCatalog);
    modify->addAction(modifyCatalog);
    modify->addAction(removeIntoCatalog);
    menu->addMenu(modify);

    //Layout di resume dei vari totali

    boxresume->addLayout(boxparziali);
    boxresume->addLayout(boxtotale);

    boxparziali->addLayout(boxparzialilabel);
    boxparziali->addLayout(boxparzialivalues);
    rent->unSelectIndex();
    buyed->unSelectIndex();
    boxparzialilabel->addWidget(labtotrent);
    boxparzialilabel->addWidget(labtotbuyed);

    boxparzialivalues->addWidget(totrent);
    boxparzialivalues->addWidget(totbuyed);

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
    resumedetails->addWidget(labLogo);

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

    details->setMinimumHeight(300);
    details->setMinimumWidth(300);
    labLogo->setMinimumHeight(300);

    connect(load, SIGNAL(triggered()), SIGNAL(openLoadWindow()));
    connect(save, SIGNAL(triggered()), SIGNAL(openSaveWindow()));
    connect(pdf, SIGNAL(triggered()), SIGNAL(openSavePDFWindow()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(addToCatalog, SIGNAL(triggered()),this, SIGNAL(openAddToCatalogWindow()));
    connect(modifyCatalog, SIGNAL(triggered()),this, SIGNAL(requestToOpenModify()));
    connect(removeIntoCatalog, SIGNAL(triggered()),this, SLOT(removeRequest()));
    connect(find, SIGNAL(textChanged(const QString &)),this, SIGNAL(updateSearch()));
    connect(buttonrent, SIGNAL(clicked()), this, SLOT(generateRent()));
    connect(buttonbuy, SIGNAL(clicked()), this, SLOT(generateBuyed()));
    connect(buttonRemoveRent, SIGNAL(clicked()), this, SLOT(destroyRent()));
    connect(buttonRemoveBuyed, SIGNAL(clicked()), this, SLOT(destroyBuyed()));
    connect(elements, SIGNAL(currentRowChanged(int)), this, SLOT(catalogSelected(int)));
    connect(rent, SIGNAL(currentRowChanged(int)), this, SLOT(rentSelected(int)));
    connect(buyed, SIGNAL(currentRowChanged(int)), this, SLOT(buyedSelected(int)));

}

void MainWindow::displayCatalog(const QStringList intestazioni)
{
    elements->reset();
    elements->clear();
    auto it = intestazioni.begin();
    while(it!=intestazioni.end()){
        elements->addItem(*it);
        ++it;
    }
}

void MainWindow::displayRent(const QStringList intestazioni)
{
    rent->reset();
    rent->clear();
    auto it = intestazioni.begin();
    while(it!=intestazioni.end()){
        rent->addItem(*it);
        ++it;
    }
}

void MainWindow::displayBuyed(const QStringList intestazioni)
{
    buyed->reset();
    buyed->clear();
    auto it = intestazioni.begin();
    while(it!=intestazioni.end()){
        buyed->addItem(*it);
        ++it;
    }
}

void MainWindow::displayInputError()
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error","Input Incompleto");
    messageBox.setFixedSize(500,200);
}

void MainWindow::displayNotSelection()
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error","Oggetto non selezionato");
    messageBox.setFixedSize(500,200);
}

void MainWindow::displayDetails(const QString d)
{
    details->clear();
    details->setText(d);
}

void MainWindow::displayTotals(double noleggiato, double comprato)
{
    totrent->clear();
    totbuyed->clear();
    totrent->setText(QString::number(noleggiato)+"€");
    totbuyed->setText(QString::number(comprato)+"€");
}

void MainWindow::displayErrorForConsumableRent()
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error","Impossibile noleggiare un consumabile");
    messageBox.setFixedSize(500,200);
}

void MainWindow::displayOpenError()
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error","Impossibile aprire il file specificato");
    messageBox.setFixedSize(500,200);
}

void MainWindow::displayIvaError()
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error","Partita iva inserita non contiene solo numeri");
    messageBox.setFixedSize(500,200);
}

void MainWindow::displayTheElementExist()
{
    QMessageBox messageBox;
    messageBox.critical(this,"Error","Esiste già un elemento con questi dettagli\n\ncontrolla la lista");
    messageBox.setFixedSize(500,200);
}

void MainWindow::displayLoad(QString err)
{
    QMessageBox messageBox;
    messageBox.warning(this,"Conferma",err);
    messageBox.setFixedSize(500,200);
}

void MainWindow::displaySave(QString err)
{
    QMessageBox messageBox;
    messageBox.warning(this,"Conferma",err);
    messageBox.setFixedSize(500,200);
}

bool MainWindow::isSelected() const
{
    return elements->isSomeoneSeleceted();
}

unsigned int MainWindow::getCatalogSelected() const
{
    return elements->getIndex();
}

const QString MainWindow::getResearchWord() const
{
    return find->text();
}

QString MainWindow::getClientName() const
{
    return name->text();
}

QString MainWindow::getClientPiva() const
{
    QRegExp regexInt("^\\d+$");
    if(iva->text().contains(regexInt))
        return iva->text();
    else
        return "error";
}

void MainWindow::updateDetails(QString info){
    details->setText(info);
}

void MainWindow::generateRent()
{
    if(elements->isSomeoneSeleceted()){
        emit clickedNoleggia(elements->getIndex(),(uint)quantity->value());
        quantity->setValue(0);
    }
    else
        displayNotSelection();
}

void MainWindow::generateBuyed()
{
    if(elements->isSomeoneSeleceted()){
        emit clickedCompra(elements->getIndex(),(uint)quantity->value());
        quantity->setValue(0);
    }
    else
        displayNotSelection();
}

void MainWindow::destroyRent()
{
    if(rent->isSomeoneSeleceted())
        emit clickedRemoveRent(rent->getIndex());
    else
        displayNotSelection();
}

void MainWindow::destroyBuyed()
{
    if(buyed->isSomeoneSeleceted())
        emit clickedRemoveBuyed(buyed->getIndex());
    else
        displayNotSelection();
}

void MainWindow::catalogSelected(int index)
{
    rent->reset();
    buyed->reset();
    emit requestDetailsCatalog((uint)index);
}

void MainWindow::rentSelected(int index)
{
    elements->reset();
    buyed->reset();
    emit requestDetailsRent((uint)index);
}

void MainWindow::buyedSelected(int index)
{
    elements->reset();
    rent->reset();
    emit requestDetailsBuyed((uint)index);
}

void MainWindow::removeRequest()
{
    if(elements->isSomeoneSeleceted())
        emit requestRemoveIntoCatalog(elements->getIndex());
    else
        displayNotSelection();
}
