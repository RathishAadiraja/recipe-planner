#ifndef GLOBALS_H
#define GLOBALS_H


#include<QtGlobal>



QT_BEGIN_NAMESPACE
class QString;
class QJsonObject;
class QStringList;
class QTimer;
QT_END_NAMESPACE


extern QString file_path;
extern QJsonObject rootObj;
extern QStringList global_recipe_list;
extern QMap<QString,float> global_ingred_map;
extern QTimer *timer2;
extern QString current_item_chosen;
extern QString final_ingred_disp;


#endif // GLOBALS_H
