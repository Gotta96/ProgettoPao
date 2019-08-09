#ifndef XMLIO_H
#define XMLIO_H

#include <QString>
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Model/Template/container.h"
#include "Model/Template/deepptr.h"
#include "Gerarchia/consumable.h"
#include "Gerarchia/multifunction.h"
#include "Gerarchia/normal.h"

class XmlIO
{
public:
    static bool readItems(const QString, Container<DeepPtr<Item>>& catalogo);
    static bool writeItems(const Container<DeepPtr<Item>>&, const QString);
};

#endif // XMLIO_H
