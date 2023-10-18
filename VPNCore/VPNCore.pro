QT -= gui
QT += network concurrent core

TEMPLATE = lib
DEFINES += VPNCORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apicaller.cpp \
    devicelistmodel.cpp \
    devicemanager.cpp \
    packagelistmodel.cpp \
    secretservice.cpp \
    traffic.cpp \
    tunnelwatcher.cpp \
    user.cpp \
    vpnconfig.cpp \
    vpncore.cpp \
    vpnmanager.cpp

HEADERS += \
    Utils.h \
    VPNCore_global.h \
    apicaller.h \
    devicelistmodel.h \
    devicemanager.h \
    packagelistmodel.h \
    secretservice.h \
    traffic.h \
    tunnelwatcher.h \
    user.h \
    vpnconfig.h \
    vpncore.h \
    vpnmanager.h
include($$PWD/lib/android_openssl/openssl.pri)
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
