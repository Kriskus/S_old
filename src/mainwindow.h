#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>

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
    Sudoku* sudoku_;
    Cell* cell_;
    BoardGame* currentBoardLayout_{};
    QVector<QVector<int>> sudokuBoard_{};
    QVector<BoardGame*> boardLayoutList_{};
    QVector<std::pair<int, int>> cellVisible_{};

    bool visibility_{false};
    int cellSideSize_{0};
    int mistakes_{0};

private slots:
    void newGame();
    void addButtons();
    void generateGameBoard();
    void clearBoard();

    void createLayout();
    void setCellSize();

    void setBoardLayout(int row, int column);

    void setCellToEdit(Cell *cellToEdit);
};
#endif // MAINWINDOW_H
