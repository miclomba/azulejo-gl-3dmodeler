/**
 * @file Grid.h
 * @brief Declaration of the Grid class which represents a 3D surface with control points and texture mapping.
 */

#ifndef _3dmodeler_grid_h
#define _3dmodeler_grid_h

#include <array>

#include "Entities/Entity.h"

#include "configuration/config.h"

namespace _3dmodeler
{

    /**
     * @class Grid
     * @brief A class representing a 3D surface with texture and control points.
     *
     * The Grid class provides functionality to draw a 3D surface using control points and textures.
     * It allows setting control points, changing textures, and rendering the grid.
     */
    class _3DMODELER_DLL_EXPORT Grid : public entity::Entity
    {
    public:
        /**
         * @brief Default constructor for the Grid class.
         */
        Grid();

        /**
         * @brief Default destructor for the Grid class.
         */
        virtual ~Grid() = default;

        /**
         * @brief Draw the grid using the specified rendering mode.
         * @param _mode The OpenGL rendering mode.
         */
        void Draw(GLenum _mode);

        /**
         * @brief Draw the control points of the grid.
         * @param _mode The OpenGL rendering mode.
         */
        void DrawControlPoints(GLenum _mode);

        /**
         * @brief Change the current texture of the grid.
         */
        void ChangeTextures();

        /**
         * @brief Set a specific control point value in the grid.
         * @param val The value to be set.
         * @param i The first index for control points.
         * @param j The second index for control points.
         * @param k The third index for control points.
         */
        void SetControlPoint(const GLfloat val, const int i, const int j, const int k);

        /**
         * @brief Get the unique key for the grid.
         * @return The grid key as a string.
         */
        static std::string GridKey();

    private:
        /**
         * @brief Create the first texture image.
         */
        void MakeTexImage1();

        /**
         * @brief Create the second texture image.
         */
        void MakeTexImage2();

        // Four sets of four points defined by (u,v,'xyz')
        std::array<std::array<std::array<GLfloat, 3>, 4>, 4> controlPoints_; /**< Control points for the grid. */
        std::array<std::array<std::array<GLfloat, 2>, 2>, 2> texturePoints_; /**< Texture points for the grid. */

        GLint curTexture_ = 1; /**< Current active texture. */

        GLint uOrder_ = 4;     /**< Order of the grid in the u-direction. */
        GLint uRangeLow_ = 0;  /**< Lower bound for the u-direction. */
        GLint uRangeHigh_ = 1; /**< Upper bound for the u-direction. */
        GLint uStride_;        /**< Stride value for the u-direction. */

        GLint vOrder_ = 4;     /**< Order of the grid in the v-direction. */
        GLint vRangeLow_ = 0;  /**< Lower bound for the v-direction. */
        GLint vRangeHigh_ = 1; /**< Upper bound for the v-direction. */
        GLint vStride_;        /**< Stride value for the v-direction. */

        GLint gridSubdivs_ = 16.0f; /**< Number of subdivisions in the grid. */

        std::array<GLfloat, 4> gold_Ka_ = {0.24725f, 0.1995f, 0.0745f, 1.0f};      /**< Ambient reflection properties for gold material. */
        std::array<GLfloat, 4> gold_Kd_ = {0.75164f, 0.60648f, 0.22648f, 1.0f};    /**< Diffuse reflection properties for gold material. */
        std::array<GLfloat, 4> gold_Ks_ = {0.628281f, 0.555802f, 0.366065f, 1.0f}; /**< Specular reflection properties for gold material. */
        GLfloat gold_Ke_ = 41.2f;                                                  /**< Emissive property for gold material. */

        std::array<GLfloat, 4> silver_Ka_ = {0.05f, 0.05f, 0.05f, 1.0f}; /**< Ambient reflection properties for silver material. */
        std::array<GLfloat, 4> silver_Kd_ = {0.4f, 0.4f, 0.4f, 1.0f};    /**< Diffuse reflection properties for silver material. */
        std::array<GLfloat, 4> silver_Ks_ = {0.7f, 0.7f, 0.7f, 1.0f};    /**< Specular reflection properties for silver material. */
        GLfloat silver_Ke_ = 12.0f;                                      /**< Emissive property for silver material. */

        static const int IMG_WIDTH = 64;  /**< Texture image width. */
        static const int IMG_HEIGHT = 64; /**< Texture image height. */

        std::array<GLubyte, IMG_WIDTH * IMG_HEIGHT * 3> image_; /**< Storage for texture image data. */
    };

} // end namespace _3dmodeler

#endif // _3dmodeler_grid_h
