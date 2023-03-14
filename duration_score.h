#ifndef DURATION_SCORE_H
#define DURATION_SCORE_H

#include <QDialog>
#include "play.h"
#include "game.h"
#include <QMessageBox>
#include <QFile>

namespace Ui {
class Duration_score;
}

class Duration_score : public QDialog
{
    Q_OBJECT

public:
    explicit Duration_score(QWidget *parent = nullptr);
    ~Duration_score();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Duration_score *ui;
};

#endif // DURATION_SCORE_H
