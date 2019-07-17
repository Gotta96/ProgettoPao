TEMPLATE = app
CONFIG += c++11
QT += gui
QT += widgets
QMAKE_CXXFLAGS += -std=c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        Model/carrello.cpp \
        Model/Gerarchia/consumable.cpp \
        Model/Gerarchia/item.cpp \
        View/mainwindow.cpp \
        main.cpp \
        Model/Gerarchia/multifunction.cpp \
        Model/Gerarchia/normal.cpp \
        Model/Gerarchia/stampante.cpp

HEADERS += \
    Model/carrello.h \
    Model/Gerarchia/consumable.h \
    Model/Template/container.h \
    Model/Template/deepptr.h \
    Model/Gerarchia/item.h \
    Model/Gerarchia/multifunction.h \
    Model/Gerarchia/normal.h \
    Model/Gerarchia/stampante.h \
    View/mainwindow.h
