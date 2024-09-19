QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    filedownloader.cpp \
    main.cpp \
    mainwindow.cpp \
    tdlgimg.cpp \
    tdlgoptions.cpp \
    tdlgstatus.cpp \
    tvars.cpp

HEADERS += \
    clickablelabel.h \
    filedownloader.h \
    mainwindow.h \
    tdlgimg.h \
    tdlgoptions.h \
    tdlgstatus.h \
    tvars.h

FORMS += \
    mainwindow.ui \
    tdlgimg.ui \
    tdlgoptions.ui \
    tdlgstatus.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# LINUX 5.12
#unix:!macx: LIBS += -L$$PWD/../../SMTP/lib/ -lSmtpMime

#INCLUDEPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src
#DEPENDPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src

RESOURCES += \
    res/res.qrc

win32:RC_ICONS += "res/mail3.ico"

# LINUX 5.13
#unix:!macx: LIBS += -L$$PWD/../../SMTP/lib/5.13/ -lSmtpMime

#INCLUDEPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src
#DEPENDPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src

#unix:!macx: LIBS += -L$$PWD/../../SMTP/win/MSVC/ -lSmtpMime2

#MINGW



#win32: LIBS += -L$$PWD/../../SMTP/win/MinGW/ -lSmtpMime2

#INCLUDEPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src
#DEPENDPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../SMTP/win/MinGW/SmtpMime2.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/../../SMTP/win/MinGW/libSmtpMime2.a

#win32: LIBS += -L$$PWD/../../SMTP/win/MSVC/ -lSmtpMime2

#INCLUDEPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src
#DEPENDPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src


#MINGW QT 6.7.2

win32: LIBS += -L$$PWD/../../SMTP/win/MinGW/6.7.2/ -lSmtpMime2

INCLUDEPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src
DEPENDPATH += $$PWD/../../SMTP/SmtpClient-for-Qt-dev/src
