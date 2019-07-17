#ifndef MULTIFUNCTION_H
#define MULTIFUNCTION_H
#include "stampante.h"

class Multifunction : public Stampante{
private:
    bool scanner, fax;
public:
    Multifunction(string ="", string ="", double =0.0, double =0.0, bool =false,bool =false, bool =false, bool =false, bool =false, bool =false, bool =false);
    Multifunction(const Multifunction&);
    Multifunction* clone() const override;
    ~Multifunction() override;

    Multifunction& operator=(const Multifunction&) const;

    bool operator==(const Item&) const override;
    bool operator!=(const Item&) const override;

    bool haveScanner() const;
    bool haveFax() const;

    std::string print() const override;
};

#endif // MULTIFUNCTION_H
