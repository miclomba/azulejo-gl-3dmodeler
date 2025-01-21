#ifndef _3dmodeler_userinterface_h
#define	_3dmodeler_userinterface_h

#include "config.h"

#include "Entities/Entity.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT UserInterface : public entity::Entity {
public:
    UserInterface();
    virtual ~UserInterface() = default;
    void Draw(GLint _w, GLint _h);
private:
    GLint w_ = 0;
    GLint h_ = 0;

    void DrawWindows();
    void DrawLabelAxis();

};

} // end _3dmodeler{

#endif	// _3dmodeler_userinterface_h

