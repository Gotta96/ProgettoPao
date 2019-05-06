#ifndef ITEM_H
#define ITEM_H
#include <string>

using std::string;

class Item{
    private:
        string vendor, model;
        double cost, daycost;
    public:
        Item(string ="", string ="", double =0.0, double =0.0);
        Item(const Item&);
        virtual Item* clone() const =0;
        virtual ~Item() = default;

        virtual bool operator==(const Item&) const;
        virtual bool operator!=(const Item&) const;

        Item& operator=(const Item&) const;       //??
        string getVendor() const;
        string getModel() const;
        double getCost() const;
        double getDayCost() const;

        virtual std::string print() const;
};

#endif // ITEM_H
