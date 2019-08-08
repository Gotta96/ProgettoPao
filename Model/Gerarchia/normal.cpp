#include "normal.h"

Normal::Normal(string v, string m, double cos, double dc, bool w, bool col,bool use, bool pl): Stampante(v,m,cos,dc,w,false,col,use,false), plotter(pl){}

Normal::Normal(const Normal& n): Stampante(n), plotter(n.plotter){}

Normal *Normal::clone() const{
    return new Normal(*this);
}

Normal::~Normal(){}

bool Normal::operator==(const Item& i) const{
    return dynamic_cast<const Normal*>(&i) && Stampante::operator==(i) && plotter==(static_cast<const Normal*>(&i))->isPlotter();
}

bool Normal::operator!=(const Item& i) const{
    return dynamic_cast<const Normal*>(&i) && Stampante::operator!=(i) && plotter!=(static_cast<const Normal*>(&i))->isPlotter();
}

bool Normal::isPlotter() const{
    return plotter;
}

QString Normal::getType() const
{
    return "n";
}

std::string Normal::print() const{
    return Stampante::print() + "\n" + "Plotter: " + (plotter ? "Si" : "No");
}

Normal *Normal::unserialize(QXmlStreamReader &rd)
{
    QString v = "--Empty--", m = "--Empty--";
    double cos =0, dc=0;
    bool ds=false,w=false, col=false, use=false, ph=false ,pl=false;

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

    if(rd.readNextStartElement() && rd.name() == "plotter")
        pl = rd.readElementText() == "1"? true:false;

    rd.skipCurrentElement();
    return new Normal(v.toStdString(),m.toStdString(),cos,dc,w,col,use,pl);
}

void Normal::dataSerialize(QXmlStreamWriter & wr) const
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

    wr.writeStartElement("plotter");
    wr.writeCharacters(QString::fromStdString(isPlotter()? "1" : "0"));
    wr.writeEndElement();

    wr.writeEndElement();

    if(wr.hasError())
        throw "Errore in scrittura (normal)";
}
