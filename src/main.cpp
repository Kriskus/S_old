#include "mainwindow.h"

#include <QApplication>

#include "sudokugenerator.h"

#include <iostream>

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    //    return a.exec();

    Sudoku* s = new Sudoku;
    QVector<QVector<int>> board = s->generateBoard();

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            std::cout << QString::number(board[i][j]).toStdString() + " ";
        }
        std::cout << "\n";
    }
    delete s;
    return 0;
}
