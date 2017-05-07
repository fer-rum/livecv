TEMPLATE = lib
TARGET   = qmljsparser
QT      += core qml quick xml
CONFIG  += qt c++11

DEFINES += Q_QMLJSPARSER_LIB


#ENABLE_PLUTINTYPES = 1

!isEmpty(ENABLE_PLUGINTYPES){
    message(Plugin Types Enabled: Live CV will use private libraries)
    QT += core-private qml-private quick-private
    DEFINES += Q_PLUGINTYPES_ENABLED
}

# Editor Lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lcveditor/release/ -llcveditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lcveditor/debug/ -llcveditor
else:unix: LIBS += -L$$OUT_PWD/../../application -llcveditor

INCLUDEPATH += $$PWD/../lcveditor/src
DEPENDPATH += $$PWD/../lcveditor/src

# Destination

win32:CONFIG(debug, debug|release): DLLDESTDIR = $$quote($$OUT_PWD/../../application/debug)
else:win32:CONFIG(release, debug|release): DLLDESTDIR = $$quote($$OUT_PWD/../../application/release)
else:unix: TARGET = $$quote($$OUT_PWD/../../application/qmljsparser)

include($$PWD/src/qmljsparser.pri)
include($$PWD/3rdparty/3rdparty.pro)
include($$PWD/plugintypes/plugintypes.pri)
