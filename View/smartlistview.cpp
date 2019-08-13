#include "smartlistview.h"

SmartListView::SmartListView(QWidget *parent):QListWidget (parent){}

unsigned int SmartListView::getIndex() const
{
    return (uint)this->selectedIndexes()[0].row();
}

bool SmartListView::isSomeoneSeleceted() const
{
    return !this->selectedIndexes().empty();
}

void SmartListView::unSelectIndex() const
{
    this->selectedIndexes().clear();
}
