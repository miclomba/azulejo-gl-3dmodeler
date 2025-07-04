/**
 * @file GLProjectionInfo.h
 * @brief Declaration of the GLProjectionInfo class for managing window properties in the 3D modeler application.
 */

#ifndef _3dmodeler_gl_projection_info_h
#define _3dmodeler_gl_projection_info_h

#include <array>
#include <memory>

#include "Entities/Entity.h"
#include "configuration/config.h"

namespace _3dmodeler
{

    /**
     * @class GLProjectionInfo
     * @brief A class for managing the properties of the game window in the 3D modeler application.
     *
     * This class provides methods for retrieving and modifying window dimensions and projection matrices.
     */
    class _3DMODELER_DLL_EXPORT GLProjectionInfo : public entity::Entity
    {
    public:
        /**
         * @brief Default constructor for GLProjectionInfo.
         */
        GLProjectionInfo();

        /**
         * @brief Destructor for GLProjectionInfo.
         */
        virtual ~GLProjectionInfo();

        GLProjectionInfo(const GLProjectionInfo &) = delete;
        GLProjectionInfo(GLProjectionInfo &&) = delete;
        GLProjectionInfo &operator=(const GLProjectionInfo &) = delete;
        GLProjectionInfo &operator=(GLProjectionInfo &&) = delete;

        /**
         * @brief Get the width of the window.
         * @return The window width as a GLint.
         */
        GLint GetWidth() const;

        /**
         * @brief Get the height of the window.
         * @return The window height as a GLint.
         */
        GLint GetHeight() const;

        /**
         * @brief Get the orthographic projection matrix.
         * @return A constant reference to the 4x4 orthographic projection matrix.
         */
        const std::array<GLfloat, 16> &GetProjOrthoMatrix() const;

        /**
         * @brief Get the perspective projection matrix.
         * @return A constant reference to the 4x4 perspective projection matrix.
         */
        const std::array<GLfloat, 16> &GetProjPerspectiveMatrix() const;

        /**
         * @brief Set the width of the window.
         * @param w The new width value.
         */
        void SetWidth(const GLint w);

        /**
         * @brief Set the height of the window.
         * @param h The new height value.
         */
        void SetHeight(const GLint h);

        /**
         * @brief Set the entire orthographic projection matrix.
         * @param projOrtho The new orthographic projection matrix.
         */
        void SetProjOrthoMatrix(std::array<GLfloat, 16> projOrtho);

        /**
         * @brief Set the entire perspective projection matrix.
         * @param projPerspective The new perspective projection matrix.
         */
        void SetProjPerspectiveMatrix(std::array<GLfloat, 16> projPerspective);

        /**
         * @brief Set a specific value in the orthographic projection matrix.
         * @param val The value to set.
         * @param index The index position in the matrix.
         */
        void SetProjOrthoMatrix(const GLfloat val, const int index);

        /**
         * @brief Set a specific value in the perspective projection matrix.
         * @param val The value to set.
         * @param index The index position in the matrix.
         */
        void SetProjPerspectiveMatrix(const GLfloat val, const int index);

    private:
        GLint w_;                                 /**< The width of the window. */
        GLint h_;                                 /**< The height of the window. */
        std::array<GLfloat, 16> projOrtho_;       /**< The 4x4 orthographic projection matrix. */
        std::array<GLfloat, 16> projPerspective_; /**< The 4x4 perspective projection matrix. */
    };

} // end _3dmodeler

#endif // _3dmodeler_gl_projection_info_h
