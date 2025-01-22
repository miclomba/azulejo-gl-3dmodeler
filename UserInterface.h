/**
 * @file UserInterface.h
 * @brief Declaration of the UserInterface class which represents a simple user interface in the 3D modeler application.
 */

#ifndef _3dmodeler_userinterface_h
#define _3dmodeler_userinterface_h

#include "config.h"
#include "Entities/Entity.h"

namespace _3dmodeler {

/**
 * @class UserInterface
 * @brief A class representing a simple user interface for the 3D modeler application.
 *
 * This class provides functionality to render UI elements such as windows and axis labels.
 */
class _3DMODELER_DLL_EXPORT UserInterface : public entity::Entity {
public:
    /**
     * @brief Default constructor for the UserInterface class.
     */
    UserInterface();

    /**
     * @brief Default destructor for the UserInterface class.
     */
    virtual ~UserInterface() = default;

    /**
     * @brief Draw the user interface.
     * @param _w Width of the UI.
     * @param _h Height of the UI.
     */
    void Draw(GLint _w, GLint _h);

    /**
     * @brief Get the unique key associated with the user interface.
     * @return The UI key as a string.
     */
    static std::string UserInterfaceKey();

private:
    GLint w_ = 0; /**< Width of the user interface. */
    GLint h_ = 0; /**< Height of the user interface. */

    /**
     * @brief Draw the windows of the UI.
     */
    void DrawWindows();

    /**
     * @brief Draw axis labels on the UI.
     */
    void DrawLabelAxis();
};

} // end namespace _3dmodeler

#endif // _3dmodeler_userinterface_h
