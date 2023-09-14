#include "cell.h"


Cell::Cell(int correctDigit)
    : correctDigit_(correctDigit)
{
    setReadOnly(true);
    setMaximumHeight(30);
    setMaximumWidth(30);

    setPlainText(QString::number(correctDigit));
}

void Cell::writeDigit(int digit)
{
    QTextCharFormat format;
    if(checkDigit(digit)) {
        format.setForeground(Qt::black);
    } else {
        format.setForeground(Qt::red);
    }
    selectAll();
    textCursor().setCharFormat(format);
    setPlainText(QString::number(digit));
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
