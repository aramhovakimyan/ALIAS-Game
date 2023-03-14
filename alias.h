#ifndef ALIAS_H
#define ALIAS_H

#include <QMainWindow>
#include <QMessageBox>
#include "addword.h"
#include "play.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Alias; }
QT_END_NAMESPACE

class Alias : public QMainWindow
{
    Q_OBJECT

public:
    Alias(QWidget *parent = nullptr);
    ~Alias();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Alias *ui;
};
#endif // ALIAS_H
