#-------------------------------------------------
#
# Project created by QtCreator 2014-08-16T17:40:21
#
#-------------------------------------------------

QT       += core gui widgets

# TEMPLATE = app

TARGET = sprite_packer
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp\
    resource.cpp \
    resourcefactory.cpp \
    gifresource.cpp \
    compoundresource.cpp \
    folder.cpp \
    item.cpp

HEADERS  += \
    resource.h \
    resourcefactory.h \
    gifresource.h \
    precompiled.h \
    compoundresource.h \
    folder.h \
    item.h

FORMS    +=
