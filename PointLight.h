#ifndef _3dmodeler_pointlight_h
#define	_3dmodeler_pointlight_h

#include <array>

#include "Entities/Entity.h"

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT PointLight : public entity::Entity {
public:
    PointLight();
    virtual ~PointLight() = default;
    void Draw(GLenum _renderMode);

    std::array<std::array<GLfloat, 4>, 2>& GetPosition();

    static std::string PointLightKey();

private:
    std::array<std::array<GLfloat, 4>, 2> position_;
};

} // end _3dmodeler{

#endif	// _3dmodeler_pointlight_h
