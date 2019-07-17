#include <iostream>
#include <QApplication>
#include "View/mainwindow.h"
#include "Model/Gerarchia/consumable.h"
#include "Model/Gerarchia/item.h"
#include "Model/Gerarchia/multifunction.h"
#include "Model/Gerarchia/stampante.h"
#include "Model/Gerarchia/normal.h"
#include "Model/Template/deepptr.h"
#include "Model/Template/container.h"

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
    MainWindow w;
    w.show();
    return a.exec();
}
