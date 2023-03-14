#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QGridLayout>
#include <QMainWindow>
#include <unordered_map>
#include <vector>
#include <QMessageBox>
#include <QVBoxLayout>
#include "play.h"

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void onTimerTick();

    void check_for_extra();

    void on_pushButton_clicked();

    void on_add_score_clicked();

    void on_ok_clicked();

private:
    Ui::Game *ui;
    QTimer *m_timer;
    QTimer *m_extra_timer;
    QLabel *m_countdownLabel;
    QWidget* score_window;
    std::vector<QString> teams;
    std::unordered_map<QString, int> team_score;
    int ts_counter;
    int curr_count;
    bool is_not_extra;

    void filling_words();
};

#endif // GAME_H
