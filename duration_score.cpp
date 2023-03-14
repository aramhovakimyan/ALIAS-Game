#include "duration_score.h"
#include "ui_duration_score.h"

Duration_score::Duration_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Duration_score)
{
    ui->setupUi(this);
}

Duration_score::~Duration_score()
{
    delete ui;
}

void Duration_score::on_pushButton_clicked()
{
    // take round duration and wining score and its in file
    int duration = ui->r_dur->text().toInt();
    int score = ui->w_score->text().toInt();
    if(duration > 0 && score > 0){
        QFile file("dur_score.txt");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << duration << "\n";
            out << score << "\n";
        }
        hide();
        Game window;
        window.setModal(true);
        window.exec();
    } else
        QMessageBox::information(this, "Round Duration & Win Score", " Please enter a number greater than 0! ");
}


void Duration_score::on_pushButton_2_clicked()
{
    hide();
    Play window;
    window.setModal(true);
    window.exec();
}

