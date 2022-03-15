#include "edit_dialog.h"
#include "ui_edit_dialog.h"
#include "globals.h"


#include <QStringList>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QCloseEvent>
#include <QJsonDocument>
#include <QMessageBox>

Edit_Dialog::Edit_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit_Dialog)
{
    ui->setupUi(this);


    if(rootObj.contains(current_item_chosen)){

        ui->fdname_plainTextEdit->setPlainText(current_item_chosen);

        QJsonObject edit_temp_food = rootObj[current_item_chosen].toObject();

        QJsonArray recipe_arr = edit_temp_food["recipe"].toArray();

        QString temp_str;

        for (int i = 0; i < recipe_arr.count(); i++){

            if (i==recipe_arr.count()-1){
                temp_str += recipe_arr[i].toString();
            }else{
                temp_str += recipe_arr[i].toString()+"\n";
            }

        }

        ui->recipe_plainTextEdit->setPlainText(temp_str);


        QStringList ingred_lst = edit_temp_food.keys();
        QString ingred_str;

        for(int i = 0; i < ingred_lst.count(); i++){
            if(ingred_lst[i]!="recipe"){
                if (i == ingred_lst.count()-1){
                    ingred_str += ingred_lst[i]+": "+edit_temp_food[ingred_lst[i]].toString();
                }else{
                    ingred_str += ingred_lst[i]+": "+edit_temp_food[ingred_lst[i]].toString()+"\n";
                }

            }
        }

        ui->ingred_plainTextEdit->setPlainText(ingred_str);

    }


}

Edit_Dialog::~Edit_Dialog()
{
    delete ui;
}



void Edit_Dialog::on_save_pushButton_clicked()
{


    QJsonObject ingred_obj;
    QJsonObject final_obj;

    QString edit_food_name = ui->fdname_plainTextEdit->toPlainText();
    QString edit_recipe = ui->recipe_plainTextEdit->toPlainText();

    QStringList edit_recipe_list = edit_recipe.split("\n");
    QJsonArray edit_recipe_arr = QJsonArray::fromStringList(edit_recipe_list);

    ingred_obj.insert("recipe",edit_recipe_arr);


    QString edit_ingred = ui->ingred_plainTextEdit->toPlainText();
    QStringList edit_ingred_list = edit_ingred.split("\n");


    QString name_matched;
    QString quant_matched;


    for (int i = 0; i < edit_ingred_list.count(); i++){

        QRegularExpression name_re;
        name_re.setPattern("([^:]+)");

        QRegularExpressionMatch name_match = name_re.match(edit_ingred_list[i]);
        if (name_match.hasMatch()){
            name_matched = name_match.captured(0);

        }else{

            qDebug() << "Name regex Failed" ;
        }




        QRegularExpression quant_re;
        quant_re.setPattern("[0-9]+[.]*[0-9]*[\\s]+[a-z]+");

        QRegularExpressionMatch quant_match = quant_re.match(edit_ingred_list[i]);
        if (quant_match.hasMatch()){
            quant_matched = quant_match.captured(0);

        }else{

            qDebug() << "Qunatity regex failed" ;
        }

        ingred_obj.insert(name_matched,quant_matched);



    }


    if(rootObj.contains(edit_food_name)){
        rootObj.insert(edit_food_name,ingred_obj);

    }else{
        QString current_combo_text = current_item_chosen;
        rootObj.remove(current_combo_text);
        rootObj.insert(edit_food_name,ingred_obj);

    }


    QJsonDocument JsonDocument;
    JsonDocument.setObject(rootObj);
    QFile file(file_path);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();

    QMessageBox::information(this,"Process finished","Item edited and saved successfully!");

    ui->fdname_plainTextEdit->clear();
    ui->recipe_plainTextEdit->clear();
    ui->ingred_plainTextEdit->clear();

}
