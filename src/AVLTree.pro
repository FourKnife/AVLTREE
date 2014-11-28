#-------------------------------------------------
#
# Project created by QtCreator 2014-11-12T14:32:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AVLTree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    avltree.cpp \
    dictionary.cpp \
    controller.cpp \
    view.cpp \
    digital.cpp \
    article.cpp

HEADERS  += mainwindow.h \
    avltree.h \
    dictionary.h \
    controller.h \
    view.h \
    digital.h \
    article.h

FORMS    += mainwindow.ui
