#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include "View/insertionwindow.h"

class ModifyWindow : public InsertionWindow
{
    Q_OBJECT
private:
    unsigned int ind;
public:
    explicit ModifyWindow(QWidget *parent = nullptr);
    explicit ModifyWindow(QStringList,unsigned int, QWidget *parent = nullptr);
public slots:
    void confirm();
signals:
    void replaceItem(unsigned int, QStringList);
};

#endif // MODIFYWINDOW_H
