#include "cook_dialog.h"
#include "ui_cook_dialog.h"
#include "globals.h"
#include "recipie_dialog.h"
#include "ingred_dialog.h"

#include <string>
#include <QDebug>
#include <regex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QMultiMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>

cook_Dialog::cook_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cook_Dialog)
{
    ui->setupUi(this);
}

cook_Dialog::~cook_Dialog()
{
    delete ui;
}

bool cook_Dialog::check_valid_string(){

    QString check_names_str = ui->names_plainTextEdit->toPlainText().toLower();
    QStringList check_names_list;
    check_names_list = check_names_str.split("\n");

    check_names_list.removeAll("");
    check_names_list.removeDuplicates();

    for (int i = 0;i < check_names_list.count();i++){
        if(!rootObj.contains(check_names_list[i])){
            return false;
        }
    }

    return true;

}


void cook_Dialog::on_check_recipie_pushButton_clicked()
{

    bool recipe_check_case = check_valid_string();

    if (ui->names_plainTextEdit->toPlainText().isEmpty()){

        QMessageBox::warning(this,"Error","Please fill the feild with food names");

    }else if(!recipe_check_case){

        QMessageBox::warning(this,"Error","Please check if the recipe for entered food items are availble or check the spelling properly!");

    }



    if (!ui->names_plainTextEdit->toPlainText().isEmpty() && recipe_check_case){


        global_recipe_list.clear();

        QString names_str = ui->names_plainTextEdit->toPlainText().toLower();
        QStringList names_list;
        names_list = names_str.split("\n");

        names_list.removeAll("");
        names_list.removeDuplicates();


        for(int i = 0; i < names_list.count(); i++){
            if(rootObj.contains(names_list[i])){

                QJsonObject temp_obj = rootObj[names_list[i]].toObject();
                QJsonArray temp_arr = temp_obj["recipe"].toArray();

                QString final_str = names_list[i];
                for (int i = 0; i < temp_arr.count(); i++){
                    final_str += "\n       => "+ temp_arr[i].toString();

                }

                if (!global_recipe_list.contains(final_str)){
                    global_recipe_list.append(final_str);
                }

            }
        }


        recipie_Dialog *sh_dlg = new recipie_Dialog(this);
        sh_dlg->show();
    }

}



void cook_Dialog::on_ing_pushButton_clicked()
{

    bool ing_check_case = check_valid_string();

    if (ui->names_plainTextEdit->toPlainText().isEmpty()){

        QMessageBox::warning(this,"Error","Please fill the feild with food names");

    }else if(!ing_check_case){

        QMessageBox::warning(this,"Error","Please check if the recipe for entered food items are availble or check the spelling properly!");

    }


    if (!ui->names_plainTextEdit->toPlainText().isEmpty() && ing_check_case){

        QString names_str = ui->names_plainTextEdit->toPlainText().toLower();
        QStringList names_list = names_str.split("\n");

        names_list.removeAll("");
        names_list.sort();


        QMap<QString,int> item_count;


        for (int i = 0; i < names_list.count(); i++){
            int count_val = names_list.count(names_list[i]);
            item_count.insert(names_list[i],count_val);

        }

        names_list.removeDuplicates();

        QMap<QString,float> ingred_map_count;

        for (int i = 0; i < names_list.count(); i++ ){

            int multiplier = item_count.value(names_list[i]);

            QJsonObject ing_temp_obj = rootObj[names_list[i]].toObject();
            QStringList ing_temp_list = ing_temp_obj.keys();
            int ingred_count = ing_temp_obj.keys().count();

            for(int i = 0; i < ingred_count; i++){
                if(ing_temp_list[i]!="recipe"){

                    QStringList temp_lst = ing_temp_obj[ing_temp_list[i]].toString().split(" ");
                    temp_lst.removeAll("");

                    QString truncate_str = ing_temp_list[i]+"---"+temp_lst[1];
                    float quant = temp_lst[0].toFloat();
                    quant = quant * multiplier;

                    if(ingred_map_count.contains(truncate_str)){
                        float updated_num = ingred_map_count.value(truncate_str)+quant;
                        ingred_map_count.insert(truncate_str,updated_num);


                    }else{
                        ingred_map_count.insert(truncate_str,quant);

                    }

                }
            }

        }


        QString final_disp_str;
        QStringList map_count_lst = ingred_map_count.keys();

        for(int i = 0; i < map_count_lst.count(); i++){

            QStringList divided_lst = map_count_lst[i].split("---");
            QString conv_num = QString::number(ingred_map_count.value(map_count_lst[i]));


            if(i==map_count_lst.count()-1){
                final_disp_str += divided_lst[0]+": "+conv_num+" "+divided_lst[1];
            }else{
                final_disp_str += divided_lst[0]+": "+conv_num+" "+divided_lst[1]+"\n";

            }


        }

        final_ingred_disp = final_disp_str;

        ingred_Dialog *ing_dlg = new ingred_Dialog(this);
        ing_dlg->show();
    }

}
