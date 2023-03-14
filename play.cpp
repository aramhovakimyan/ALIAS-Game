#include "play.h"
#include "ui_play.h"

Play::Play(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Play)
{
    ui->setupUi(this);
}

Play::~Play()
{
    delete ui;
}

void Play::on_continue_2_clicked()
{
    // take teams count and save it in file
    int numTeams = ui->team_count->text().toInt();
    if(numTeams <= 1){
        QMessageBox::information(this, "Teams Count", "This number of teams is forbidden! It must be 2 or more");
    }
    else {
        QFile file("utils.txt");
        if (file.open(QIODevice::WriteOnly)){
            QTextStream out(&file); out << numTeams << "\n";
            file.close();
        }
        hide();
        Teams_name window;
        window.setModal(true);
        window.exec();
    }
}


void Play::on_cancel_clicked()
{
    hide();
}

