#include <AIS_InteractiveContext.hxx>
#include <Geom_BezierSurface.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Face.hxx>
#include <BRep_Tool.hxx>
#include <AIS_Shape.hxx>

#include "surfaces.h"
#include "occView.h"

void Surfaces::bezier_surface()
{
    // -------------------------------------------------------------------------------------------------------------- //
    // Define the array of control points
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the array
    Standard_Integer rowLower = 1, rowUpper = 5;
    Standard_Integer colLower = 1, colUpper = 3;
    TColgp_Array2OfPnt P(rowLower, rowUpper, colLower, colUpper);

    // First row
    P(1, 1) = gp_Pnt(0.00, 0.0, 0.0);
    P(2, 1) = gp_Pnt(0.25, 0.0, 0.0);
    P(3, 1) = gp_Pnt(0.50, 0.0, 0.0);
    P(4, 1) = gp_Pnt(0.75, 0.0, 0.0);
    P(5, 1) = gp_Pnt(1.00, 0.0, 0.0);

    // Second row
    P(1, 2) = gp_Pnt(0.00, 0.5, 0.0);
    P(2, 2) = gp_Pnt(0.25, 0.5, 1.0);
    P(3, 2) = gp_Pnt(0.50, 0.5, 1.0);
    P(4, 2) = gp_Pnt(0.75, 0.5, 1.0);
    P(5, 2) = gp_Pnt(1.00, 0.5, 0.0);

    // Third row
    P(1, 3) = gp_Pnt(0.00, 1.0, 0.0);
    P(2, 3) = gp_Pnt(0.25, 1.0, 0.0);
    P(3, 3) = gp_Pnt(0.50, 1.0, 0.0);
    P(4, 3) = gp_Pnt(0.75, 1.0, 0.0);
    P(5, 3) = gp_Pnt(1.00, 1.0, 0.0);


    // -------------------------------------------------------------------------------------------------------------- //
    // Define the geometry and topology of a Bezier surface
    // -------------------------------------------------------------------------------------------------------------- //

    // Define the geometry of a Bezier surface referenced by handle
    Handle(Geom_BezierSurface) BezierGeo = new Geom_BezierSurface(P);

    // Define the topology of the Bezier surface using the BRepBuilderAPI
    TopoDS_Face BezierFace = BRepBuilderAPI_MakeFace(BezierGeo, 0);

    // Get the geometric surface from the topological face and check the bounds in parametric space [Optional]
    Handle(Geom_Surface) BezierGeo_bis = BRep_Tool::Surface (BezierFace);
    double u_lower, u_upper, v_lower, v_upper;
    BezierGeo_bis->Bounds(u_lower, u_upper, v_lower, v_upper);

    // Create a TopoDS_Shape object
    TopoDS_Shape open_cascade_model = BezierFace;

    Handle(AIS_Shape) surfaceVision = new AIS_Shape(open_cascade_model);
    surfaceVision->SetColor(Quantity_NOC_MATRABLUE);

    myOccView->getContext()->Display(surfaceVision, Standard_True);
    myOccView->fitAll();
}

#include <TopoDS.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>

