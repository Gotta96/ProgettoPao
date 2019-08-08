#include "xmlio.h"

Container<DeepPtr<Item> > XmlIO::readItems(const QString filename){

    //Creo container vuoto
    Container<DeepPtr<Item>> catalogo;

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox box(QMessageBox::Warning, "Errore apertura file", "Impossibile leggere file", QMessageBox::Ok);
        box.exec();
        throw 1;
//        return catalogo;
    }

    //Leggo file XML
    QXmlStreamReader reader(&file);
    QString type;
    if(reader.readNextStartElement() && reader.name() == "catalog"){
        while(reader.readNextStartElement()){
            type=reader.attributes().value("type").toString();
            try {
                if(type=="c")
                    catalogo.pushInOrder(Consumable::unserialize(reader));
                if(type=="n")
                    catalogo.pushInOrder(Normal::unserialize(reader));
                if(type=="m")
                    catalogo.pushInOrder(Multifunction::unserialize(reader));
            } catch (std::string s) {
                QMessageBox box(QMessageBox::Warning, "Errore caricamento file", QString("Impossibile caricare il file, errore in lettura""<br><u>Causa:</u> %1").arg(QString::fromStdString(s)), QMessageBox::Ok);
                box.exec();
                throw 1;
            }
        }
    }
    else {
        QMessageBox box(QMessageBox::Warning,"Errore di caricamento", "contenuto non riconosciuto", QMessageBox::Ok);
        box.exec();
        throw 1;
    }

        file.close();
        return catalogo;
}

bool XmlIO::writeItems(const Container<DeepPtr<Item> > & catalogo, const QString filename)
{
    QSaveFile file(filename);

    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeComment("Catalogo oggetti");

    writer.writeStartElement("catalog");

    try {
        auto cit=catalogo.constBegin();
        for(int k=0; k<catalogo.size(); k++){
            (*cit)->dataSerialize(writer);
            ++cit;
        }
    } catch (std::string s) {
        return false;
    }

    writer.writeEndElement();
    writer.writeEndDocument();

    file.commit();
    return true;
}

