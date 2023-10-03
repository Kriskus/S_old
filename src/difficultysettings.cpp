#include "difficultysettings.h"
#include "ui_difficultysettings.h"

DifficultySettings::DifficultySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DifficultySettings)
{
    ui->setupUi(this);

    setWindowFlag(Qt::WindowStaysOnTopHint);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &DifficultySettings::closeWindow);

    for (int el = 0; el < ui->buttonLayout->count(); ++el) {
        QPushButton *button = qobject_cast<QPushButton*>(ui->buttonLayout->itemAt(el)->widget());
        if (button) {
            connect(button, &QPushButton::clicked, [this, button, el]() {
                setDificultyLevel(el);
            });
        }
    }
}

DifficultySettings::~DifficultySettings()
{
    delete ui;
}

void DifficultySettings::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
}

void DifficultySettings::setDificultyLevel(int lvl)
{
    switch (lvl) {
    case 0:
        emit setDificulty(40);
        break;
    case 1:
        emit setDificulty(35);
        break;
    case 2:
        emit setDificulty(30);
        break;
    case 3:
        emit setDificulty(25);
        break;
    case 4:
        emit setDificulty(20);
        break;
    case 5:
        emit setDificulty(13);
        break;
    default:
        break;
    }
}