void Surfaces::bezier_surface_rational()
{
    // -------------------------------------------------------------------------------------------------------------- //
    // Define the array of control points
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare the array
    Standard_Integer rowLower = 1, rowUpper = 3;
    Standard_Integer colLower = 1, colUpper = 2;
    TColgp_Array2OfPnt P(rowLower, rowUpper, colLower, colUpper);

    // First row
    P(1, 1) = gp_Pnt(1.0, 0.0, 0.0);
    P(2, 1) = gp_Pnt(1.0, 1.0, 0.0);
    P(3, 1) = gp_Pnt(0.0, 1.0, 0.0);

    // Second row
    P(1, 2) = gp_Pnt(1.0, 0.0, 2.0);
    P(2, 2) = gp_Pnt(1.0, 1.0, 2.0);
    P(3, 2) = gp_Pnt(0.0, 1.0, 2.0);


    // -------------------------------------------------------------------------------------------------------------- //
    // Define the array of control point weights
    // -------------------------------------------------------------------------------------------------------------- //

    // Declare array
    TColStd_Array2OfReal W(rowLower, rowUpper, colLower, colUpper);

    // First row
    W(1, 1) = 1.;
    W(2, 1) = sqrt(2.)/2.;      // This choice of weight leads to a circular sector of 90 degrees
    W(3, 1) = 1.;

    // Second row
    W(1, 2) = 1.;
    W(2, 2) = sqrt(2.)/2.;      // This choice of weight leads to a circular sector of 90 degrees
    W(3, 2) = 1.;


    // -------------------------------------------------------------------------------------------------------------- //
    // Define the geometry and topology of a rational Bezier surface patch (90 degrees)
    // -------------------------------------------------------------------------------------------------------------- //

    // Create the  geometry and reference it by handle
    Handle(Geom_BezierSurface) BezierGeo = new Geom_BezierSurface(P, W);

    // Define the topology of the Bezier surface using the BRepBuilderAPI
    TopoDS_Face BezierFace = BRepBuilderAPI_MakeFace(BezierGeo, 0.);


    // -------------------------------------------------------------------------------------------------------------- //
    // Define the geometry and topology of a rational Bezier surface patch
    // -------------------------------------------------------------------------------------------------------------- //

    // Get the value of pi
    const double pi = M_PI;

    // Rotate the Bezier patch 90 degrees around the Z-axis
    gp_Trsf myTransformation;                                           // Declare a transformation object
    gp_Ax1 axisOfRotation = gp::OZ();                                   // Set Z as the axis of rotation
    Standard_Real angleOfRotation = pi/2;                               // Set the angle of rotation
    myTransformation.SetRotation(axisOfRotation, angleOfRotation);      // Set the transformation as a rotation
    BRepBuilderAPI_Transform BRepT1(BezierFace, myTransformation);      // Apply the rotation to the Bezier patch
    TopoDS_Shape temp = BRepT1.Shape();                                 // Retrieve the rotated bezier patch
    TopoDS_Face BezierRotatedFace = TopoDS::Face(temp);                 // Cast the TopoDS_Shape into a TopoDS_Face

    // Make a compound with the two bezier patches
    TopoDS_Compound myCompound;                                         // Declare the TopoDS_Compound object
    BRep_Builder myBuilder;                                             // Declare the compound builder object
    myBuilder.MakeCompound (myCompound);                                // Start the compound creation
    myBuilder.Add (myCompound, BezierFace);                             // Add the original Bezier patch
    myBuilder.Add (myCompound, BezierRotatedFace);                      // Add the rotated Bezier patch

    // Mirror the two Bezier patches in the XZ plane
    gp_Ax2 planeOfReflexion = gp::ZOX();                                // Set the XY plane as the plane of symmetry
    myTransformation.SetMirror(planeOfReflexion);                       // Set the transformation as a reflection
    BRepBuilderAPI_Transform BRepT2(myCompound, myTransformation);      // Apply the mirroring to the compound
    temp = BRepT2.Shape();                                              // Retrieve the rotated bezier patch
    TopoDS_Compound CylinderMirrored = TopoDS::Compound(temp);          // Cast the TopoDS_Shape into a TopoDS_Compound
    myBuilder.Add (myCompound, CylinderMirrored);                       // Add the mirrored patches to the compound

    // Create a TopoDS_Shape object to
    TopoDS_Shape open_cascade_model = myCompound;


    Handle(AIS_Shape) surfaceVision = new AIS_Shape(open_cascade_model);
    surfaceVision->SetColor(Quantity_NOC_GREENYELLOW);
    myOccView->getContext()->Display(surfaceVision, Standard_True);
    myOccView->fitAll();

}

#include <GeomFill_BezierCurves.hxx>
#include <Geom_BezierCurve.hxx>

