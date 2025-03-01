
#include "occQt.h"
#include "occView.h"
#include "surfaces.h"

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
    //for surfaces
    mySurfaces = std::make_unique<Surfaces>(myOccView);

    setCentralWidget(myOccView);
    createActions();
    createMenus();
    createToolBars();
}

occQt::~occQt()
{
    delete myOccView;
}

void occQt::createActions( void )
{
    // File
    //old syntax
    //connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
    //new syntax
    connect(ui.actionExit, &QAction::triggered, this, &occQt::close);

    // View
    //connect(ui.actionZoom, SIGNAL(triggered()), myOccView, SLOT(zoom()));
    connect(ui.actionZoom, &QAction::triggered, myOccView, &OccView::zoom);


    //connect(ui.actionPan, SIGNAL(triggered()), myOccView, SLOT(pan()));
    connect(ui.actionPan, &QAction::triggered, myOccView, &OccView::pan);

    //connect(ui.actionRotate, SIGNAL(triggered()), myOccView, SLOT(rotate()));
    connect(ui.actionRotate, &QAction::triggered, myOccView, &OccView::rotate);

    //connect(ui.actionReset, SIGNAL(triggered()), myOccView, SLOT(reset()));
    connect(ui.actionReset, &QAction::triggered, myOccView, &OccView::reset);
    //connect(ui.actionFitAll, SIGNAL(triggered()), myOccView, SLOT(fitAll()));
    connect(ui.actionFitAll, &QAction::triggered, myOccView, &OccView::fitAll);
    //connect(ui.actionDeleteAll, SIGNAL(triggered()), myOccView, SLOT(deleteAll()));
    connect(ui.actionDeleteAll, &QAction::triggered, myOccView, &OccView::deleteAll);

    //2D
    //connect(ui.actionPoints, SIGNAL(triggered()), this, SLOT(points()));
    connect(ui.actionPoints, &QAction::triggered, this, &occQt::points);
    //connect(ui.actionLines, SIGNAL(triggered()), this, SLOT(lines()));
    connect(ui.actionLines, &QAction::triggered, this, &occQt::lines);
    //connect(ui.actionSplines, SIGNAL(triggered()), this, SLOT(splines()));
    connect(ui.actionSplines, &QAction::triggered, this, &occQt::splines);
    //connect(ui.actionBspline, SIGNAL(triggered()), this, SLOT(bspline()));
    connect(ui.actionBspline, &QAction::triggered, this, &occQt::bspline);

    //Surfaces
    connect(ui.actionBezier_surface, &QAction::triggered, mySurfaces.get(), &Surfaces::bezier_surface);
    connect(ui.actionBezier_surface_rational, &QAction::triggered, mySurfaces.get(), &Surfaces::bezier_surface_rational);
    connect(ui.actionSurface_2boundares, &QAction::triggered, mySurfaces.get(), &Surfaces::surface_2boundares);
    connect(ui.actionRuled_surface, &QAction::triggered, mySurfaces.get(), &Surfaces::ruled_surface);
    connect(ui.actionSampleSurface, &QAction::triggered, mySurfaces.get(), &Surfaces::SampleSurface);


    // Primitive
    //connect(ui.actionBox, SIGNAL(triggered()), this, SLOT(makeBox()));
    connect(ui.actionBox, &QAction::triggered, this, &occQt::makeBox);
    //connect(ui.actionCone, SIGNAL(triggered()), this, SLOT(makeCone()));
    connect(ui.actionCone, &QAction::triggered, this, &occQt::makeCone);

    // Help
    //connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.actionAbout, &QAction::triggered, this, &occQt::about);
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
    aToolBar->addAction(ui.actionBspline);

    aToolBar = addToolBar(tr("Help"));
    aToolBar->addAction(ui.actionAbout);

    aToolBar = addToolBar(tr("&Surface"));
    aToolBar->setAllowedAreas(Qt::LeftToolBarArea);

    aToolBar->addAction(ui.actionBezier_surface);
    aToolBar->addAction(ui.actionBezier_surface_rational);
    aToolBar->addAction(ui.actionSurface_2boundares);
    aToolBar->addAction(ui.actionRuled_surface);
    aToolBar->addAction(ui.actionSampleSurface);
    this->addToolBar(Qt::LeftToolBarArea, aToolBar);
}

