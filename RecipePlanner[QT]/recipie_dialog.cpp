#include "recipie_dialog.h"
#include "ui_recipie_dialog.h"
#include "globals.h"

#include<QStringListModel>

recipie_Dialog::recipie_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recipie_Dialog)
{
    ui->setupUi(this);

    QStringListModel *model = new QStringListModel();
    model->setStringList(global_recipe_list);

    ui->recipie_listView->setModel(model);
    ui->recipie_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);



}

recipie_Dialog::~recipie_Dialog()
{
    delete ui;
}
