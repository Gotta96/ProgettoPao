#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          name(new QLineEdit("Nome cliente",this)),
                                          iva(new QLineEdit("P.IVA",this)),
                                          find(new QLineEdit(this)),
                                          quantity(new QSpinBox(this)),
                                          date(new QDateEdit(QDate::currentDate(),this)),
                                          elements(new QListView(this)),
                                          rent(new QListView(this)),
                                          buyed(new QListView(this)),
                                          details(new QLabel("----Dettagli----",this)),
                                          image(new QLabel("---IMG---",this)),
                                          totrent(new QLabel("0",this)),
                                          totbuyed(new QLabel("0",this)),
                                          tot(new QLabel("0",this)) {
    //creazione elementi base, seguo la procedura bottom up

    QWidget *mainWidget= new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QMenuBar *menu= new QMenuBar(this);
    QMenu *file = new QMenu("File",this);
    QMenu *modify = new QMenu("Modifica",this);
    QAction *load = new QAction("Carica", this);
    QAction *save = new QAction("Salva file", this);
    QAction *pdf = new QAction("PDF Export", this);
    QAction *exit = new QAction("Esci", this);
    QAction *addElementToList = new QAction("Aggiungi elemento", this);
    QAction *removeElementToList = new QAction("Rimuovi elemento", this);
    QAction *modifyElement = new QAction("Modifica elemento", this);
    QLabel *labname = new QLabel("Nome: ");                     //mettere parent
    QLabel *labiva = new QLabel("P.IVA: ");                     //mettere parent
    QLabel *labdate = new QLabel("Data: ");                     //mettere parent
    QLabel *labcatalog = new QLabel("Catalogo:");               //mettere parent
    QLabel *labfind = new QLabel("Cerca: ");                    //mettere parent
    QLabel *labrent = new QLabel("Noleggio:");                  //mettere parent
    QLabel *labbuyed = new QLabel("Compra:");                   //mettere parent
    QLabel *labquantity = new QLabel("Quantita': ");            //mettere parent
    QLabel *labtotrent = new QLabel("Totale noleggiato: ");     //mettere parent
    QLabel *labtotbuyed = new QLabel("Totale comprato: ");      //mettere parent
    QLabel *labtot = new QLabel("Totale: ");                    //mettere parent
    QPushButton *buttonrent = new QPushButton("Noleggia");      //mettere parent
    QPushButton *buttonbuy = new QPushButton("Compra");         //mettere parent
    //QPushButton *buttonfind = new QPushButton("Cerca");         //mettere parent      forse inutile causa aggiornamento dato da autocompletamento

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
    modify->addAction(addElementToList);
    modify->addAction(removeElementToList);
    modify->addAction(modifyElement);
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
    boxbuy->addWidget(labbuyed);
    boxbuy->addWidget(buyed);

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
    left->addLayout(findsection);

    //Layout di destra della vista di principale utilizzo

    right->addLayout(resumedetails);
    right->addLayout(twolists);
    right->addLayout(buttonsquantity);
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
}
