#include "xmlio.h"

bool XmlIO::readItems(const QString filename, Container<DeepPtr<Item> > &catalogo){

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        return false;
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
                return false;
            }
        }
    }
    else {
        return false;
    }

        file.close();
        return true;
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

