#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "globals.h"
#include "mainwindow.h"



#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>

Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Dialog)
{
    ui->setupUi(this);


}

Add_Dialog::~Add_Dialog()
{
    delete ui;
}

void Add_Dialog::on_add_ing_pushButton_clicked()
{

    if(ui->ingr_plainTextEdit->toPlainText().isEmpty()||ui->quant_plainTextEdit->toPlainText().isEmpty()||
            ui->unit_plainTextEdit->toPlainText().isEmpty()){

        QMessageBox::warning(this,"Error","Please fill all the fields");

    }else{

        QString ingr_quant;
        ingr_quant =ui->quant_plainTextEdit->toPlainText() +" "+ui->unit_plainTextEdit->toPlainText();

        QString ingr_name;
        ingr_name = ui->ingr_plainTextEdit->toPlainText();

        ingred_list.insert(ingr_name,ingr_quant);

        ui->ingr_plainTextEdit->clear();
        ui->quant_plainTextEdit->clear();
        ui->unit_plainTextEdit->clear();


        QMessageBox::information(this,"Process finished","New ingredient added successfully!");

    }

}


void Add_Dialog::on_save_pushButton_clicked()
{

    if(ui->food_plainTextEdit->toPlainText().isEmpty()||ui->recipe_textEdit->toPlainText().isEmpty()){

        QMessageBox::warning(this,"Error","Please fill all the fields");
    }else{

        QString name_str = ui->food_plainTextEdit->toPlainText().toLower();
        QString recipe_str = ui->recipe_textEdit->toPlainText();

        QJsonArray recipe_arr = QJsonArray::fromStringList(recipe_str.split('\n'));

        ingred_list.insert("recipe",recipe_arr);

        rootObj.insert(name_str,ingred_list);

        QJsonDocument JsonDocument;
        JsonDocument.setObject(rootObj);
        QFile file(file_path);
        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(JsonDocument.toJson());
        file.close();

        QMessageBox::information(this,"Process finished","New item added and saved successfully!");

        ui->food_plainTextEdit->clear();
        ui->recipe_textEdit->clear();


    }

}
