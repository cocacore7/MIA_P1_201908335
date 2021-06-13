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
        clcat.cpp \
        clchgrp.cpp \
        clchmmod.cpp \
        clchown.cpp \
        clcp.cpp \
        cledit.cpp \
        clexec.cpp \
        clfdisk.cpp \
        clfind.cpp \
        cllogin.cpp \
        clloss.cpp \
        clmkdir.cpp \
        clmkdisk.cpp \
        clmkfile.cpp \
        clmkfs.cpp \
        clmkgrp.cpp \
        clmkuser.cpp \
        clmontada.cpp \
        clmount.cpp \
        clmv.cpp \
        clrecovery.cpp \
        clrem.cpp \
        clren.cpp \
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
    clcat.h \
    clchgrp.h \
    clchmmod.h \
    clchown.h \
    clcp.h \
    cledit.h \
    clexec.h \
    clfdisk.h \
    clfind.h \
    cllogin.h \
    clloss.h \
    clmkdir.h \
    clmkdisk.h \
    clmkfile.h \
    clmkfs.h \
    clmkgrp.h \
    clmkuser.h \
    clmontada.h \
    clmount.h \
    clmv.h \
    clrecovery.h \
    clrem.h \
    clren.h \
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
