#ifndef _3dmodeler_grid_h
#define	_3dmodeler_grid_h

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT Grid {
public:
    Grid();
    virtual ~Grid() = default;
    void display(GLenum _mode);
    void displayControlPoints(GLenum _mode);

private:
    friend class MeshEditor;

    void initGridPoints();
    void makeTexImage1();
    void makeTexImage2();
    void changeTextures();

    //Four sets of four points def by (u,v,'xyz')
    GLfloat controlPoints_[4][4][3];
    GLfloat texturePoints_[2][2][2];

    GLint curTexture_;

    GLint uOrder_;
    GLint uRangeLow_;
    GLint uRangeHigh_;
    GLint uStride_;

    GLint vOrder_;
    GLint vRangeLow_;
    GLint vRangeHigh_;
    GLint vStride_;

    GLint gridSubdivs_;

    GLfloat gold_Ka_[4];
    GLfloat gold_Kd_[4];
    GLfloat gold_Ks_[4];
    GLfloat gold_Ke_;
    GLfloat silver_Ka_[4];
    GLfloat silver_Kd_[4];
    GLfloat silver_Ks_[4];
    GLfloat silver_Ke_;

    static const int IMG_WIDTH = 64;
    static const int IMG_HEIGHT = 64;

    GLubyte image_[IMG_WIDTH * IMG_HEIGHT * 3];
};

} // end _3dmodeler{

#endif	// _3dmodeler_grid_h

