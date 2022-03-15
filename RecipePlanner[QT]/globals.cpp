#include"globals.h"

#include <QString>
#include <QJsonObject>

QString file_path = "C:\\Users\\Rathish\\Desktop\\my_file.json";
QJsonObject rootObj;
QStringList global_recipe_list;
QMap<QString,float> global_ingred_map;
QTimer* timer2;
QString current_item_chosen;
QString final_ingred_disp;

