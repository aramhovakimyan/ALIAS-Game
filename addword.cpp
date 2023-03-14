#include "addword.h"
#include "ui_addword.h"

AddWord::AddWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWord)
{
    ui->setupUi(this);
}

AddWord::~AddWord()
{
    delete ui;
}

void AddWord::on_Save_accepted()
{
    // Save word in file
    QString word = ui->word->text();
    if(!word.isEmpty()){
        QFile file("words.txt");
        bool flag = true;
        if(file.open(QIODevice::ReadOnly)){
            QString data;
            QTextStream out(&file);
            while (!out.atEnd()){
                data = out.readLine();
                if (word == data)
                    flag = false;
            }
            file.close();
        }
        if (flag){
            if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file); out << word << "\n";
                file.close();
                QMessageBox::information(this, "WORD ADDED", "Your word is added! ");
            }
        } else {
            QMessageBox::warning(this, "WORD EXIST", "This word is exist, please enter another one! ");
            AddWord window;
            window.setModal(true);
            window.exec();
        }
    }
}
