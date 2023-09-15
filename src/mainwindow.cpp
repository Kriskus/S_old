#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

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
    int buttonRow = 0;
    int buttonColumn = 0;
    for (int element = 0; element < 10; ++element) {
        QPushButton* button;
        if(element < 9) {
            button = new QPushButton(QString::number(element+1));
            button->setObjectName(QString::number(element+1));
        } else {
            button = new QPushButton("C");
            button->setObjectName("0");
        }
        button->setMinimumSize(60,60);
        button->setMaximumSize(60,60);
        if(buttonColumn == 5) {
            buttonColumn = 0;
            buttonRow++;
        }
        ui->buttonLayout->addWidget(button, buttonRow, buttonColumn++);
        connect(button, &QPushButton::clicked, [this, button]() {
                cell_->writeDigit(button->objectName());
            });
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

