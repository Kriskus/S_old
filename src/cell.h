#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
    Q_OBJECT
public:
    Cell(int correctDigit = 0, bool visible = false, int difficultyLvl = 0);
    ~Cell();

private:
    int correctDigit_{0};
    int difficultyLvl_{0};
    QString style_{};
    bool readOnly_{false};

public slots:
    void writeDigit(const QString &digit);
    void setStyle(bool active);

private slots:
    bool checkDigit();
    QString setFontColor(bool active);

signals:
    void clicked(Cell* cell);
    void mistake();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CELL_H
