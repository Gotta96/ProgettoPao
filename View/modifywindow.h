#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include "View/insertionwindow.h"

class ModifyWindow : public InsertionWindow
{
    Q_OBJECT
private:
    unsigned int ind;
public:
    explicit ModifyWindow(QWidget *parent = nullptr);

    void loadDataForEdit(QStringList, unsigned int);
public slots:
    void confirm() override;
signals:
    void replaceItem(unsigned int, QStringList);
};

#endif // MODIFYWINDOW_H
