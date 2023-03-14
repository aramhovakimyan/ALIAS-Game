#ifndef ADDWORD_H
#define ADDWORD_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class AddWord;
}

class AddWord : public QDialog
{
    Q_OBJECT

public:
    explicit AddWord(QWidget *parent = nullptr);
    ~AddWord();

private slots:
    void on_Save_accepted();

private:
    Ui::AddWord *ui;
};

#endif // ADDWORD_H
