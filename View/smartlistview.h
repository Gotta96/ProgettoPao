#ifndef SMARTLISTVIEW_H
#define SMARTLISTVIEW_H

#include <QWidget>
#include <QListView>

class SmartListView : public QListView
{
    Q_OBJECT
public:
    SmartListView(QWidget * =nullptr);

    unsigned int getIndex() const;

    void unSelectIndex() const;
};

#endif // SMARTLISTVIEW_H
