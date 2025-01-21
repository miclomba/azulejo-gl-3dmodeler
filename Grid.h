#ifndef _3dmodeler_grid_h
#define	_3dmodeler_grid_h

#include <array>

#include "config.h"

#include "Entities/Entity.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT Grid : public entity::Entity {
public:
    Grid();
    virtual ~Grid() = default;
    void Draw(GLenum _mode);
    void DrawControlPoints(GLenum _mode);
    void ChangeTextures();

    void SetControlPoint(const GLfloat val, const int i, const int j, const int k);

    static std::string GridKey();

private:
    void InitGridPoints();
    void MakeTexImage1();
    void MakeTexImage2();

    //Four sets of four points def by (u,v,'xyz')
    std::array<std::array<std::array<GLfloat, 3>, 4>, 4> controlPoints_;
    std::array<std::array<std::array<GLfloat, 2>, 2>, 2> texturePoints_;

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

    std::array<GLfloat, 4> gold_Ka_;
    std::array<GLfloat, 4> gold_Kd_;
    std::array<GLfloat, 4> gold_Ks_;
    GLfloat gold_Ke_;
    std::array<GLfloat, 4> silver_Ka_;
    std::array<GLfloat, 4> silver_Kd_;
    std::array<GLfloat, 4> silver_Ks_;
    GLfloat silver_Ke_;

    static const int IMG_WIDTH = 64;
    static const int IMG_HEIGHT = 64;

    std::array<GLubyte, IMG_WIDTH* IMG_HEIGHT * 3> image_;
};

} // end _3dmodeler{

#endif	// _3dmodeler_grid_h

