#ifndef ITEM_H
#define ITEM_H
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

using std::string;

class Item{
    private:
        string vendor, model;
        double cost;
    public:
        Item(string ="", string ="", double =0.0);
        Item(const Item&);
        virtual Item* clone() const =0;
        virtual ~Item() = default;

        virtual bool operator==(const Item&) const;
        virtual bool operator!=(const Item&) const;
        virtual bool operator<(const Item&) const;
        virtual bool operator>(const Item&) const;

        static bool caseUnsensitiveMatch(string, string);

        string getVendor() const;
        string getModel() const;
        double getCost() const;

        virtual QString getType() const =0;

        virtual std::string print() const;

        virtual void dataSerialize(QXmlStreamWriter&) const =0;
};

#endif // ITEM_H
