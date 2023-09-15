#ifndef CELL_H
#define CELL_H

#include <QPlainTextEdit>

class Cell : public QPlainTextEdit
{
    Q_OBJECT
public:
    Cell(int correctDigit = 0);

private:
    int correctDigit_{0};

public slots:
    void writeDigit(const QString &digit);

private slots:
    bool checkDigit(int digit);

signals:
    void clicked(Cell* cell);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CELL_H
