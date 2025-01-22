/**
 * @file PointLight.h
 * @brief Declaration of the PointLight class which represents point light sources in the 3D modeler application.
 */

#ifndef _3dmodeler_pointlight_h
#define _3dmodeler_pointlight_h

#include <array>

#include "Entities/Entity.h"
#include "config.h"

namespace _3dmodeler {

/**
 * @class PointLight
 * @brief A class representing a point light source in the 3D scene.
 *
 * The PointLight class allows for the positioning and rendering of a point light source.
 */
class _3DMODELER_DLL_EXPORT PointLight : public entity::Entity {
public:
    /**
     * @brief Default constructor for the PointLight class.
     */
    PointLight();

    /**
     * @brief Default destructor for the PointLight class.
     */
    virtual ~PointLight() = default;

    /**
     * @brief Draw the point light in the scene.
     * @param _renderMode The OpenGL rendering mode to use.
     */
    void Draw(GLenum _renderMode);

    /**
     * @brief Get the position of the point light.
     * @return Reference to a 2D array representing the position of the light.
     */
    std::array<std::array<GLfloat, 4>, 2>& GetPosition();

    /**
     * @brief Get the unique key associated with the point light.
     * @return The key as a string.
     */
    static std::string PointLightKey();

private:
    std::array<std::array<GLfloat, 4>, 2> position_; /**< Position of the point light. */
};

} // end namespace _3dmodeler

#endif // _3dmodeler_pointlight_h
