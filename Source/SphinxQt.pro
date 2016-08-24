QT          += core gui widgets multimedia
TARGET      = SphinxQt
TEMPLATE    = app
SOURCES     += main.cpp window.cpp about.cpp recognition.cpp
HEADERS     += window.h about.h recognition.h
FORMS       += window.ui about.ui
RESOURCES   += resources.qrc
RC_FILE     = resources.rc
INCLUDEPATH += $$PWD/resources/sphinx/include
DEPENDPATH  += $$PWD/resources/sphinx/include

win32 {
    CONFIG(debug, debug|release) {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/resources/sphinx/lib/windows/debug/32bit/ -lsphinxbase
            LIBS += -L$$PWD/resources/sphinx/lib/windows/debug/32bit/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/resources/sphinx/lib/windows/debug/64bit/ -lsphinxbase
            LIBS += -L$$PWD/resources/sphinx/lib/windows/debug/64bit/ -lpocketsphinx
        }
    } else {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/resources/sphinx/lib/windows/release/32bit/ -lsphinxbase
            LIBS += -L$$PWD/resources/sphinx/lib/windows/release/32bit/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/resources/sphinx/lib/windows/release/64bit/ -lsphinxbase
            LIBS += -L$$PWD/resources/sphinx/lib/windows/release/64bit/ -lpocketsphinx
        }
    }
}