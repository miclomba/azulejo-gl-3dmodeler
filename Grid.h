/**
 * @file Grid.h
 * @brief Declaration of the Grid class which represents a 3D surface with control points and texture mapping.
 */

#ifndef _3dmodeler_grid_h
#define _3dmodeler_grid_h

#include <array>

#include "configuration/config.h"
#include "Entities/Entity.h"

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
         * @brief Initialize the grid's control points.
         */
        void InitGridPoints();

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

        GLint curTexture_; /**< Current active texture. */

        GLint uOrder_;     /**< Order of the grid in the u-direction. */
        GLint uRangeLow_;  /**< Lower bound for the u-direction. */
        GLint uRangeHigh_; /**< Upper bound for the u-direction. */
        GLint uStride_;    /**< Stride value for the u-direction. */

        GLint vOrder_;     /**< Order of the grid in the v-direction. */
        GLint vRangeLow_;  /**< Lower bound for the v-direction. */
        GLint vRangeHigh_; /**< Upper bound for the v-direction. */
        GLint vStride_;    /**< Stride value for the v-direction. */

        GLint gridSubdivs_; /**< Number of subdivisions in the grid. */

        std::array<GLfloat, 4> gold_Ka_; /**< Ambient reflection properties for gold material. */
        std::array<GLfloat, 4> gold_Kd_; /**< Diffuse reflection properties for gold material. */
        std::array<GLfloat, 4> gold_Ks_; /**< Specular reflection properties for gold material. */
        GLfloat gold_Ke_;                /**< Emissive property for gold material. */

        std::array<GLfloat, 4> silver_Ka_; /**< Ambient reflection properties for silver material. */
        std::array<GLfloat, 4> silver_Kd_; /**< Diffuse reflection properties for silver material. */
        std::array<GLfloat, 4> silver_Ks_; /**< Specular reflection properties for silver material. */
        GLfloat silver_Ke_;                /**< Emissive property for silver material. */

        static const int IMG_WIDTH = 64;  /**< Texture image width. */
        static const int IMG_HEIGHT = 64; /**< Texture image height. */

        std::array<GLubyte, IMG_WIDTH * IMG_HEIGHT * 3> image_; /**< Storage for texture image data. */
    };

} // end namespace _3dmodeler

#endif // _3dmodeler_grid_h
