#-------------------------------------------------
#
# Project created by QtCreator 2018-08-01T00:49:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

equals(QT_MAJOR_VERSION,4) {
   message("QT4 used")
}

equals(QT_MAJOR_VERSION,5) {
   message("QT5 used")
}

VERSION  = 0.0.1
TARGET = pivmake-gui
TEMPLATE = app

DESTDIR=bin
CONFIG += release
#win32:CONFIG += console



################################################################################
## EXTRA LIBS SCRIPT
################################################################################

#LIBPDSDATAFUNC
extralibpdsdatafunc.target   = $${OUT_PWD}/extras/include/pds/pdsdatafunc.h
win32{
extralibpdsdatafunc.commands = $${PWD}/scripts/getpdsdatafunc.bat \"$${OUT_PWD}/extras\"
}
unix{
extralibpdsdatafunc.commands = $${PWD}/scripts/getpdsdatafunc.sh "$${OUT_PWD}/extras"
}
extralibpdsdatafunc.depends  =
QMAKE_EXTRA_TARGETS         += extralibpdsdatafunc
LIBS                        += $${OUT_PWD}/extras/lib/libpdsdatafunc.a
PRE_TARGETDEPS              += $${OUT_PWD}/extras/include/pds/pdsdatafunc.h

#LIBPDSRA
extralibpdsra.target   = $${OUT_PWD}/extras/include/pds/pdsra.h
win32{
extralibpdsra.commands = $${PWD}/scripts/getpdsra.bat \"$${OUT_PWD}/extras\"
}
unix{
extralibpdsra.commands = $${PWD}/scripts/getpdsra.sh "$${OUT_PWD}/extras"
}
extralibpdsra.depends  =
QMAKE_EXTRA_TARGETS   += extralibpdsra
LIBS                  += $${OUT_PWD}/extras/lib/libpdsra.a
PRE_TARGETDEPS        += $${OUT_PWD}/extras/include/pds/pdsra.h

#LIBPDSDIC
extralibpdsdic.target   = $${OUT_PWD}/extras/include/pds/pdsdic.h
win32{
extralibpdsdic.commands = $${PWD}/scripts/getpdsdic.bat \"$${OUT_PWD}/extras\"
}
unix{
extralibpdsdic.commands = $${PWD}/scripts/getpdsdic.sh "$${OUT_PWD}/extras"
}
extralibpdsdic.depends  = extralibpdsra
QMAKE_EXTRA_TARGETS    += extralibpdsdic
LIBS                   += $${OUT_PWD}/extras/lib/libpdsdic.a
PRE_TARGETDEPS         += $${OUT_PWD}/extras/include/pds/pdsdic.h

# ADDING ALL LIBS
INCLUDEPATH += $${OUT_PWD}/extras/include





################################################################################
## PREFIX SCRIPT
################################################################################

win32{
    DEFINES += __OS_WINDOWS__

    isEmpty(PREFIX) {
        PREFIX = c:\\usr\\local
        message("")
        message("To change the current 'make install' path, write: qmake PREFIX=C:\\another\\path")
    }
}

unix{
    DEFINES += __OS_UNIX__

    isEmpty(PREFIX) {
        PREFIX = /usr/local
        message("")
        message("To change the current 'make install' path, write: qmake PREFIX=/another/path")
    }
    
    
}
message("The current 'make install' path is $$PREFIX")

################################################################################
## CODE SCRIPT
################################################################################

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
        src/mythread.cpp \
    src/mainwindow_check.cpp \
    src/mainwindow_get_program.cpp \
    src/mainwindow_all_generate.cpp \
    src/mainwindow_all_configuration.cpp \
    src/mainwindow_all_listfilesdat.cpp \
    src/mainwindow_all_listregionsdat.cpp \
    src/mainwindow_all_output.cpp \
    src/mainwindow_messages.cpp \
    src/mainwindow_state.cpp \
    src/mainwindow_enable_widget.cpp \
    src/mainwindow_action.cpp

INCLUDEPATH += headers
HEADERS  += headers/mainwindow.h \ 
            headers/mythread.h


FORMS    += ui/mainwindow.ui


RESOURCES += \
    $${TARGET}.qrc

################################################################################
## INSTALL SCRIPT
################################################################################

## MYAPP
myapp.path   = $$PREFIX/bin
unix{
    myapp.files += bin/$${TARGET}
}
win32{
    myapp.files += bin/$${TARGET}.exe
}

# DOCS
documentation.path   = $$PREFIX/share/doc/$${TARGET}
documentation.files += \
    share/doc/$${TARGET}/$${TARGET}.md \
    share/doc/$${TARGET}/$${TARGET}.pdf

