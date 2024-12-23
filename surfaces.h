#pragma once

#include <QObject>


class OccView;
class Surfaces:public QObject
{
    public:
    Surfaces(OccView* _view): myOccView{_view}
    {}

    public slots:

    //!surfaces
    //! bezier_surface
    void bezier_surface();

    //! bezier_surface_rational
    void bezier_surface_rational();

    //! surface_2boundares
    void surface_2boundares();


    //ruled_surface
    void ruled_surface();


    //!SampleSurface
    void SampleSurface();


    private:
    // wrapped the widget for occ.
    OccView* myOccView;

};
