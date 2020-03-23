    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //przygotowanie widgetu VTK do działania
    aRenderer = vtkSmartPointer<vtkRenderer>::New();
    renWin = ui->qvtkWidget->GetRenderWindow();
    renWin->AddRenderer(aRenderer);

    // utworzenie strumienia VTK
    newVtkPipe();

    // łączenie sygnałów i slotów
    connect(ui->actionQt,SIGNAL(triggered()),
            qApp,SLOT(aboutQt()));

    // przesłanie informacji z Qt do VTK
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            this,SLOT(setIsoValue(int)));

    // Zestawienie połączeń VTK->Gt:
    connections = vtkSmartPointer<vtkEventQtSlotConnect>::New();

    // przechwycenie zdarzeń VTK:
    connections->Connect(ui->qvtkWidget->GetInteractor(),
                         vtkCommand::LeftButtonReleaseEvent,
                         this,
                         SLOT(updateCamCoords(vtkObject*, unsigned long, void*, void*)));

    connections->Connect(ui->qvtkWidget->GetInteractor(),
                         vtkCommand::AnyEvent,
                         this,
                         SLOT(testSlot(vtkObject*, unsigned long, void*, void*)));

    connections->Connect(ui->qvtkWidget->GetInteractor(),
                         vtkCommand::KeyPressEvent,
                         this,
                         SLOT(testSlot(vtkObject*, unsigned long, void*, void*)));


    // debug poprawności połączeń VTK->Qt na konsolę:
    connections->PrintSelf(cout, vtkIndent());      // tak można sprawdzać dowolne obiekty VTK

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newVtkPipe()
{

    vtkSmartPointer<vtkVolume16Reader> v16 =
      vtkSmartPointer<vtkVolume16Reader>::New();
    v16->SetDataDimensions (64,64);
    v16->SetImageRange (1,93);
    v16->SetDataByteOrderToLittleEndian();
    v16->SetFilePrefix ("/usr/share/VTKData/Data/headsq/quarter");
    v16->SetDataSpacing (3.2, 3.2, 1.5);

    
    skinExtractor = vtkSmartPointer<vtkContourFilter>::New();
    skinExtractor->SetInputConnection(v16->GetOutputPort());
    skinExtractor->SetValue(0, 1000);

    vtkSmartPointer<vtkPolyDataNormals> skinNormals =
      vtkSmartPointer<vtkPolyDataNormals>::New();
    skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);

    vtkSmartPointer<vtkPolyDataMapper> skinMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    skinMapper->SetInputConnection(skinNormals->GetOutputPort());
    skinMapper->ScalarVisibilityOff();

     skin =
   vtkSmartPointer<vtkActor>::New();
    skin->SetMapper(skinMapper);

     
    vtkSmartPointer<vtkOutlineFilter> outlineData =
      vtkSmartPointer<vtkOutlineFilter>::New();
    outlineData->SetInputConnection(v16->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> mapOutline =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapOutline->SetInputConnection(outlineData->GetOutputPort());

   outline =
      vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkCamera> aCamera =
      vtkSmartPointer<vtkCamera>::New();
    aCamera->SetViewUp (0, 0, -1);
    aCamera->SetPosition (0, 1, 0);
    aCamera->SetFocalPoint (0, 0, 0);
    aCamera->ComputeViewPlaneNormal();
    aCamera->Azimuth(30.0);
    aCamera->Elevation(30.0);

   
    aRenderer->AddActor(outline);
    aRenderer->AddActor(skin);
    aRenderer->SetActiveCamera(aCamera);
    aRenderer->ResetCamera ();
    aCamera->Dolly(1.5);

     
    aRenderer->SetBackground(.8, .3, .4);
    renWin->SetSize(640, 480);

     
    aRenderer->ResetCameraClippingRange ();

 
}

void MainWindow::setIsoValue(int iso)
{
    skinExtractor->SetValue(0, iso);
    //wymuszenie rysowania widgetu Qt ze sceną VTK
    ui->qvtkWidget->repaint();

    qDebug() << iso;
}
 
void MainWindow::updateCamCoords(vtkObject*, unsigned long, void*, void*)
{
    double camPosition[3];
    aRenderer->GetActiveCamera()->GetPosition(camPosition);

    QString str = QString("camera position: x=%1 : ty=%2 : z=%3")
                  .arg(camPosition[0], 0, 'f', 4)
                  .arg(camPosition[1], 0, 'f', 4)
                  .arg(camPosition[2], 0, 'f', 4);

    qDebug() << "cam: " << str;

    ui->statusBar->showMessage(str);
}

void MainWindow::testSlot(vtkObject* obj, unsigned long, void*, void*)
{
    qDebug() << "# " <<  obj->GetClassName();
}

void MainWindow::on_actionbekgra_nd_triggered()
{
    QColor color = QColorDialog::getColor();  // wywołanie okienka
      if (color.isValid())    ;                // sprawdzenie poprawnosci
       aRenderer->SetBackground(color.redF(), color.greenF(), color.blueF());               // użycie koloru :)
    // void setCurrentColor((const QColor &color));
}

void MainWindow::on_actionczaszunia_triggered()
{
    QColor color = QColorDialog::getColor();  // wywołanie okienka
      if (color.isValid())    ;                // sprawdzenie poprawnosci
      skin->GetProperty()->SetColor(color.redF(), color.greenF(), color.blueF());               // użycie koloru :)
    // void setCurrentColor((const QColor &color));
}



void MainWindow::on_checkBox_clicked()
{
  outline->SetMapper(mapOutline);
   outline->GetProperty()->SetColor(1,1,1);
}

