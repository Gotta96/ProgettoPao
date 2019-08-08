#include "consumable.h"

Consumable::Consumable(string v, string m , double cos, unsigned int s, bool rest, bool origin, string col): Item(v,m,cos), size(s), restore(rest), original(origin), color(col){}

Consumable::Consumable(const Consumable& c): Item(c), size(c.getSize()), restore(c.isRestored()), original(c.isOriginal()), color(c.getColorName()){}

Consumable *Consumable::clone() const{
    return new Consumable(*this);
}

Consumable::~Consumable(){};

bool Consumable::operator==(const Item& i) const{
    return dynamic_cast<const Consumable*>(&i) && Item::operator==(i) && size==(static_cast<const Consumable*>(&i))->getSize() && restore==(static_cast<const Consumable*>(&i))->isRestored() && original==static_cast<const Consumable*>(&i)->isOriginal();
}

bool Consumable::operator!=(const Item& i) const{
    return dynamic_cast<const Consumable*>(&i) && Item::operator!=(i) && size!=(static_cast<const Consumable*>(&i))->getSize() && restore!=(static_cast<const Consumable*>(&i))->isRestored() && original!=static_cast<const Consumable*>(&i)->isOriginal();
}

unsigned int Consumable::getSize() const{
    return size;
}

bool Consumable::isRestored() const{
    return restore;
}

bool Consumable::isOriginal() const{
    return original;
}

std::string Consumable::getColorName() const{
    return color;
}

QString Consumable::getType() const
{
    return "c";
}

std::string Consumable::print() const
{
    return Item::print() + "\n" + "Dimensione: " + std::to_string(size) + " Colore: " + getColorName() + "\n" + "Rigenerata: " + (restore? "si":"no") + " Originale: " + (original? "si":"no");
}

Consumable *Consumable::unserialize(QXmlStreamReader &rd)
{
    QString v = "--Empty--", m = "--Empty--", col="--Empty--";
    double cos =0;
    unsigned int s=0;
    bool rest=false, origin=false;

    if(rd.readNextStartElement() && rd.name() == "vendor")
        v = rd.readElementText();

    if(rd.readNextStartElement() && rd.name() == "model")
        m = rd.readElementText();

    if(rd.readNextStartElement() && rd.name() == "cost")
        cos = rd.readElementText().toDouble();

    if(rd.readNextStartElement() && rd.name() == "size")
        s = rd.readElementText().toUInt();

    if(rd.readNextStartElement() && rd.name() == "restored")
        rest = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "original")
        origin = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "color_name")
        col = rd.readElementText();

    rd.skipCurrentElement();
    return new Consumable(v.toStdString(),m.toStdString(),cos,s,rest,origin,col.toStdString());
}

void Consumable::dataSerialize(QXmlStreamWriter & wr) const
{
    wr.writeStartElement("item");
    wr.writeAttribute("type", getType());

    wr.writeStartElement("vendor");
    wr.writeCharacters(QString::fromStdString(getVendor()));
    wr.writeEndElement();

    wr.writeStartElement("model");
    wr.writeCharacters(QString::fromStdString(getModel()));
    wr.writeEndElement();

    wr.writeStartElement("cost");
    wr.writeCharacters(QString::number(getCost()));
    wr.writeEndElement();

    wr.writeStartElement("size");
    wr.writeCharacters(QString::number(getSize()));
    wr.writeEndElement();

    wr.writeStartElement("restored");
    wr.writeCharacters(QString::fromStdString(isRestored()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("original");
    wr.writeCharacters(QString::fromStdString(isOriginal()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("color_name");
    wr.writeCharacters(QString::fromStdString(getColorName()));
    wr.writeEndElement();

    wr.writeEndElement();

    if(wr.hasError())
        throw "Errore in scrittura (consumable)";
}
