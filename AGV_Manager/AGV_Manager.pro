QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/AGV.cpp \
    src/robot.cpp \
    src/scene.cpp \
    src/Warehouse.cpp \
    src/Stage.cpp \
    src/taskitem.cpp \
    src/TrafficSystemControl.cpp \
   

HEADERS += \
    inc/mainwindow.hpp \
    inc/AGV.hpp \
    inc/Task.hpp \
    inc/robot.hpp \
    inc/scene.hpp \
    inc/taskitem.hpp \
    inc/Warehouse.hpp \
    inc/Stage.hpp \
    inc/Dynamic2DMatrix.hpp \
    inc/TrafficSystemControl.hpp \
    inc/TrafficSystemControl.hpp


FORMS += \
    ui/mainwindow.ui \
    ui/taskitem.ui

RESOURCES += \
    resources.qrc

RC_ICONS = resources/icons/warehouse.ico


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

