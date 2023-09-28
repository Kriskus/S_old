#include "cell.h"


Cell::Cell(int correctDigit, bool visible, int sideSize)
    : correctDigit_(correctDigit)
{
    setFixedSize(sideSize, sideSize);
    setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    QFont font;
    font.setPointSize(20);
    setFont(font);
    setStyleSheet("QLabel{border: 1px solid grey;"
                          "color: white;}");
    if(visible) {
        setText(QString::number(correctDigit));
        readOnly_ = true;
    }
}

Cell::~Cell()
{}

void Cell::writeDigit(const QString& digit)
{
    setText(digit);
    setStyle(true);
}

void Cell::setStyle(bool active)
{
    QString bColor = active ? "silver" : "none";
    QString fColor = checkDigit(active);
    style_ = "QLabel{"
             "border: 1px solid grey;"
             "color: " + fColor + ";"
             "background-color: " + bColor + ";}";
    setStyleSheet(style_);
}

QString Cell::checkDigit(bool active)
{
    if(text() != "" && text().toInt() != correctDigit_) {
        emit mistake();
        return "red";
    } else if(active) {
        return "black";
    } else {
        return "white";
    }
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(!readOnly_) {
        emit clicked(this);
    }
}
