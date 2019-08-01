#include <iostream>
#include <QApplication>
//#include "View/mainwindow.h"
//#include "Model/Gerarchia/consumable.h"
//#include "Model/Gerarchia/item.h"
//#include "Model/Gerarchia/multifunction.h"
//#include "Model/Gerarchia/stampante.h"
//#include "Model/Gerarchia/normal.h"
//#include "Model/Template/deepptr.h"
//#include "Model/Template/container.h"
#include "controller.h"

using namespace std;

int main(int argc,char *argv[])
{
    /*Normal n;
    Normal* pn = new Normal("HP", "12DF5D", 300, 3, true, true, false, false);
    Multifunction mf;
    DeepPtr<Normal> dptrn(pn);
    Container<DeepPtr<Normal>> lista(dptrn);

    cout << dptrn->print() << endl;
    cout << mf.print() << endl;
    cout << endl << lista.Begin()->printDptr();*/
    QApplication a(argc,argv);
//    MainWindow w;
//    w.show();
    Controller c;
    return a.exec();

//    Container<DeepPtr<Item>> prova;
//    Consumable *c= new Consumable("canon", "456", 23, 50, true, false, "blue");
//    cout << endl <<c->print() << endl;
//    DeepPtr<Item> e;
//    e=c;
//    prova.pushInOrder(e);
//    auto it=prova.constBegin();
//    cout << endl <<(*it)->print() << endl;
}
