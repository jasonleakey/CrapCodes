#-------------------------------------------------
#
# Project created by QtCreator 2012-03-26T22:29:16
#
#-------------------------------------------------

QT       += core gui

TARGET = weibo4linux
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    oauthagent.cpp

HEADERS  += loginwindow.h \
    ../weibo-sdk-util/include/ParsingObject.hxx \
    ../weibo-sdk-util/include/IWeiboMethod.hxx \
    ../weibo-sdk-util/include/IWeiboDef.hxx \
    ../weibo-sdk-util/include/IWeibo.hxx \
    ../weibo-sdk-util/include/compat.hxx \
    oauthagent.h

FORMS    += loginwindow.ui
