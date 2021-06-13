QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cabeceramontadas.cpp \
        clexec.cpp \
        clfdisk.cpp \
        clmkdisk.cpp \
        clmkfs.cpp \
        clmontada.cpp \
        clmount.cpp \
        clreportes.cpp \
        clrmdisk.cpp \
        clunmount.cpp \
        ebrstruct.cpp \
        main.cpp \
        mbrstruct.cpp \
        parser.cpp \
        scanner.cpp \
        spstruct.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cabeceramontadas.h \
    clexec.h \
    clfdisk.h \
    clmkdisk.h \
    clmkfs.h \
    clmontada.h \
    clmount.h \
    clreportes.h \
    clrmdisk.h \
    clunmount.h \
    ebrstruct.h \
    lexico.l \
    mbrstruct.h \
    parser.h \
    scanner.h \
    sintactico.y \
    spstruct.h
