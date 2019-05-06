TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Gerarchia/consumable.cpp \
        Gerarchia/item.cpp \
        main.cpp \
        Gerarchia/multifunction.cpp \
        Gerarchia/normal.cpp \
        Gerarchia/stampante.cpp

HEADERS += \
    Gerarchia/consumable.h \
    Template/container.h \
    Template/deepptr.h \
    Gerarchia/item.h \
    Gerarchia/multifunction.h \
    Gerarchia/normal.h \
    Gerarchia/stampante.h
