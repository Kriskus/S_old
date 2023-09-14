#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <QWidget>
#include <QGridLayout>

#include "cell.h"

class BoardGame : public QWidget
{
    Q_OBJECT
public:
    BoardGame(int row = 0, int column = 0);

private:
    int row_{0};
    int column_{0};
    QGridLayout* layout_; // Układ dla BoardGame

public slots:
    void addCell(Cell* cell);

};

#endif // BOARDGAME_H
