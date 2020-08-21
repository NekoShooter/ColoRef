TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        base_RGB/Algoritmo_RGB.c \
        base_RGB/Convertir_a_RGB.c \
        base_RGB/RGB.cpp \
        base_RGB/SuperColor.cpp \
        interfaz/Principal.cpp \
        main.cpp

HEADERS += \
    base_RGB/Algoritmo_RGB.h \
    base_RGB/Convertir_a_RGB.h \
    base_RGB/MACROS.h \
    base_RGB/RGB.h \
    base_RGB/SuperColor.h \
    interfaz/Principal.h
