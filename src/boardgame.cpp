#include "boardgame.h"

#include <QPushButton>

static const int kMaxRows = 3;
static const int kMaxColumns = 3;

BoardGame::BoardGame(int row, int column)
{
    setObjectName(QString::number(row*3) + QString::number(column*3));
    layout_ = new QGridLayout(this);
    setLayout(layout_);
}

BoardGame::~BoardGame()
{
    delete layout_;
}

void BoardGame::addCell(Cell *cell)
{
    if (row_ < kMaxRows && column_ < kMaxColumns) {
        layout_->addWidget(cell, row_, column_++);
        if (column_ == kMaxColumns) {
            row_++;
            column_ = 0;
        }
    }
}

void BoardGame::clearContents() {
    QLayoutItem* item;
    while ((item = layout_->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        if (widget) {
            delete widget;
        }
        delete item;
    }
}
