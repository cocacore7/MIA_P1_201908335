QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        bloquesapstruct.cpp \
        bloquesarstruct.cpp \
        bloquescastruct.cpp \
        cabeceramontadas.cpp \
        clexec.cpp \
        clfdisk.cpp \
        cllogin.cpp \
        clmkdisk.cpp \
        clmkfs.cpp \
        clmkgrp.cpp \
        clmkuser.cpp \
        clmontada.cpp \
        clmount.cpp \
        clreportes.cpp \
        clrmdisk.cpp \
        clrmgrp.cpp \
        clrmuser.cpp \
        clsesion.cpp \
        clunmount.cpp \
        ebrstruct.cpp \
        main.cpp \
        mbrstruct.cpp \
        parser.cpp \
        sbstruct.cpp \
        scanner.cpp \
        tinodosstruct.cpp \
        usuariostruct.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    bloquesapstruct.h \
    bloquesarstruct.h \
    bloquescastruct.h \
    cabeceramontadas.h \
    clexec.h \
    clfdisk.h \
    cllogin.h \
    clmkdisk.h \
    clmkfs.h \
    clmkgrp.h \
    clmkuser.h \
    clmontada.h \
    clmount.h \
    clreportes.h \
    clrmdisk.h \
    clrmgrp.h \
    clrmuser.h \
    clsesion.h \
    clunmount.h \
    ebrstruct.h \
    lexico.l \
    mbrstruct.h \
    parser.h \
    sbstruct.h \
    scanner.h \
    sintactico.y \
    tinodosstruct.h \
    usuariostruct.h
