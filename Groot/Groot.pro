QT += quick sql core concurrent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        uicontroller.cpp

RESOURCES += qml.qrc
include($$PWD/../VPNCore/lib/android_openssl/openssl.pri)
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD

# set_source_files_properties($$PWD/style/Style.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}


unix:!macx: LIBS += -L$$OUT_PWD/../VPNCore/ -lVPNCore_arm64-v8a

INCLUDEPATH += $$PWD/../VPNCore
DEPENDPATH += $$PWD/../VPNCore

HEADERS += \
    uicontroller.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/xyz/irootsoftware/device/Device.java \
    android/src/xyz/irootsoftware/wireguard/WgManager.java \
    android/src/xyz/irootsoftware/wireguard/WireguardCientConfig.java \
    android/src/xyz/irootsoftware/wireguard/WireguardConnection.java \
    android/src/xyz/irootsoftware/wireguard/WireguardTunnel.java \
    android/src/xyz/irootsoftware/keymanager/KKeyManager.java \
    android/src/xyz/irootsoftware/device/Device.java
