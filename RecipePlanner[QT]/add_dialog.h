#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <QJsonObject>
#include "mainwindow.h"
#include "globals.h"

namespace Ui {
class Add_Dialog;
}

class Add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Dialog(QWidget *parent = nullptr);
    ~Add_Dialog();
    QJsonObject ingred_list;


protected:

    void closeEvent(QCloseEvent *event) override {

            if (event->spontaneous()) {
                timer2->stop();

            } else {
                qDebug("The clode button was not clicked");
            }
        }

private slots:
    void on_add_ing_pushButton_clicked();
    void on_save_pushButton_clicked();

private:
    Ui::Add_Dialog *ui;
};

#endif // ADD_DIALOG_H
