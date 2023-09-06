#include "cell.h"


Cell::Cell(int number)
    : number_(number)
{

}

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(this);
}
