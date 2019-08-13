#include "modifywindow.h"

ModifyWindow::ModifyWindow(QWidget *parent):InsertionWindow(parent){}

void ModifyWindow::loadDataForEdit(QStringList e, unsigned int i){
    ind=i;
    //setto i valori passati dalla QStringList

    QString dot= "\\.";
    QRegExp findDot(dot);
    if(e.at(0)=="c"){
        //setto le group box che si devono visualizzare
        consumableDetails->setVisible(true);
        typeSelectionBox->setVisible(false);
        printerDetails->setVisible(false);
        normalDetails->setVisible(false);
        multifunctionDetails->setVisible(false);

        this->adjustSize();

        //setto i valori degli elementi
        consumable->setChecked(true);
        marca->setText(e.at(1));
        modello->setText(e.at(2));
        if(e.at(3).contains(findDot))
            cost->setText(e.at(3));
        else
            cost->setText(e.at(3)+".0");
        size->setText(e.at(4));
        restore->setChecked(e.at(5)=="true"? true : false);
        original->setChecked(e.at(6)=="true"? true : false);
        colorName->setText(e.at(7));
    }
    else {
        if(e.at(0)=="p"){
            //setto le group box che si devono visualizzare
            consumableDetails->setVisible(false);
            typeSelectionBox->setVisible(true);
            printerDetails->setVisible(true);

            this->adjustSize();

            //setto i valori degli elementi
            printer->setChecked(true);
            marca->setText(e.at(2));
            modello->setText(e.at(3));
            if(e.at(4).contains(findDot))
                cost->setText(e.at(4));
            else
                cost->setText(e.at(4)+".0");
            if(e.at(5).contains(findDot))
                daycost->setText(e.at(5));
            else
                daycost->setText(e.at(5)+".0");
            wifi->setChecked(e.at(6)=="true"? true : false);
            doubleside->setChecked(e.at(7)=="true"? true : false);
            color->setChecked(e.at(8)=="true"? true : false);
            used->setChecked(e.at(9)=="true"? true : false);
            photo->setChecked(e.at(10)=="true"? true : false);
            if(e.at(1)=="n"){
                //setto le group box che si devono visualizzare
                multifunctionDetails->setVisible(false);
                normalDetails->setVisible(true);

                this->adjustSize();

                //setto i valori degli elementi
                normale->setChecked(true);
                plotter->setChecked(e.at(11)=="true"? true : false);
                doubleside->setText("Fronte-retro (no in normale)");
                photo->setText("Fotografie (no in normale)");
                doubleside->setChecked(false);
                photo->setChecked(false);
                doubleside->setEnabled(false);
                photo->setEnabled(false);
                scanner->setChecked(false);
                fax->setChecked(false);
            }
            if(e.at(1)=="m"){
                //setto le group box che si devono visualizzare
                normalDetails->setVisible(false);
                multifunctionDetails->setVisible(true);

                this->adjustSize();

                //setto i valori degli elementi
                multifunction->setChecked(true);
                scanner->setChecked(e.at(11)=="true"? true : false);
                fax->setChecked(e.at(12)=="true"? true : false);
                doubleside->setText("Fronte-retro");
                photo->setText("Fotografie");
                doubleside->setEnabled(true);
                photo->setEnabled(true);
            }
        }
        else {
            //setto tutto come se non fosse stato inserito niente
            consumableDetails->setVisible(false);
            typeSelectionBox->setVisible(false);
            printerDetails->setVisible(false);
            normalDetails->setVisible(false);
            multifunctionDetails->setVisible(false);

            this->adjustSize();
        }
    }
}

void ModifyWindow::confirm()
{
    QRegExp regexNumber("^(?:0|[1-9][0-9]*)\\.[0-9]+$");
    QRegExp regexInt("^\\d+$");
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
        tmp->push_back(restore->isChecked()? "true":"false");
        tmp->push_back(original->isChecked()? "true":"false");
        tmp->push_back(colorName->text());
    }
    else {
        tmp->push_back(daycost->text());
        tmp->push_back(wifi->isChecked()? "true":"false");
        tmp->push_back(doubleside->isChecked()? "true":"false");
        tmp->push_back(color->isChecked()? "true":"false");
        tmp->push_back(used->isChecked()? "true":"false");
        tmp->push_back(photo->isChecked()? "true":"false");
        if(normale->isChecked()){
            tmp->push_back(plotter->isChecked()? "true":"false");
        }
        else {
            if(multifunction->isChecked())
            tmp->push_back(scanner->isChecked()? "true":"false");
            tmp->push_back(fax->isChecked()? "true":"false");
        }
    }
    if(cost->text().contains(regexNumber)){
        if(consumable->isChecked() && size->text().contains(regexInt)){
            emit replaceItem(ind,*tmp);
            this->close();
        }
        else {
            if(printer->isChecked() && daycost->text().contains(regexNumber)){
                emit replaceItem(ind,*tmp);
                this->close();
            }
            else
                emit inputError();
        }
    }
    else
        emit inputError();
}
