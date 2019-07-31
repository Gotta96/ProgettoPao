#include "smartlistview.h"

SmartListView::SmartListView(QWidget *parent):QListWidget (parent){}

unsigned int SmartListView::getIndex() const
{
    return this->selectedIndexes()[0].row();
}

void SmartListView::unSelectIndex() const
{
    this->selectedIndexes().clear();
}
