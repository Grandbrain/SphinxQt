QT          += core gui widgets multimedia
TARGET      = SphinxQt
TEMPLATE    = app
SOURCES     += main.cpp window.cpp about.cpp recognition.cpp
HEADERS     += window.h about.h recognition.h
FORMS       += window.ui about.ui
RESOURCES   += resources.qrc
RC_FILE     = resources.rc
INCLUDEPATH += $$PWD/../External/sphinx/include
DEPENDPATH  += $$PWD/../External/sphinx/include

win32 {
    CONFIG(debug, debug|release) {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/../External/sphinx/lib/windows/32bit/debug/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/windows/32bit/debug/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/../External/sphinx/lib/windows/64bit/debug/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/windows/64bit/debug/ -lpocketsphinx
        }
    } else {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/../External/sphinx/lib/windows/32bit/release/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/windows/32bit/release/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/../External/sphinx/lib/windows/64bit/release/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/windows/64bit/release/ -lpocketsphinx
        }
    }
}

unix {
    CONFIG(debug, debug|release) {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/../External/sphinx/lib/linux/32bit/debug/ -lsphinxad
            LIBS += -L$$PWD/../External/sphinx/lib/linux/32bit/debug/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/linux/32bit/debug/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/../External/sphinx/lib/linux/64bit/debug/ -lsphinxad
            LIBS += -L$$PWD/../External/sphinx/lib/linux/64bit/debug/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/linux/64bit/debug/ -lpocketsphinx
        }
    } else {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/../External/sphinx/lib/linux/32bit/release/ -lsphinxad
            LIBS += -L$$PWD/../External/sphinx/lib/linux/32bit/release/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/linux/32bit/release/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/../External/sphinx/lib/linux/64bit/release/ -lsphinxad
            LIBS += -L$$PWD/../External/sphinx/lib/linux/64bit/release/ -lsphinxbase
            LIBS += -L$$PWD/../External/sphinx/lib/linux/64bit/release/ -lpocketsphinx
        }
    }
}