# ICONS
iconos.path = $$PREFIX/share/$${TARGET}/icons
iconos.files += \
    share/$${TARGET}/icons/$${TARGET}.png 

# DESKTOP
desktop.path = $$PREFIX/share/applications
desktop.files += share/applications/$${TARGET}.desktop

# Install: MYAPP DOCS ICONS DESKTOP
INSTALLS    += myapp\
    documentation \
    iconos \
    desktop 



################################################################################
## DISTRIBUTION RELEASE SCRIPT
################################################################################
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_TARGET=\\\"$$TARGET\\\"
DEFINES += APP_HOMEPAGE=\\\"https://github.com/trucomanx/pivmake-gui\\\"

unix{
QMAKE_CLEAN += -r bin
}

APPARCHITECTURE = $${QMAKE_HOST.arch}
equals(APPARCHITECTURE , "x86_64") {
    APPARCHITECTURE = "amd64"
}
equals(APPARCHITECTURE , "x86") {
    APPARCHITECTURE = "i386"
}
equals(APPARCHITECTURE , "i686") {
    APPARCHITECTURE = "i386"
}


message("")
message(" Program filename: $$TARGET")
message(" Program version:  $$VERSION")
message(" Host architecture $${QMAKE_HOST.arch}: $$APPARCHITECTURE")
message("")

APPSUMMARY="GUI to make PIV"
APPDESCRIPTION="A graphic user interface program to make particle image velocimetry"


DISTFILES += \
    scripts/* \
    scripts/README.md \
    share/applications/* \
    share/doc/$${TARGET}/* \
    share/$${TARGET}/icons/* \
    win/makewin.bat \
    win/README.md \
    win/$${TARGET}.nsi.input \
    deb/control.input \
    deb/makedeb.sh \
    deb/README.md \
    clean_all.sh  \
    ChangeLog  \
    README.md \
    LICENSE



################################################################################
## Generating the NSI file to create the *.exe file
################################################################################

NSI_FILE_STRING=$$cat(win/$${TARGET}.nsi.input,blob)
NSI_FILE_STRING=$$replace(NSI_FILE_STRING, QMAKE_VAR_APPVERSION    , $$VERSION)
NSI_FILE_STRING=$$replace(NSI_FILE_STRING, QMAKE_VAR_APPFILENAME   , $$TARGET)
NSI_FILE_STRING=$$replace(NSI_FILE_STRING, QMAKE_VAR_APPARCH       , $$APPARCHITECTURE)
NSI_FILE_STRING=$$replace(NSI_FILE_STRING, QMAKE_VAR_APPSUMMARY    , $$APPSUMMARY)
NSI_FILE_STRING=$$replace(NSI_FILE_STRING, QMAKE_VAR_APPDESCRIPTION, $$APPDESCRIPTION)
write_file(win/$${TARGET}.nsi, NSI_FILE_STRING)

QMAKE_CLEAN += win/$${TARGET}.nsi


################################################################################
## Generating the CONTROL file to create the *.deb file
################################################################################

DEBIAN_CONTROL_FILE_STRING=$$cat(deb/control.input,blob)
APPDEPENDENCES='libqt5gui5 (>=5.5.1), libqt5core5a (>=5.5.1), libqt5widgets5 (>=5.5.1)'
DEBIAN_CONTROL_FILE_STRING=$$replace(DEBIAN_CONTROL_FILE_STRING, QMAKE_VAR_APPVERSION    , $$VERSION)
DEBIAN_CONTROL_FILE_STRING=$$replace(DEBIAN_CONTROL_FILE_STRING, QMAKE_VAR_APPFILENAME   , $$TARGET)
DEBIAN_CONTROL_FILE_STRING=$$replace(DEBIAN_CONTROL_FILE_STRING, QMAKE_VAR_APPARCH       , $$APPARCHITECTURE)
DEBIAN_CONTROL_FILE_STRING=$$replace(DEBIAN_CONTROL_FILE_STRING, QMAKE_VAR_APPSUMMARY    , $$APPSUMMARY)
DEBIAN_CONTROL_FILE_STRING=$$replace(DEBIAN_CONTROL_FILE_STRING, QMAKE_VAR_APPDESCRIPTION, $$APPDESCRIPTION)
DEBIAN_CONTROL_FILE_STRING=$$replace(DEBIAN_CONTROL_FILE_STRING, QMAKE_VAR_APPDEPENDENCES, $$APPDEPENDENCES)
write_file(deb/control, DEBIAN_CONTROL_FILE_STRING)

QMAKE_CLEAN += deb/control



