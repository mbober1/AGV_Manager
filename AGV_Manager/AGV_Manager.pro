QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/robot.cpp \
    src/scene.cpp \
    src/taskitem.cpp

HEADERS += \
    inc/mainwindow.hpp \
    inc/robot.hpp \
    inc/scene.hpp \
    inc/taskitem.hpp \
    build/ui_listitem.h \
    build/ui_mainwindow.h \
    build/ui_taskitem.h

FORMS += \
    ui/mainwindow.ui \
    ui/taskitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
