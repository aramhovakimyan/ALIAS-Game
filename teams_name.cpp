#include "teams_name.h"
#include "ui_teams_name.h"

Teams_name::Teams_name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teams_name)
{
    ui->setupUi(this);

    // take teams count from file
    QFile file("utils.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream out(&file); out >> numTeams;
        file.close();
    }

    // add labels and input fields for teams
    QGridLayout *gridLayout = new QGridLayout(this);
    for(int i = 1; i <= numTeams; ++i){
        gridLayout->addWidget(new QLabel("Team " + QString::number(i)), i - 1, 0);
        teamLineEdit.push_back(new QLineEdit(this));
        teamLineEdit[i-1]->setObjectName("Team_" + QString::number(i));
        gridLayout->addWidget(teamLineEdit[i-1], i - 1, 1);
    }
    // add Cancel and Continue buttons
    QPushButton* cancel_but = new QPushButton(this);
    cancel_but->setText("Cancel");
    cancel_but->setCursor(Qt::PointingHandCursor);
    cancel_but->show();
    gridLayout->addWidget(cancel_but);
    connect(cancel_but, SIGNAL(clicked()), this, SLOT(on_cancel_clicked()));
    QPushButton* conitue_but = new QPushButton(this);
    conitue_but->setText("Continue");
    conitue_but->show();
    conitue_but->setCursor(Qt::PointingHandCursor);
    gridLayout->addWidget(conitue_but);
    connect(conitue_but, SIGNAL(clicked()), this, SLOT(on_continue_3_clicked()));
}

Teams_name::~Teams_name()
{
    delete ui;
}

void Teams_name::on_continue_3_clicked()
{
    // check if all teams are named
    QFile file("team_names.txt");
    bool flag = true;

    for(int i = 0; i < numTeams; ++i){
        if(teamLineEdit[i]->text() == "")
            flag = false;
        for(int j = i + 1; j < numTeams; ++j){
            if (teamLineEdit[i]->text() == teamLineEdit[j]->text())
                flag = false;
        }
    }
    if (flag){
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            for(int i = 0; i < numTeams; i++){
                 out << teamLineEdit[i]->text() << "\n";
            }
        }
        file.close();
        hide();
        Duration_score window;
        window.setModal(true);
        window.exec();
    } else {
        QMessageBox::information(this, "Teams", "Please select all team names! Team names must not be repeated");
    }

}
void Teams_name::on_cancel_clicked()
{
    hide();
    Play window;
    window.setModal(true);
    window.exec();
}

