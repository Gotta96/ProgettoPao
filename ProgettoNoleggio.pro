TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Model/carrello.cpp \
        Model/Gerarchia/consumable.cpp \
        Model/Gerarchia/item.cpp \
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
    Model/Gerarchia/stampante.h
