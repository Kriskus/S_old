#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QTimer>

#include "cell.h"
#include "sudokugenerator.h"
#include "boardgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer* timer_{};
    Sudoku* sudoku_{};
    Cell* cell_{};
    BoardGame* currentBoardLayout_{};
    QVector<QVector<int>> sudokuBoard_{};
    QVector<BoardGame*> boardLayoutList_{};
    QVector<std::pair<int, int>> cellVisible_{};

    bool visibility_{false};
    int cellSideSize_{0};
    int mistakes_{0};
    int totalTimeInSeconds_{0};

private slots:
    void createLayout();
    void setCurrentBoardLayout(int row, int column);

    void setButtons();
    void setCellSize();

    void generateGameBoard();
    void checkVisibility(int row, int column);
    void addCellToGameLayout(int row, int column);

    void chooseLvl();
    void newGame(int dificultyLvl);

    void clearBoard();


    void setCellToEdit(Cell *cellToEdit);
    void startTimer();
};
#endif // MAINWINDOW_H
