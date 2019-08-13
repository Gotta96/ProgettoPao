#ifndef STAMPANTE_H
#define STAMPANTE_H

#include "item.h"


class Stampante : public Item{
private:
    double daycost;
    bool wifi, doubleside, color, used, photo;
public:
    Stampante(string ="", string ="", double =0.0, double =0.0,bool =false, bool =false, bool =false, bool =false, bool =false);
    Stampante(const Stampante&);
    Stampante* clone() const override =0;
    ~Stampante() override;

    bool operator==(const Item&) const override;
    bool operator!=(const Item&) const override;

    bool isWiFi() const;
    bool isDoubleSide() const;
    bool isColor() const;
    bool isUsed() const;
    bool isPhoto() const;
    double getDaycost() const;

    QString getType() const override =0;

    std::string print() const override;

    virtual void dataSerialize(QXmlStreamWriter&) const override =0;
};

#endif // STAMPANTE_H
