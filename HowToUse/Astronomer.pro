#----------------------------------------------------------------------------#
#                              *** АСТРОНОМ ***                              #
#                                                                            #
# Проект для Qt 5                                                            #
#                                                                            #
# Автор ГЛУЩЕНКО Сергей                                                      #
#                                                                            #
#                                                                     Москва #
#----------------------------------------------------------------------------#

QT += core widgets network sql

TARGET = Astronomer  #Имя исполняемого файла
TEMPLATE = app

DESTDIR = $$PWD/App  #Размещение исполняемого файла

win32 : RC_ICONS = Picture/Pic1.ico  #Пиктограмма приложения

SOURCES += \
    Main.cpp \
    Base.cpp \
    Wait.cpp \
    Error.cpp \
    Placement.cpp \
    WinTuner.cpp \
    WinLogBook.cpp \
    MainWin.cpp \
    Map.cpp \
    LayerAdd.cpp \
    LayerCtrl.cpp \
    ObjCtrl.cpp \
    ../../Calendar/Calendar.cpp \
    ../../Num/Numerical.cpp \
    ../Cartography.cpp \
    ../Frame.cpp \
    ../GISLib.cpp \
    ../Layer.cpp \
    ../MapData.cpp \
    ../Scene.cpp \
    ../ShellGIS.cpp \
    ../View.cpp \
    ../../Multitude/Clipper.cpp \
    ../../Multitude/Multitude.cpp \
    Nutation.cpp \
    ../../QuatVectMatr/GeneralLib.cpp

HEADERS += \
    Wait.h \
    Base.h \
    Error.h \
    Placement.h \
    WinTuner.h \
    WinLogBook.h \
    MainWin.h \
    Map.h \
    LayerAdd.h \
    LayerCtrl.h \
    ObjCtrl.h \
    ../../Calendar/Calendar.h \
    ../../Num/Numerical.h \
    ../Cartography.h \
    ../Frame.h \
    ../GISLib.h \
    ../Layer.h \
    ../MapData.h \
    ../Scene.h \
    ../ShellGIS.h \
    ../View.h \
    ../../Multitude/Clipper.h \
    ../../Multitude/Multitude.h \
    Nutation.h \
    ../../QuatVectMatr/GeneralLib.h

FORMS += \
    Wait.ui \
    Error.ui \
    WinTuner.ui \
    WinLogBook.ui \
    MainWin.ui \
    Map.ui \
    LayerAdd.ui \
    LayerCtrl.ui \
    ObjCtrl.ui

RESOURCES += \
    IconsForMenu.qrc
