#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>
#include <tuple>
#include <QScreen>

#include "cellvisibilitygenerator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sudoku_(new Sudoku)
    , cell_(nullptr)
{
    ui->setupUi(this);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->pushButtonNew, &QPushButton::clicked, this, &MainWindow::newGame);

    setCellSize();
    setButtons();
    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createLayout()
{
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            BoardGame* boardLayout = new BoardGame(row, column);
            ui->gameLayout->addWidget(boardLayout, row, column);
            boardLayoutList_.push_back(boardLayout);
        }
    }
}

void MainWindow::setCurrentBoardLayout(int row, int column)
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

void MainWindow::setButtons()
{
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            QPushButton *button = qobject_cast<QPushButton*>(ui->buttonLayout->itemAtPosition(row, column)->widget());
            if (button) {
                connect(button, &QPushButton::clicked, [this, button]() {
                    cell_->writeDigit(button->objectName().split("_").last());
                });
            }
        }
    }
    connect(ui->pushButton_C, &QPushButton::clicked, [this]() {
        cell_->writeDigit("");
    });
}

void MainWindow::setCellSize()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    cellSideSize_ = screenGeometry.width() * 0.9 / 9;
}

void MainWindow::generateGameBoard()
{
    for (int row = 0; row < 9; ++row) {
        for (int column = 0; column < 9; ++column) {
            setCurrentBoardLayout(row, column);
            checkVisibility(row, column);

            addCellToGameLayout(row, column);

            visibility_ = false;
        }
    }
}

void MainWindow::checkVisibility(int row, int column)
{
    for (const auto& visible: cellVisible_) {
        if(row == visible.first && column == visible.second) {
            visibility_ = true;
            break;
        }
    }
}

void MainWindow::addCellToGameLayout(int row, int column)
{
    Cell* cell = new Cell(sudokuBoard_[row][column], visibility_, cellSideSize_);
    connect(cell, &Cell::clicked, this, &MainWindow::setCellToEdit);
    connect(cell, &Cell::mistake, [this]() {
        ui->labelMistakeCnt->setText(QString::number(++mistakes_));
    });

    currentBoardLayout_->addCell(cell);
}

void MainWindow::newGame()
{
    clearBoard();
    mistakes_ = 0;
    sudokuBoard_ = sudoku_->generateBoard();
    CellVisibilityGenerator* cellV = new CellVisibilityGenerator();
    cellVisible_ = cellV->drawCellVisibility(25);
    createLayout();
    generateGameBoard();
    delete cellV;
}

void MainWindow::clearBoard()
{
    for (BoardGame* boardLayout : boardLayoutList_) {
        boardLayout->clearContents();
        delete boardLayout;
    }
    boardLayoutList_.clear();
}

void MainWindow::setCellToEdit(Cell* cellToEdit)
{
    if(cell_!=nullptr) {
        cell_->setStyle(false);
    }
    cell_ = cellToEdit;
    cell_->setStyle(true);
}

