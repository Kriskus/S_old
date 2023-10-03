#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>
#include <tuple>
#include <QScreen>

#include "cellvisibilitygenerator.h"
#include "difficultysettings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sudoku_(new Sudoku)
    , cell_(nullptr)
{
    ui->setupUi(this);

    connect(ui->pushButtonExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->pushButtonNew, &QPushButton::clicked, this, &MainWindow::chooseLvl);

    setMinimumWidth(515);
    setMaximumWidth(515);
    setMinimumHeight(669);
    setMinimumHeight(669);

    //ui->labelTimeCnt->setText(QString::number(this->width()) + "|" + QString::number(this->height()));
    setCellSize();
    setButtons();
    //chooseLvl();
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
        for (int column = 1; column < 4; ++column) {
            QPushButton *button = qobject_cast<QPushButton*>(ui->buttonLayout->itemAtPosition(row, column)->widget());
            if (button) {
                connect(button, &QPushButton::clicked, [this, button]() {
                    if(cell_ != nullptr) {
                        cell_->writeDigit(button->objectName().split("_").last());
                    }
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
    //QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    //cellSideSize_ = screenGeometry.width() * 0.9 / 9;
    cellSideSize_ = 41;
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

void MainWindow::chooseLvl()
{
    DifficultySettings* selectLvl = new DifficultySettings();
    connect(selectLvl, &DifficultySettings::closeWindow, selectLvl, &DifficultySettings::close);
    connect(selectLvl, &DifficultySettings::closeWindow, this, &MainWindow::close);
    connect(selectLvl, &DifficultySettings::setDificulty, this, &MainWindow::newGame);
    connect(selectLvl, &DifficultySettings::setDificulty, selectLvl, &DifficultySettings::close);
    selectLvl->show();
}

void MainWindow::newGame(int dificultyLvl)
{
    clearBoard();
    mistakes_ = 0;
    ui->labelMistakeCnt->setText(QString::number(mistakes_));
    sudokuBoard_ = sudoku_->generateBoard();
    CellVisibilityGenerator* cellV = new CellVisibilityGenerator();
    cellVisible_ = cellV->drawCellVisibility(dificultyLvl);
    createLayout();
    generateGameBoard();
    delete cellV;
    startTimer();
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

void MainWindow::startTimer()
{
    timer_ = new QTimer();

    QObject::connect(timer_, &QTimer::timeout, [&]() {
        int minutes = totalTimeInSeconds_ / 60;
        int seconds = totalTimeInSeconds_ % 60;
        QString timeText = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        ui->labelTimeCnt->setText(timeText);
        totalTimeInSeconds_++;
    });

    timer_->start(1000);
}

