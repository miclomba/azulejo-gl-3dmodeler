/**
 * @file GLEntity.h
 * @brief Declaration of the GLEntity class for managing 3D model transformations.
 */

#ifndef _3dmodeler_glentity_h
#define _3dmodeler_glentity_h

#include "configuration/config.h"

#include "Entities/Entity.h"
#include "test_filesystem_adapters/ContainerResource2D.h"

namespace _3dmodeler
{

    using Resource2DGLfloat = ContainerResource2D<GLfloat>;

    /**
     * @class GLEntity
     * @brief A class for representing a 3D model entity with transformation capabilities.
     *
     * This class provides functionality for handling 3D transformations such as scaling,
     * translation, and rotation using matrix operations.
     */
    class _3DMODELER_DLL_EXPORT GLEntity : public entity::Entity
    {
    public:
        /**
         * @brief Default constructor for the GLEntity class.
         */
        GLEntity();

        /**
         * @brief Destructor for the GLEntity class.
         */
        ~GLEntity();

        /**
         * @brief Copy constructor.
         * @param other The GLEntity instance to copy from.
         */
        GLEntity(const GLEntity &other);

        /**
         * @brief Move constructor.
         * @param other The GLEntity instance to move from.
         */
        GLEntity(GLEntity &&other);

        /**
         * @brief Copy assignment operator.
         * @param other The GLEntity instance to copy from.
         * @return Reference to the updated instance.
         */
        GLEntity &operator=(const GLEntity &other);

        /**
         * @brief Move assignment operator.
         * @param other The GLEntity instance to move from.
         * @return Reference to the updated instance.
         */
        GLEntity &operator=(GLEntity &&other);

        /**
         * @brief Draw the 3D entity.
         */
        virtual void Draw();

        /**
         * @brief Get the transformation matrix describing the entity's geometry.
         * @return Reference to the frame matrix.
         */
        Resource2DGLfloat &GetFrame();

        /**
         * @brief Get the scale transformation matrix.
         * @return A constant reference to the scale matrix.
         */
        const Resource2DGLfloat &SMatrix() const;

        /**
         * @brief Get the translation transformation matrix.
         * @return A constant reference to the translation matrix.
         */
        const Resource2DGLfloat &TMatrix() const;

        /**
         * @brief Get the rotation transformation matrix.
         * @return A constant reference to the rotation matrix.
         */
        const Resource2DGLfloat &RMatrix() const;

        /**
         * @brief Set a value in the frame matrix.
         * @param i Row index.
         * @param j Column index.
         * @param val Value to set.
         */
        void SetFrame(int i, int j, GLfloat val);

        /**
         * @brief Set the entire frame matrix.
         * @param frame The frame matrix to set.
         */
        void SetFrame(const Resource2DGLfloat &frame);

    protected:
        Resource2DGLfloat S_; /**< Scale transformation matrix. */
        Resource2DGLfloat T_; /**< Translation transformation matrix. */
        Resource2DGLfloat R_; /**< Rotation transformation matrix. */

    private:
        Resource2DGLfloat frame_; /**< Matrix representing entity geometry. */
    };

} // end namespace _3dmodeler

#endif // _3dmodeler_glentity_h
