#ifndef EDIT_DIALOG_H
#define EDIT_DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
#include "globals.h"


namespace Ui {
class Edit_Dialog;
}

class Edit_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_Dialog(QWidget *parent = nullptr);
    ~Edit_Dialog();

protected:
    void closeEvent(QCloseEvent *event) override {

            if (event->spontaneous()) {
                timer2->stop();

            } else {
                qDebug("The clode button was not clicked");
            }
        }
private slots:

    void on_save_pushButton_clicked();


private:
    Ui::Edit_Dialog *ui;
};

#endif // EDIT_DIALOG_H
