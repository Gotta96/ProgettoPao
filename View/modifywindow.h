#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGroupBox>
#include <QWidget>
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
    explicit ModifyWindow(QStringList,unsigned int, QWidget *parent = nullptr);
public slots:
    void confirm() override;
signals:
    void replaceItem(unsigned int, QStringList);
};

#endif // MODIFYWINDOW_H
