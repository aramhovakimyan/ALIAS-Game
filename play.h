#ifndef PLAY_H
#define PLAY_H

#include <QDialog>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "teams_name.h"
#include <QAbstractButton>
#include <QMessageBox>

namespace Ui {
class Play;
}

class Play : public QDialog
{
    Q_OBJECT

public:
    explicit Play(QWidget *parent = nullptr);
    ~Play();

private slots:
    void on_continue_2_clicked();

    void on_cancel_clicked();

private:
    Ui::Play *ui;
};

#endif // PLAY_H
