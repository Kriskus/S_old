#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <QVector>


class Sudoku
{
public:
    Sudoku();
    ~Sudoku();

    QVector<QVector<int>> board_{};

    QVector<QVector<int>> generateBoard();

private:
    int lineFailure_{0};
    int row_{0};
    int column_{0};

    bool checkRow(int row, int number);
    bool checkColumn(int column, int number);
    bool checkSquare(int row, int column, int number);

    QVector<int> shuffleNumbers(QVector<int> line);
    void checkGeneratedRow(int row);

    void resetRow(int row);
    void resetBoard();

};

#endif // SUDOKUGENERATOR_H


