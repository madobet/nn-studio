#-------------------------------------------------
#
# Project created by QtCreator 2018-04-19T16:18:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    engine/mateng.cpp \
    engine/matengcore.cpp \
    engine/vengine.cpp \
    engine/venginecore.cpp \
    math/randnum.cpp \
    math/vmatrix.cpp \
    model/vaiharabrainnet.cpp \
    model/vneuronnet.cpp \
    network/vbrainnet.cpp \
    network/vgraph.cpp \
    network/vsmallworld.cpp \
    neuron/unknownmodel.cpp \
    neuron/vaihara.cpp \
    neuron/vhudgkinhuxley.cpp \
    neuron/vneuron.cpp \
    main.cpp \
    netvmainwin.cpp \
    optionwin.cpp \
    experiment.cpp

HEADERS += \
    engine/mateng.h \
    engine/matengcore.h \
    engine/vengine.h \
    engine/venginecore.h \
    math/randnum.h \
    math/vmath.h \
    math/vmatrix.h \
    model/vaiharabrainnet.h \
    model/vneuronnet.h \
    network/vbrainnet.h \
    network/vgraph.h \
    network/vsmallworld.h \
    neuron/unknownmodel.h \
    neuron/vaihara.h \
    neuron/vhudgkinhuxley.h \
    neuron/vneuron.h \
    netvmainwin.h \
    optionwin.h \
    experiment.h \
    ioprocess.h

FORMS += \
        netvmainwin.ui \
    optionwin.ui

# Matlab Engine
INCLUDEPATH += "D:/Program Files/MATLAB/R2018a/extern/include"

LIBS += \
    -L"D:/Program Files/MATLAB/R2018a/extern/lib/win64/microsoft" -llibeng -llibmat -llibmx -llibmex -lmclmcrrt -lmclmcr \
    -L"D:/Program Files/MATLAB/R2018a/extern/lib/win64/mingw64" -llibeng -llibmat -llibmx -llibmex -lmclmcrrt -lmclmcr \

RESOURCES += \
    resource.qrc
