#ifndef TEAMS_NAME_H
#define TEAMS_NAME_H

#include <QDialog>
#include <QLineEdit>
#include <vector>
#include "duration_score.h"
#include "play.h"
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class Teams_name;
}

class Teams_name : public QDialog
{
    Q_OBJECT

public:
    explicit Teams_name(QWidget *parent = nullptr);
    ~Teams_name();

private slots:
    void on_continue_3_clicked();
    void on_cancel_clicked();

private:
    Ui::Teams_name *ui;
    int numTeams;
    std::vector<QLineEdit*> teamLineEdit;
};

#endif // TEAMS_NAME_H
