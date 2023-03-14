#include "alias.h"
#include "./ui_alias.h"

Alias::Alias(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Alias)
{
    ui->setupUi(this);
}

Alias::~Alias()
{
    delete ui;
}


void Alias::on_pushButton_clicked()
{
    hide();
    Play window;
    window.setModal(true);
    window.exec();
    show();
}


void Alias::on_pushButton_2_clicked()
{
    hide();
    QString rules = "   Number of players: \n  The game is played in teams of two or more players.\n   Objective:\n    The objective of the game is to help your team members guess the word on your card, without using the word itself, in the shortest possible time.\nGameplay:\n    1.  The game is played in rounds, with each round consisting of one member from each team taking a turn at describing the word on the card.\n  2.  The player describing the word is not allowed to use the word itself, any part of the word, or any other word that rhymes with it.\n  3.  The player is allowed to use gestures, draw pictures, and use other creative means to help their team members guess the word.\n  4.  The other members of the team can ask as many questions as they like within the given time limit (usually 60 seconds), and the player describing the word can only answer 'yes' or 'no'.\n  5.  If the team successfully guesses the word, they earn one point, and the next team takes their turn. If they do not guess the word within the time limit, the turn passes to the next team.\n  6.  The game continues until all the cards have been used, or until a pre-determined score is reached (usually 10 points).\n  7.  In the final round, the team with the most points gets to describe one final word, and the other team has one chance to guess. If the other team correctly guesses the word, the game goes into a tie-breaker round.\n  8.  In the tie-breaker round, each team chooses one player to describe a single word, and the first team to correctly guess the other team's word wins the game.";
    QMessageBox::about(this, "RULES", rules);
    show();
}


void Alias::on_pushButton_3_clicked()
{
    hide();
    AddWord window;
    window.setModal(true);
    window.exec();
    show();
}

