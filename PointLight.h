#ifndef _3dmodeler_pointlight_h
#define	_3dmodeler_pointlight_h

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT PointLight {
public:
    PointLight();
    virtual ~PointLight() = default;
    void display(GLenum _renderMode);

private:
    friend class MeshEditor;
    GLfloat position_[2][4];
};

} // end _3dmodeler{

#endif	// _3dmodeler_pointlight_h
