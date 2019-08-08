#include "multifunction.h"

Multifunction::Multifunction(string v, string m, double cos, double dc, bool w, bool ds, bool col,bool use, bool ph, bool scan, bool fa): Stampante (v,m,cos,dc,w,ds,col,use,ph), scanner(scan), fax(fa){}

Multifunction::Multifunction(const Multifunction& m): Stampante(m), scanner(m.haveScanner()), fax(m.haveFax()){}

Multifunction *Multifunction::clone() const{
    return new Multifunction(*this);
}

Multifunction::~Multifunction(){}

bool Multifunction::operator==(const Item& i) const{
    return dynamic_cast<const Multifunction*>(&i) && Stampante::operator==(i) && scanner==(static_cast<const Multifunction*>(&i))->haveScanner() && fax==(static_cast<const Multifunction*>(&i))->haveFax();
}

bool Multifunction::operator!=(const Item& i) const{
    return dynamic_cast<const Multifunction*>(&i) && Stampante::operator!=(i) && scanner!=(static_cast<const Multifunction*>(&i))->haveScanner() && fax!=(static_cast<const Multifunction*>(&i))->haveFax();
}

bool Multifunction::haveScanner() const{
    return scanner;
}

bool Multifunction::haveFax() const{
    return fax;
}

QString Multifunction::getType() const
{
    return "m";
}

std::string Multifunction::print() const{
    return Stampante::print() + "\n"+  "Scanner: " + (scanner ? "Si" : "No") + " Fax: " + (fax ? "Si" : "No");
}

Multifunction *Multifunction::unserialize(QXmlStreamReader &rd)
{
    QString v = "--Empty--", m = "--Empty--";
    double cos =0, dc=0;
    bool ds=false,w=false, col=false, use=false, ph=false ,scan=false, fa=false;

    if(rd.readNextStartElement() && rd.name() == "vendor")
        v = rd.readElementText();

    if(rd.readNextStartElement() && rd.name() == "model")
        m = rd.readElementText();

    if(rd.readNextStartElement() && rd.name() == "cost")
        cos = rd.readElementText().toDouble();

    if(rd.readNextStartElement() && rd.name() == "day_cost")
        dc = rd.readElementText().toDouble();

    if(rd.readNextStartElement() && rd.name() == "doubleside")
        ds = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "wifi")
        w = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "color")
        col = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "used")
        use = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "photo")
        ph = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "scanner")
        scan = rd.readElementText() == "1"? true:false;

    if(rd.readNextStartElement() && rd.name() == "fax")
        fa = rd.readElementText() == "1"? true:false;

    rd.skipCurrentElement();
    return new Multifunction(v.toStdString(),m.toStdString(),cos,dc,w,ds,col,use,ph,scan,fa);
}

void Multifunction::dataSerialize(QXmlStreamWriter & wr) const
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

    wr.writeStartElement("day_cost");
    wr.writeCharacters(QString::number(getDaycost()));
    wr.writeEndElement();

    wr.writeStartElement("doubleside");
    wr.writeCharacters(QString::fromStdString(isDoubleSide()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("wifi");
    wr.writeCharacters(QString::fromStdString(isWiFi()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("color");
    wr.writeCharacters(QString::fromStdString(isColor()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("used");
    wr.writeCharacters(QString::fromStdString(isUsed()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("photo");
    wr.writeCharacters(QString::fromStdString(isPhoto()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("scanner");
    wr.writeCharacters(QString::fromStdString(haveScanner()? "1" : "0"));
    wr.writeEndElement();

    wr.writeStartElement("fax");
    wr.writeCharacters(QString::fromStdString(haveFax()? "1" : "0"));
    wr.writeEndElement();

    wr.writeEndElement();

    if(wr.hasError())
        throw "Errore in scrittura (multifunction)";
}

