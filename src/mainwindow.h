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

private slots:
    void newGame();
    void generateGameBoard();

    void createLayout();

    void setBoardLayout(int row, int column);

    void setCellToEdit(Cell *cellToEdit);
};
#endif // MAINWINDOW_H
