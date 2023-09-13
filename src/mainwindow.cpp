#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sudoku_ = new Sudoku;

    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    board_ = sudoku_->generateBoard();
    generateGameBoard();
}

void MainWindow::generateGameBoard()
{
    for (int row = 0; row < 9; ++row) {
        for (int column = 0; column < 9; ++column) {
            Cell* cell = new Cell(board_[row][column]);
            connect(cell, &Cell::clicked, this, &MainWindow::setCellToEdit);
            ui->boardLayout->addWidget(cell, row, column);
        }
    }
}

void MainWindow::setCellToEdit(Cell* cellToEdit)
{
    cell_ = cellToEdit;
}

