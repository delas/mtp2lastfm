# -------------------------------------------------
# Project created by QtCreator 2009-02-04T18:25:21
# -------------------------------------------------
QT += network \
    sql \
    xml
TARGET = mtp2lastfm
TEMPLATE = app
SOURCES += src/main.cpp \
    src/view/mainwindow.cpp \
    src/view/configurationloading.cpp \
    src/threads/loaderthread.cpp \
    src/net/versionchecker.cpp \
    src/model/dbconfig.cpp \
    src/db/sqliteorm.cpp \
    src/view/newversiondialog.cpp \
    src/model/device.cpp \
    src/threads/devicepoller.cpp \
    src/model/qintitem.cpp \
    src/threads/tracksimporter.cpp \
    src/view/tracksimport.cpp \
    src/threads/scrobbler.cpp \
    src/view/scrobblerprogress.cpp \
    src/model/md5.cpp \
    src/view/authenticationdialog.cpp \
    src/model/track.cpp
HEADERS += src/view/mainwindow.h \
    src/config.h \
    src/view/configurationloading.h \
    src/threads/loaderthread.h \
    src/net/versionchecker.h \
    src/db/base_sql_structure.h \
    src/model/dbconfig.h \
    src/db/sqliteorm.h \
    src/view/newversiondialog.h \
    src/model/device.h \
    src/threads/devicepoller.h \
    src/model/qintitem.h \
    src/threads/tracksimporter.h \
    src/view/tracksimport.h \
    src/threads/scrobbler.h \
    src/view/scrobblerprogress.h \
    src/model/md5.h \
    src/view/authenticationdialog.h \
    src/model/track.h
FORMS += src/view/mainwindow.ui \
    src/view/configurationloading.ui \
    src/view/newversiondialog.ui \
    src/view/tracksimport.ui \
    src/view/scrobblerprogress.ui \
    src/view/authenticationdialog.ui
RESOURCES += src/resources/resources.qrc
