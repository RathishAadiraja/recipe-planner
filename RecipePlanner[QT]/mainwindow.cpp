#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cook_dialog.h"
#include "globals.h"
#include "add_dialog.h"
#include "edit_dialog.h"


#include<QDebug>
#include<QJsonParseError>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QStringListModel>
#include<QAbstractItemView>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Process initiated";

    update_func();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_func()
{
    QFile inFile(file_path);
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()){
        qDebug() << "Opening and reading file failed";
    }

    rootObj = doc.object();
    QJsonObject ingredients_list_needed;

    QStringList food_list = rootObj.keys();

    QStringListModel *model = new QStringListModel();
    model->setStringList(food_list);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

void MainWindow::start_timer()
{
    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(update_func()));
    timer2->start(1000);

}

void MainWindow::on_write_pushButton_clicked()
{
    cook_Dialog* cook_dlg = new cook_Dialog(this);
    cook_dlg->show();

}

void MainWindow::on_Add_pushButton_clicked()
{

    Add_Dialog* add_dlg = new Add_Dialog(this);
    add_dlg->show();

    start_timer();

}

void MainWindow::on_Edit_pushButton_clicked()
{

    QModelIndex edit_index = ui->listView->currentIndex();
    QString edit_itemText = edit_index.data(Qt::DisplayRole).toString();

    current_item_chosen = edit_itemText;

    Edit_Dialog* edit_dlg = new Edit_Dialog(this);
    edit_dlg->show();

    start_timer();

}

void MainWindow::on_Delete_pushButton_clicked()
{


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete message", "Are you sure you want to delete all the contents of the selected item?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        QModelIndex del_index = ui->listView->currentIndex();
        QString itemText = del_index.data(Qt::DisplayRole).toString();

        rootObj.remove(itemText);

        QJsonDocument JsonDocument;
        JsonDocument.setObject(rootObj);
        QFile file(file_path);
        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(JsonDocument.toJson());
        file.close();

        update_func();

    }

}
