#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sudoku_ = new Sudoku;

    newGame();

    generateGameBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    sudokuBoard_ = sudoku_->generateBoard();
    createLayout();
}

void MainWindow::generateGameBoard()
{
        for (int row = 0; row < 9; ++row) {
            for (int column = 0; column < 9; ++column) {
                setBoardLayout(row, column);

                Cell* cell = new Cell(sudokuBoard_[row][column]);
                connect(cell, &Cell::clicked, this, &MainWindow::setCellToEdit);

                currentBoardLayout_->addCell(cell);
            }
        }
}

void MainWindow::createLayout()
{
    int i = 0;
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            BoardGame* boardLayout = new BoardGame(row, column);
            ui->gameLayout->addWidget(boardLayout, row, column);
            boardLayoutList_.push_back(boardLayout);
        }
    }
}

void MainWindow::setBoardLayout(int row, int column)
{
    row -= row % 3;
    column -= column % 3;

    for(const auto& board: boardLayoutList_) {
        if(board->objectName().contains(QString::number(row) + QString::number(column))) {
            currentBoardLayout_ = board;
            break;
        }
    }
}

void MainWindow::setCellToEdit(Cell* cellToEdit)
{
    cell_ = cellToEdit;
}

