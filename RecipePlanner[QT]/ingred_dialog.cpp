#include "ingred_dialog.h"
#include "ui_ingred_dialog.h"

#include "globals.h"

ingred_Dialog::ingred_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ingred_Dialog)
{
    ui->setupUi(this);

    ui->fin_ingred_plainTextEdit->setPlainText(final_ingred_disp);


}

ingred_Dialog::~ingred_Dialog()
{
    delete ui;
}
