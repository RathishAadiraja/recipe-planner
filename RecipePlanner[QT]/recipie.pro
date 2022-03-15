QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_dialog.cpp \
    cook_dialog.cpp \
    edit_dialog.cpp \
    globals.cpp \
    ingred_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    recipie_dialog.cpp

HEADERS += \
    add_dialog.h \
    cook_dialog.h \
    edit_dialog.h \
    globals.h \
    ingred_dialog.h \
    mainwindow.h \
    recipie_dialog.h

FORMS += \
    add_dialog.ui \
    cook_dialog.ui \
    edit_dialog.ui \
    ingred_dialog.ui \
    mainwindow.ui \
    recipie_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