void Surfaces::surface_2boundares()
{
    // -------------------------------------------------------------------------------------------------------------- //
    // Define the boundaries of the domain
    // -------------------------------------------------------------------------------------------------------------- //

    // The domain is defined by 2 contiguous Bezier curves
    // Each Bezier curve is constructed from an array of control points and it is referenced by handle

    // Boundary 1
    TColgp_Array1OfPnt P_upper(1, 4);
    P_upper(1) = gp_Pnt(0.00, 0.0, 0.0);
    P_upper(2) = gp_Pnt(0.33, 1.0, 0.5);
    P_upper(3) = gp_Pnt(0.66, 1.0, -0.5);
    P_upper(4) = gp_Pnt(1.00, 0.0, 0.0);
    Handle(Geom_BezierCurve) bezier_upper = new Geom_BezierCurve(P_upper);

    // Boundary 2
    TColgp_Array1OfPnt P_lower(1, 4);
    P_lower(1) = bezier_upper->Pole(1);                                     // Conforming corner | same as P_upper(1)
    P_lower(2) = gp_Pnt(0.33, -1.00, -0.50);
    P_lower(3) = gp_Pnt(0.66, -1.00, 0.50);
    P_lower(4) = bezier_upper->Pole(bezier_upper->NbPoles());               // Conforming corner | same as P_upper(3)
    Handle(Geom_BezierCurve) bezier_lower = new Geom_BezierCurve(P_lower);

    // -------------------------------------------------------------------------------------------------------------- //
    // Create a Coons patch defined by its boundaries
    // -------------------------------------------------------------------------------------------------------------- //

    // Create the Bezier surface from the boundaries and a filling style
    // Styles available: 1) GeomFill_CoonsStyle 2) GeomFill_StretchStyle 3) GeomFill_CurvedStyle
    GeomFill_BezierCurves makeBezierSurfGeo(bezier_upper, bezier_lower, GeomFill_CoonsStyle);
    Handle(Geom_BezierSurface) BezierSurfGeo = makeBezierSurfGeo.Surface();

    // Define the topology of the Bezier surface using the BRepBuilderAPI
    TopoDS_Face BezierSurfTopo = BRepBuilderAPI_MakeFace(BezierSurfGeo, 0.);

    // Create a TopoDS_Shape object
    TopoDS_Shape open_cascade_model = BezierSurfTopo;
    Handle(AIS_Shape) surfaceVision = new AIS_Shape(open_cascade_model);
    surfaceVision->SetColor(Quantity_NOC_MATRAGRAY);

    myOccView->getContext()->Display(surfaceVision, Standard_True);
    myOccView->fitAll();
}

#include <GeomFill.hxx>
#include <Geom_BSplineSurface.hxx>
void Surfaces::ruled_surface()
{
    /*
     * This demonstration script shows how to create a ruled surface between 2 curves
     * The ruled surface is generated using GeomFill()
     * The output from GeomFill() seems to be the same as the output from GeomFill_BezierCurves/GeomFill_BSplineCurves
     *
     * Author: Roberto Agromayor
     * Data: December 2019
     *
     * */


    // -------------------------------------------------------------------------------------------------------------- //
    // Define the boundaries of the domain
    // -------------------------------------------------------------------------------------------------------------- //

    // The domain is defined by 2 contiguous Bezier curves
    // Each Bezier curve is constructed from an array of control points and it is referenced by handle

    // Boundary 1
    TColgp_Array1OfPnt P_upper(1, 4);
    P_upper(1) = gp_Pnt(0.00, 0.0, 0.0);
    P_upper(2) = gp_Pnt(0.33, 1.0, 0.5);
    P_upper(3) = gp_Pnt(0.66, 1.0, -0.5);
    P_upper(4) = gp_Pnt(1.00, 0.0, 0.0);
    Handle(Geom_BezierCurve) bezier_upper = new Geom_BezierCurve(P_upper);

    // Boundary 2
    TColgp_Array1OfPnt P_lower(1, 4);
    P_lower(1) = bezier_upper->Pole(1);                                     // Conforming corner | same as P_upper(1)
    P_lower(2) = gp_Pnt(0.33, -1.00, -0.50);
    P_lower(3) = gp_Pnt(0.66, -1.00, 0.50);
    P_lower(4) = bezier_upper->Pole(bezier_upper->NbPoles());               // Conforming corner | same as P_upper(3)
    Handle(Geom_BezierCurve) bezier_lower = new Geom_BezierCurve(P_lower);


    // -------------------------------------------------------------------------------------------------------------- //
    // Create a Coons patch defined by its boundaries
    // -------------------------------------------------------------------------------------------------------------- //

    // Create the ruled surface using the GeomFill package
    Handle(Geom_Surface) RuledSurfaceGeo = GeomFill().Surface(bezier_upper, bezier_lower);

    // Cast the Geom_Surface to Geom_BSpline to access its methods if desired [Optional]
    Handle(Geom_BSplineSurface) temp = Handle(Geom_BSplineSurface)::DownCast(RuledSurfaceGeo);

    // Define the topology of the ruled surface using the BRepBuilderAPI
    TopoDS_Face RuledSurfaceFace = BRepBuilderAPI_MakeFace(RuledSurfaceGeo, 0.);

    // Create a TopoDS_Shape object to
    TopoDS_Shape open_cascade_model = RuledSurfaceFace;

    Handle(AIS_Shape) surfaceVision = new AIS_Shape(open_cascade_model);
    surfaceVision->SetColor(Quantity_NOC_BISQUE);

    myOccView->getContext()->Display(surfaceVision, Standard_True);
    myOccView->fitAll();
}

