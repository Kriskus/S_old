#include "boardgame.h"

#include <QPushButton>

BoardGame::BoardGame(int row, int column)
{
    setObjectName(QString::number(row*3) + QString::number(column*3));
    layout_ = new QGridLayout(this);
    setLayout(layout_);
}

void BoardGame::addCell(Cell *cell)
{
    if(column_ == 3) {
        row_++;
        column_ = 0;
    }
    if(row_ < 3) {
        layout_->addWidget(cell, row_, column_++);
    }
}
