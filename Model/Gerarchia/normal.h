#ifndef NORMAL_H
#define NORMAL_H
#include "stampante.h"


class Normal : public Stampante{
private:
    bool plotter;
public:
    Normal(string ="", string ="", double =0.0, double =0.0, bool =false, bool =false,bool =false, bool =false, bool =false, bool =false);
    Normal(const Normal&);
    virtual Normal* clone() const override;
    ~Normal() override;

    Normal& operator=(const Normal&) const;

    bool operator==(const Item&) const override;
    bool operator!=(const Item&) const override;

    bool isPlotter() const;
};

#endif // NORMAL_H
