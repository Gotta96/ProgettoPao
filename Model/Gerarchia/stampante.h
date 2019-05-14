#ifndef STAMPANTE_H
#define STAMPANTE_H

#include "item.h"


class Stampante : public Item{
private:
    bool wifi, doubleside, color, used, photo;
public:
    Stampante(string ="", string ="", double =0.0, double =0.0,bool =false, bool =false, bool =false, bool =false, bool =false);
    Stampante(const Stampante&);
    Stampante* clone() const override =0;
    ~Stampante() override;

    Stampante& operator=(const Stampante&) const;       //??

    bool operator==(const Item&) const override;
    bool operator!=(const Item&) const override;

    bool isWiFi() const;
    bool isDoubleSide() const;
    bool isColor() const;
    bool isUsed() const;
    bool isPhoto() const;

    std::string print() const override;
};

#endif // STAMPANTE_H
