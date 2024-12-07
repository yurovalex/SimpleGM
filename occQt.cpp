
#include "occQt.h"
#include "occView.h"

#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QDockWidget>


#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>

#include <AIS_Shape.hxx>

occQt::occQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    myOccView = new OccView(this);
    setCentralWidget(myOccView);
    createActions();
    createMenus();
    createToolBars();
}

occQt::~occQt()
{

}

void occQt::createActions( void )
{
    // File
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // View
    connect(ui.actionZoom, SIGNAL(triggered()), myOccView, SLOT(zoom()));
    connect(ui.actionPan, SIGNAL(triggered()), myOccView, SLOT(pan()));
    connect(ui.actionRotate, SIGNAL(triggered()), myOccView, SLOT(rotate()));

    connect(ui.actionReset, SIGNAL(triggered()), myOccView, SLOT(reset()));
    connect(ui.actionFitAll, SIGNAL(triggered()), myOccView, SLOT(fitAll()));
    connect(ui.actionDeleteAll, SIGNAL(triggered()), myOccView, SLOT(deleteAll()));

    //2D
    connect(ui.actionPoints, SIGNAL(triggered()), this, SLOT(points()));
    connect(ui.actionLines, SIGNAL(triggered()), this, SLOT(lines()));
    connect(ui.actionSplines, SIGNAL(triggered()), this, SLOT(splines()));

    // Primitive
    connect(ui.actionBox, SIGNAL(triggered()), this, SLOT(makeBox()));
    connect(ui.actionCone, SIGNAL(triggered()), this, SLOT(makeCone()));

    // Help
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void occQt::createMenus( void )
{
}

void occQt::createToolBars( void )
{
    QToolBar* aToolBar = addToolBar(tr("&Navigate"));
    aToolBar->addAction(ui.actionZoom);
    aToolBar->addAction(ui.actionPan);
    aToolBar->addAction(ui.actionRotate);

    aToolBar = addToolBar(tr("&View"));
    aToolBar->addAction(ui.actionReset);
    aToolBar->addAction(ui.actionFitAll);
    aToolBar->addAction(ui.actionDeleteAll);

    aToolBar = addToolBar(tr("&Primitive"));
    aToolBar->addAction(ui.actionBox);
    aToolBar->addAction(ui.actionCone);
    aToolBar->addAction(ui.actionLines);

    aToolBar = addToolBar(tr("Help"));
    aToolBar->addAction(ui.actionAbout);
}

void occQt::about()
{
    QMessageBox::about(this, tr("About SimpleGM for Qt"),
        tr("<h2>occQt 2.1</h2>"
        "<p>Copyright &copy; 2014-2024 eryar@163.com (yurovalex2@gmail.com)"
        "<p>SimpleGM is a demo applicaton about Qt and OpenCASCADE."));
}

void occQt::makeBox()
{
    TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();
    Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
    anAisBox->SetColor(Quantity_NOC_AZURE);
    myOccView->getContext()->Display(anAisBox, Standard_True);

}

void occQt::makeCone()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 10.0, 0.0));

    TopoDS_Shape aTopoReducer = BRepPrimAPI_MakeCone(anAxis, 3.0, 1.5, 5.0).Shape();
    Handle(AIS_Shape) anAisReducer = new AIS_Shape(aTopoReducer);

    anAisReducer->SetColor(Quantity_NOC_BISQUE);

    anAxis.SetLocation(gp_Pnt(8.0, 10.0, 0.0));
    TopoDS_Shape aTopoCone = BRepPrimAPI_MakeCone(anAxis, 3.0, 0.0, 5.0).Shape();
    Handle(AIS_Shape) anAisCone = new AIS_Shape(aTopoCone);

    anAisCone->SetColor(Quantity_NOC_CHOCOLATE);

    myOccView->getContext()->Display(anAisReducer, Standard_True);
    myOccView->getContext()->Display(anAisCone, Standard_True);
}

//#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
void occQt::points()
{
    gp_Pnt point, p2(0,0,0);
    point.SetX(100);
    point.SetY(0);
    point.SetZ(0);
    //Standard_Real myDistance=p2.Distance(point);


    TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(point);
    Handle(AIS_Shape) aisVertex =new AIS_Shape(vertex);
    aisVertex->SetColor(Quantity_NOC_ORANGE3);
    myOccView->getContext()->Display(aisVertex, Standard_True);


    vertex = BRepBuilderAPI_MakeVertex(p2);
    aisVertex =new AIS_Shape(vertex);
    aisVertex->SetColor(Quantity_NOC_SNOW);
    myOccView->getContext()->Display(aisVertex, Standard_True);

}

#include <Geom_CartesianPoint.hxx>
#include <AIS_Line.hxx>
void occQt::lines()
{
    Handle(Geom_CartesianPoint) p1 = new
        Geom_CartesianPoint(gp_Pnt(10,10,0));
    Handle(Geom_CartesianPoint) p2 = new
        Geom_CartesianPoint(gp_Pnt(10,70,0));
    Handle(AIS_Line) lineVision = new AIS_Line(p1,p2);
    myOccView->getContext()->Display(lineVision, Standard_True);
}


// Include OpenCascade libraries
 #include <Geom_BezierCurve.hxx>
 #include <BRepBuilderAPI_MakeEdge.hxx>
void occQt::splines()
{
    // Note: it seems that OpenCascade prefers
    //to start indexing control point arrays from one instead of zero :(
    // Step 1: Define control points
    TColgp_Array1OfPnt controlPoints(1, 5); // Array size 4 (1-based indexing in Open Cascade)
    controlPoints.SetValue(1, gp_Pnt(1.0, 1.0, 0.0)); // Point 1
    controlPoints.SetValue(2, gp_Pnt(2.0, 3.0, 0.0)); // Point 2
    controlPoints.SetValue(3, gp_Pnt(3.0, 0.0, 0.0)); // Point 3
    controlPoints.SetValue(4, gp_Pnt(4.0, 3.0, 0.0)); // Point 4
    controlPoints.SetValue(5, gp_Pnt(5.0, 2.0, 0.0)); // Point 5
    Handle(Geom_BezierCurve) bezierCurve = new Geom_BezierCurve(controlPoints);
    TopoDS_Edge bezierEdge = BRepBuilderAPI_MakeEdge(bezierCurve);

    Handle(AIS_Shape) curveVision = new AIS_Shape(bezierEdge);
    curveVision->SetColor(Quantity_NOC_PALEGREEN);
    myOccView->getContext()->Display(curveVision, Standard_True);

    // Assume this is initialized properly
    myOccView->fitAll();
    myOccView->redraw();
}


