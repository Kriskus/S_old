#ifndef DIFFICULTYSETTINGS_H
#define DIFFICULTYSETTINGS_H

#include <QDialog>

namespace Ui {
class DifficultySettings;
}

class DifficultySettings : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultySettings(QWidget *parent = nullptr);
    ~DifficultySettings();

private:
    Ui::DifficultySettings *ui;

    void closeEvent(QCloseEvent* event);

private slots:
    void setDificultyLevel(int lvl);

signals:
    void closeWindow();
    void setDificulty(int);
};

#endif // DIFFICULTYSETTINGS_H
