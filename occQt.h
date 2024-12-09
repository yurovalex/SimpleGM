
//#ifndef OCCQT_H
//#define OCCQT_H

#pragma once

#include "ui_occQt.h"
#include <AIS_InteractiveContext.hxx>

class OccView;

//! Qt main window which include OpenCASCADE for its central widget.
class occQt : public QMainWindow
{
    Q_OBJECT

public:
    //! constructor/destructor.
    occQt(QWidget *parent = nullptr);
    ~occQt();

protected:
    //! create all the actions.
    void createActions(void);

    //! create all the menus.
    void createMenus(void);

    //! create the toolbar.
    void createToolBars(void);


private slots:
    //! show about box.
    void about(void);

    //! make box test.
    void makeBox(void);

    //! make cone test.
    void makeCone(void);


    //! make point test.
    void points(void);

    //!Lines
    void lines();

    //!Splines
    void splines();

    void bspline();




private:
    Ui::occQtClass ui;

    // wrapped the widget for occ.
    OccView* myOccView;
};

//#endif // OCCQT_H
