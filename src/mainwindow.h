#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cell.h"
#include "sudokugenerator.h"

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
    QVector<QVector<int>> board_{};

private slots:
    void newGame();
    void generateGameBoard();

    void setCellToEdit(Cell *cellToEdit);
};
#endif // MAINWINDOW_H
