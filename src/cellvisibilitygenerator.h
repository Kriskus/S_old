#ifndef CELLVISIBILITYGENERATOR_H
#define CELLVISIBILITYGENERATOR_H

#include <QVector>
#include <set>
#include <random>
#include <chrono>

class CellVisibilityGenerator
{
public:
    CellVisibilityGenerator();

    QVector<std::pair<int, int>> drawCellVisibility(int numberOfCell);


private:
    QVector<std::pair<int, int>> cellSettings_{};
    std::mt19937 generator_;
    std::pair<int, int> generateNumbers();
};

#endif // CELLVISIBILITYGENERATOR_H
