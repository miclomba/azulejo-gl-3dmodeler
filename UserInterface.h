#ifndef _3dmodeler_userinterface_h
#define	_3dmodeler_userinterface_h

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT UserInterface {
public:
    virtual ~UserInterface() = default;
    void display(GLint _w, GLint _h);
private:
    friend class MeshEditor;
    friend class Modeler;

    GLint w_ = 0;
    GLint h_ = 0;

    void drawWindows();
    void drawLabelAxis();

};

} // end _3dmodeler{

#endif	// _3dmodeler_userinterface_h

