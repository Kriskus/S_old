#include "sudokugenerator.h"

#include <random>

Sudoku::Sudoku()
{
    board_ = QVector<QVector<int>>(9, QVector<int>(9, 0));
}

Sudoku::~Sudoku()
{

}

QVector<QVector<int> > Sudoku::generateBoard()
{
    for(row_ = 0; row_ < 9; row_++) {
        QVector<int> numbers = shuffleNumbers({1,2,3,4,5,6,7,8,9});
        for(column_ = 0; column_ < 9; column_++) {
            for(int element = 0; element < 9; element++) {
                if(!checkRow(row_, numbers[element]) && !checkColumn(column_, numbers[element]) && !checkSquare(row_, column_, numbers[element])) {
                    board_[row_][column_] = numbers[element];
                    numbers.remove(element, 1);
                    break;
                }
            }
        }
        checkGeneratedRow(row_);
    }

    return board_;
}

bool Sudoku::checkRow(int row, int number)
{
    for(int column = 0; column < 9; column++) {
        if(board_[row][column] == number) {
            return true;
        }
    }
    return false;
}

bool Sudoku::checkColumn(int column, int number)
{
    for(int row = 0; row < 9; row++) {
        if(board_[row][column] == number) {
            return true;
        }
    }
    return false;
}

bool Sudoku::checkSquare(int row, int column, int number)
{
    row = row - row % 3;
    column = column - column % 3;
    int maxRow = row + 3;
    int maxColumn = column + 3;

    for(row; row < maxRow; row++) {
        for(column; column < maxColumn; column++) {
            if(board_[row][column] == number) {
                return true;
            }
        }
        column = maxColumn - 3;
    }
    return false;
}

QVector<int> Sudoku::shuffleNumbers(QVector<int> line)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(line.begin(), line.end(), gen);
    return line;
}

void Sudoku::checkGeneratedRow(int row)
{
    for(int column = 0; column < 9; column++) {
        if(board_[row][column] == 0) {
            resetRow(row);
            lineFailure_++;
            if(lineFailure_ == 10) {
                resetBoard();
                row_ = -1;
                lineFailure_ = 0;
            } else {
                row_--;
            }
        }
        if(column == 9) {
            lineFailure_ = 0;
        }
    }
}

void Sudoku::resetRow(int row)
{
    board_[row] = {0,0,0,0,0,0,0,0,0};
}

void Sudoku::resetBoard()
{
    board_ = QVector<QVector<int>>(9, QVector<int>(9, 0));
}