void occQt::about()
{
    QMessageBox::about(this, tr("About SimpleGM for Qt"),
        tr("<h2>occQt 2.2</h2>"
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
    TColgp_Array1OfPnt controlPoints(1, 6); // Array size 6 (1-based indexing in Open Cascade)
    controlPoints.SetValue(1, gp_Pnt(1.0, 1.0, 0.0)); // Point 1
    controlPoints.SetValue(2, gp_Pnt(2.0, 3.0, 0.0)); // Point 2
    controlPoints.SetValue(3, gp_Pnt(3.0, 0.0, 0.0)); // Point 3
    controlPoints.SetValue(4, gp_Pnt(4.0, 3.0, 0.0)); // Point 4
    controlPoints.SetValue(5, gp_Pnt(5.0, 2.0, 0.0)); // Point 5
     controlPoints.SetValue(6, gp_Pnt(15.0, 5.0, 5.0)); // Point 6
    Handle(Geom_BezierCurve) bezierCurve = new Geom_BezierCurve(controlPoints);
    TopoDS_Edge bezierEdge = BRepBuilderAPI_MakeEdge(bezierCurve);

    Handle(AIS_Shape) curveVision = new AIS_Shape(bezierEdge);
    curveVision->SetWidth(3.0);
    curveVision->SetColor(Quantity_NOC_WHITE);
    myOccView->getContext()->Display(curveVision, Standard_True);

    // Assume this is initialized properly
    myOccView->fitAll();
    myOccView->redraw();
}

#include <Geom_BSplineCurve.hxx>


void occQt::bspline()
{
    // -------------------------------------------------------------------------------------------------------------- //
    // Define the array of control points
    // -------------------------------------------------------------------------------------------------------------- //

    TColgp_Array1OfPnt P(1, 7);
    P(1) = gp_Pnt(0.00, 0.0, 0.0);
    P(2) = gp_Pnt(0.25, -0.5, 0.0);
    P(3) = gp_Pnt(0.50, 0.0, 0.0);
    P(4) = gp_Pnt(0.75, 0.0, 0.0);
    P(5) = gp_Pnt(1.00, 0.0, 0.0);
    P(6) = gp_Pnt(0.50, 0.5, 0.0);
    P(7) = gp_Pnt(0.00, 0.5, 0.0);

    // -------------------------------------------------------------------------------------------------------------- //
    // Define the knot vector
    // -------------------------------------------------------------------------------------------------------------- //

    // Maximum index of the control points (counting from zero)
    Standard_Integer n = P.Length() - 1;

    // Define the order of the basis polynomials
    // Linear (p = 1), Quadratic (p = 2), Cubic (p = 3), etc.
    // Set p = n (number of control points minus one) to obtain Bezier basis polynomials
    Standard_Integer p = 3;

    // Define of the knot vector (clamped spline)
    // p+1 zeros, n-p equispaced points between 0 and 1, and p+1 ones. N+1=n-p+2 distinct values
    Standard_Integer N = n - p + 2 - 1;
    TColStd_Array1OfReal U_values(0, N);
    TColStd_Array1OfInteger U_mults(0, N);

    for (int i = 0; i <= N; ++i) {

        // Set the knot values
        U_values(i) = double(i) / double(N);

        // Set the knot multiplicities
        if (i == 0 || i == N) { U_mults(i) = p+1; }
        else { U_mults(i) = 1; }

    }


    // -------------------------------------------------------------------------------------------------------------- //
    // Define the geometry and topology of a B-Spline curve
    // -------------------------------------------------------------------------------------------------------------- //

    // Create the geometry and reference it by handle
    Handle(Geom_BSplineCurve) BSplineGeo = new Geom_BSplineCurve(P, U_values, U_mults, p);

    // Define the topology of the B-Spline curve using the BRepBuilderAPI
    TopoDS_Edge BSplineEdge = BRepBuilderAPI_MakeEdge(BSplineGeo);


    Handle(AIS_Shape) curveVision = new AIS_Shape(BSplineEdge);
    curveVision->SetColor(Quantity_NOC_LIGHTCYAN);
    myOccView->getContext()->Display(curveVision, Standard_True);

    // Assume this is initialized properly
    myOccView->fitAll();
    myOccView->redraw();
}





