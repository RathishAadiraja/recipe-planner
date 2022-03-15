#ifndef INGRED_DIALOG_H
#define INGRED_DIALOG_H

#include <QDialog>

namespace Ui {
class ingred_Dialog;
}

class ingred_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ingred_Dialog(QWidget *parent = nullptr);
    ~ingred_Dialog();

private:
    Ui::ingred_Dialog *ui;
};

#endif // INGRED_DIALOG_H
