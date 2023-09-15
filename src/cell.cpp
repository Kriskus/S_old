#include "cell.h"


Cell::Cell(int correctDigit)
    : correctDigit_(correctDigit)
{
    setReadOnly(true);
    setMaximumHeight(30);
    setMaximumWidth(30);

    setPlainText(QString::number(correctDigit));
}

void Cell::writeDigit(const QString& digit)
{
    QTextCharFormat format;
    if(digit == "0") {
        format.setForeground(Qt::white);
    } else {
        if(checkDigit(digit.toInt())) {
            format.setForeground(Qt::black);
        } else {
            format.setForeground(Qt::red);
        }
    }
    selectAll();
    textCursor().setCharFormat(format);
    setPlainText(digit);
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
