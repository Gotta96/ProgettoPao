#ifndef SMARTLISTVIEW_H
#define SMARTLISTVIEW_H

#include <QListWidget>

class SmartListView : public QListWidget
{
    Q_OBJECT
public:
    SmartListView(QWidget * =nullptr);

    unsigned int getIndex() const;

    bool isSomeoneSeleceted() const;

    void unSelectIndex() const;
};

#endif // SMARTLISTVIEW_H
