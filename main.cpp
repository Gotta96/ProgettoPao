#include <iostream>
#include <QApplication>
#include "controller.h"

using namespace std;

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    Controller c;
    return a.exec();
}
