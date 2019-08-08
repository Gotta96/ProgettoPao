TEMPLATE = app
CONFIG += c++11
QT += gui
QT += widgets
QMAKE_CXXFLAGS += -std=c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        Model/Gerarchia/consumable.cpp \
        Model/Gerarchia/item.cpp \
        Model/carrello.cpp \
        Model/model.cpp \
        Model/xmlio.cpp \
        View/mainwindow.cpp \
        View/modifywindow.cpp \
        View/smartlistview.cpp \
        View/insertionwindow.cpp \
        controller.cpp \
        main.cpp \
        Model/Gerarchia/multifunction.cpp \
        Model/Gerarchia/normal.cpp \
        Model/Gerarchia/stampante.cpp

HEADERS += \
    Model/Gerarchia/consumable.h \
    Model/Template/container.h \
    Model/Template/deepptr.h \
    Model/Gerarchia/item.h \
    Model/Gerarchia/multifunction.h \
    Model/Gerarchia/normal.h \
    Model/Gerarchia/stampante.h \
    Model/carrello.h \
    Model/model.h \
    Model/xmlio.h \
    View/insertionwindow.h \
    View/mainwindow.h \
    View/modifywindow.h \
    View/smartlistview.h \
    controller.h
