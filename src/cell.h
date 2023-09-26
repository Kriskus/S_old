#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
    Q_OBJECT
public:
    Cell(int correctDigit = 0);

private:
    int correctDigit_{0};
    QString style_{};

public slots:
    void writeDigit(const QString &digit);
    void setStyleSheet(bool active);

private slots:
    bool checkDigit(int digit);

signals:
    void clicked(Cell* cell);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CELL_H
