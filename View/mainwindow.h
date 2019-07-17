#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListView>
#include <QLabel>
#include <QDateEdit>
#include <QMenuBar>
#include <QSpinBox>
#include <QPushButton>
#include <QBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineEdit *name, *iva, *find;
    QSpinBox *quantity;
    QDateEdit *date;
    QListView *elements, *rent, *buyed;
    QLabel *details, *image, *totrent, *totbuyed, *tot;
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWINDOW_H
