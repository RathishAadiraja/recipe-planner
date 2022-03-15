#ifndef RECIPIE_DIALOG_H
#define RECIPIE_DIALOG_H

#include <QDialog>

namespace Ui {
class recipie_Dialog;
}

class recipie_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit recipie_Dialog(QWidget *parent = nullptr);
    ~recipie_Dialog();

private slots:


private:
    Ui::recipie_Dialog *ui;
};

#endif // RECIPIE_DIALOG_H
