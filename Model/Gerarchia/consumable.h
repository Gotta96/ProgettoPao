#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"

class Consumable : public Item{
private:
    unsigned int size;
    bool restore, original;
    string color;
public:
    Consumable(string ="", string ="", double =0.0, unsigned int =0, bool =false, bool =true, string ="");
    Consumable(const Consumable&);
    Consumable* clone() const override;
    ~Consumable() override;

    Consumable& operator=(const Consumable&) const;

    bool operator==(const Item&) const override;
    bool operator!=(const Item&) const override;

    unsigned int getSize() const;
    bool isRestored() const;
    bool isOriginal() const;
    string getColorName() const;
};

#endif // CONSUMABLE_H
