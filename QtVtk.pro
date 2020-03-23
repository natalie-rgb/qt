QMAKE_CXXFLAGS += -Wno-deprecated

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtVtk
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# VTK - warto sprawdzić, czy na danym komuterze te ścieżki i pliki faktycznie istnieją i są poprawne
#INCLUDEPATH += /usr/local/include/vtk-7.1
INCLUDEPATH += /usr/include/vtk-7.1


LIBS    += -L/usr/local/lib\
        -ldl -lGL -lvtkCommonColor-7.1 -lvtkCommonCore-7.1 \
        -lvtkCommonComputationalGeometry-7.1 -lvtkCommonDataModel-7.1 -lvtkCommonExecutionModel-7.1 \
        -lvtkCommonMath-7.1 -lvtkCommonMisc-7.1 -lvtkCommonSystem-7.1 -lvtkCommonTransforms-7.1 -lvtkFiltersCore-7.1 \
        -lvtkFiltersModeling-7.1 -lvtkFiltersExtraction-7.1 -lvtkFiltersGeneral-7.1 -lvtkFiltersGeometry-7.1 -lvtkFiltersHybrid-7.1 \
        -lvtkFiltersSources-7.1 -lvtkFiltersStatistics-7.1 -lvtkImagingCore-7.1 -lvtkImagingColor-7.1 \
        -lvtkImagingFourier-7.1 -lvtkImagingMath-7.1 -lvtkImagingMorphological-7.1 -lvtkImagingStencil-7.1 \
        -lvtkIOCore-7.1 -lvtkIOGeometry-7.1 -lvtkIOImage-7.1 -lvtkIOPLY-7.1 -lvtkInteractionStyle-7.1 \
        -lvtkInteractionWidgets-7.1 -lvtkGUISupportQt-7.1 -lvtkRenderingCore-7.1 -lvtkRenderingOpenGL2-7.1 \
        -lvtkRenderingQt-7.1 -lvtkRenderingVolume-7.1 -lvtksys-7.1
#-lvtkjsoncpp-7.1
#-lvtkzlib-7.1
#-lvtkalglib-7.1 #brakuje nowej wersji???
