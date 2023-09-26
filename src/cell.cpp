#include "cell.h"


Cell::Cell(int correctDigit)
    : correctDigit_(correctDigit)
{
    setMaximumHeight(30);
    setMaximumWidth(30);
    setAlignment(Qt::AlignCenter);
    setAlignment(Qt::AlignHCenter);
    setStyleSheet("QLabel{border: 1px solid black}");
    setText(QString::number(correctDigit));
}

void Cell::writeDigit(const QString& digit)
{
    setText(digit);
    if(checkDigit(digit.toInt())) {
        setStyleSheet("QLabel{color: black;}");
    } else {
        setStyleSheet("QLabel{color: red;}");
    }
}

void Cell::setStyleSheet(bool active)
{

}

bool Cell::checkDigit(int digit)
{
    return digit == correctDigit_;
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(this);
}
