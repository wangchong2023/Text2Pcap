QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(Thirdpart/singleapplication/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QApplication
DEFINES += QT_MESSAGELOGCONTEXT


SOURCES += \
    Main/initialize.cpp \
    Main/main.cpp \
    Pages/text2pcapwidget.cpp \
    Schedule/timerutils.cpp \
    Service/text2pcap.cpp \
    Utils/MultiPlatform/Common/common_adaptor.cpp \
    Utils/MultiPlatform/Common/fileutils.cpp \
    Utils/MultiPlatform/Common/fontutils.cpp \
    Utils/MultiPlatform/Common/wiresharkutils.cpp \
    Utils/System/logutils.cpp \
    Utils/System/processutils.cpp \
    Utils/System/sysrun.cpp \
    Utils/System/systray.cpp \
    Utils/Theme/qssstyle.cpp \
    Utils/Tools/buildutils.cpp \
    Utils/Tools/stringutils.cpp

macx {
    SOURCES += \
        Utils/MultiPlatform/MacOS/fileutils_macos.cpp \
        Utils/MultiPlatform/MacOS/wiresharkutils_macos.cpp
}

win32 {
    SOURCES += \
        Utils/MultiPlatform/Windows/fileutils_win.cpp \
        Utils/MultiPlatform/Windows/wiresharkutils_win.cpp
}

HEADERS += \
    Common/common_def.h \
    Common/common_header.h \
    Common/infostring.h \
    Common/sys_header.h \
    Common/thirdpart_header.h \
    Common/ui_header.h \
    Main/initialize.h \
    Pages/text2pcapwidget.h \
    Schedule/timerutils.h \
    Service/text2pcap.h \
    Utils/MultiPlatform/Common/common_adapter_def.h \
    Utils/MultiPlatform/Common/common_adaptor.h \
    Utils/MultiPlatform/Common/fileutils.h \
    Utils/MultiPlatform/Common/fontutils.h \
    Utils/MultiPlatform/Common/wiresharkutils.h \
    Utils/System/logutils.h \
    Utils/System/processutils.h \
    Utils/System/sysrun.h \
    Utils/System/systray.h \
    Utils/Theme/qssstyle.h \
    Utils/Tools/buildutils.h \
    Utils/Tools/stringutils.h

macx {
    HEADERS += \
        Utils/MultiPlatform/MacOS/fileutils_macos.h \
        Utils/MultiPlatform/MacOS/wiresharkutils_macos.h
}

win32 {
    HEADERS += \
        Utils/MultiPlatform/Windows/fileutils_win.h \
        Utils/MultiPlatform/Windows/wiresharkutils_win.h
}

FORMS += \
    Resources/ui/text2pcapwidget.ui


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/text2pcap.qrc

ICON = Resources/icons/app.icns

RC_ICONS = Resources/icons/app.ico

DISTFILES += \
    Resources/icons/icoons/app.icns \
    Resources/icons/icoons/app.ico \
    Resources/lang/Text2Pcap_zh_CN.ts \
    Resources/qss/dark.qss \
    Resources/qss/light.qss\n
