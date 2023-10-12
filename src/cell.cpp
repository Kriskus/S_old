#include "cell.h"


Cell::Cell(int correctDigit, bool visible, int difficultyLvl)
    : correctDigit_(correctDigit)
    , difficultyLvl_(difficultyLvl)
{
    setFixedSize(41, 41);
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
    QString fColor = setFontColor(active);
    style_ = "QLabel{"
             "border: 2px solid grey;"
             "color: " + fColor + ";"
             "background-color: " + bColor + ";}";
    setStyleSheet(style_);
}

bool Cell::checkDigit()
{
    return text().toInt() != correctDigit_;
}

QString Cell::setFontColor(bool active)
{
    if(checkDigit() && difficultyLvl_ < 2) {
        return "red";
    } else {
        return "black";
    }
    if(!active) {
        return "silver";
    }
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(!readOnly_) {
        emit clicked(this);
    }
}
