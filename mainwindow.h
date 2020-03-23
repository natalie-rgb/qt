#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>

#include <vtkEventQtSlotConnect.h>

// dodane biblioteki z Madical 1
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkSmartPointer.h>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newVtkPipe();             // inicjalizacja strumienia VTK

public slots:
    void setIsoValue(int iso);
    void updateCamCoords(vtkObject*, unsigned long, void*, void*);
    void testSlot(vtkObject*, unsigned long, void*, void*);
    
private slots:
    void on_actionbekgra_nd_triggered();

    void on_actionczaszunia_triggered();

    void on_actionsraatata_triggered();

    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;

    // wskaźniki na obiekty VTK
//    vtkConeSource* source;
//    vtkPolyDataMapper* mapper;
//    vtkActor* actor;
//    vtkRenderWindow* renWin;
    vtkSmartPointer<vtkRenderer> aRenderer;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkVolume16Reader> v16;
    vtkSmartPointer<vtkContourFilter> skinExtractor;
    vtkSmartPointer<vtkPolyDataNormals> skinNormals;
    vtkSmartPointer<vtkPolyDataMapper> skinMapper;
    vtkSmartPointer<vtkActor> skin;
    vtkSmartPointer<vtkOutlineFilter> outlineData;
    vtkSmartPointer<vtkPolyDataMapper> mapOutline;
    vtkSmartPointer<vtkActor> outline;
    vtkSmartPointer<vtkCamera> aCamera;


 
    vtkSmartPointer<vtkEventQtSlotConnect> connections;
};

#endif // MAINWINDOW_H
