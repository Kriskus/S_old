#ifndef CELLVISIBILITYGENERATOR_H
#define CELLVISIBILITYGENERATOR_H

#include <QVector>
#include <tuple>

class CellVisibilityGenerator
{
public:
    CellVisibilityGenerator();

    QVector<std::pair<int, int>> drawCellVisibility(int numberOfCell);

    std::pair<int, int> generateNumbers();

private:
    QVector<std::pair<int, int>> cellSettings_{};
};

#endif // CELLVISIBILITYGENERATOR_H
