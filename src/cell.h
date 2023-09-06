#ifndef CELL_H
#define CELL_H

#include <QPlainTextEdit>

class Cell : public QPlainTextEdit
{
public:
    Cell(int number = 0);

private:
    int number_{0};

signals:
    void clicked(Cell* cell);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CELL_H
