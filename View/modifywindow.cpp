#include "modifywindow.h"

ModifyWindow::ModifyWindow(QWidget *parent):InsertionWindow(parent){}

ModifyWindow::ModifyWindow(QStringList e, unsigned int index, QWidget *parent) : InsertionWindow(parent),ind(index){

    //setto i valori passati dalla QStringList

    if(e.at(0)=="c"){
        //setto le group box che si devono visualizzare
        consumableDetails->setVisible(true);
        typeSelectionBox->setVisible(false);
        printerDetails->setVisible(false);
        normalDetails->setVisible(false);
        multifunctionDetails->setVisible(false);

        //setto i valori degli elementi
        consumable->setChecked(true);
        marca->setText(e.at(1));
        modello->setText(e.at(2));
        cost->setText(e.at(3));
        size->setText(e.at(4));
        restore->setChecked(e.at(5)=="1"? true : false);
        original->setChecked(e.at(6)=="1"? true : false);
        colorName->setText(e.at(7));
    }
    else {
        if(e.at(0)=="p"){
            //setto le group box che si devono visualizzare
            consumableDetails->setVisible(false);
            typeSelectionBox->setVisible(true);
            printerDetails->setVisible(true);

            //setto i valori degli elementi
            printer->setChecked(true);
            marca->setText(e.at(2));
            modello->setText(e.at(3));
            cost->setText(e.at(4));
            daycost->setText(e.at(5));
            wifi->setChecked(e.at(6)=="1"? true : false);
            doubleside->setChecked(e.at(7)=="1"? true : false);
            color->setChecked(e.at(8)=="1"? true : false);
            used->setChecked(e.at(9)=="1"? true : false);
            photo->setChecked(e.at(10)=="1"? true : false);
            if(e.at(1)=="n"){
                //setto le group box che si devono visualizzare
                normalDetails->setVisible(true);
                multifunctionDetails->setVisible(false);

                //setto i valori degli elementi
                normale->setChecked(true);
                plotter->setChecked(e.at(11)=="1"? true : false);
            }
            if(e.at(1)=="m"){
                //setto le group box che si devono visualizzare
                normalDetails->setVisible(false);
                multifunctionDetails->setVisible(true);

                //setto i valori degli elementi
                multifunction->setChecked(true);
                scanner->setChecked(e.at(11)=="1"? true : false);
                fax->setChecked(e.at(12)=="1"? true : false);
            }
            else {
                //setto tutto come se non fosse stato inserito niente
                consumableDetails->setVisible(false);
                typeSelectionBox->setVisible(false);
                printerDetails->setVisible(false);
                normalDetails->setVisible(false);
                multifunctionDetails->setVisible(false);
            }
        }
    }
}

void ModifyWindow::confirm()
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
    emit replaceItem(ind,*tmp);
    this->close();
}
