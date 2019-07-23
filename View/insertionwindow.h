#ifndef INSERTIONWINDOW_H
#define INSERTIONWINDOW_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QBoxLayout>

class InsertionWindow : public QDialog
{
    Q_OBJECT

private:
    QLineEdit *marca, *modello;
    QCheckBox dettagli;
    QRadioButton item, tipo;

public:
    explicit InsertionWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // INSERTIONWINDOW_H
