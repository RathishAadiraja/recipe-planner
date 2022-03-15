#ifndef COOK_DIALOG_H
#define COOK_DIALOG_H

#include <QDialog>

namespace Ui {
class cook_Dialog;
}

class cook_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit cook_Dialog(QWidget *parent = nullptr);
    ~cook_Dialog();

private slots:
    void on_check_recipie_pushButton_clicked();

    void on_ing_pushButton_clicked();

    bool check_valid_string();

private:
    Ui::cook_Dialog *ui;
};

#endif // COOK_DIALOG_H
