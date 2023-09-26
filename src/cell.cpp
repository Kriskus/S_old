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
    setStyle(true);
}

void Cell::setStyle(bool active)
{
    QString bColor{};
    if(active) {
        bColor = "silver";
    } else {
        bColor = "none";
    }
    QString fColor = checkDigit();
    style_ = "QLabel{"
            "border: 1px solid black;"
            "color: " + fColor + ";"
            "background-color: " + bColor + ";}";
    setStyleSheet(style_);
}

QString Cell::checkDigit()
{
    if(text() != "" && text().toInt() != correctDigit_) {
        return "red";
    }else {
        return "black";
    }
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(this);
}
