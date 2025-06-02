/**
 * @file Modeler.h
 * @brief Declaration of the Modeler class representing a 3D modeling application.
 *
 * The Modeler class manages rendering, picking control points, panning,
 * lighting, and texturing of the Grid object within different viewports.
 */

#ifndef _3dmodeler_modeler_h
#define _3dmodeler_modeler_h

#include <array>
#include <memory>
#include <string>

#include <boost/asio/thread_pool.hpp>

#include "config.h"
#include "gl/GLEntity.h"
#include "Grid.h"
#include "PointLight.h"
#include "UserInterface.h"

namespace _3dmodeler
{

    /**
     * @class Modeler
     * @brief A class representing a 3D modeling application.
     *
     * This class provides functionalities for rendering 3D objects, handling user input events,
     * managing different viewports, and performing picking and panning operations on control points.
     */
    class _3DMODELER_DLL_EXPORT Modeler : public GLEntity
    {
    public:
        /**
         * @brief Default constructor for the Modeler class.
         */
        Modeler();

        /**
         * @brief Destructor for the Modeler class.
         */
        ~Modeler();

        Modeler(const Modeler &) = delete;
        Modeler(Modeler &&) = delete;
        Modeler &operator=(const Modeler &) = delete;
        Modeler &operator=(Modeler &&) = delete;

        /**
         * @brief Draw the model in different viewports.
         * @param w_ Width of the viewport.
         * @param h_ Height of the viewport.
         * @param projOrtho_ Orthographic projection matrix.
         * @param projPerspective_ Perspective projection matrix.
         */
        void Draw(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_);

        /**
         * @brief Handle picking of control points in the scene.
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _h The window height
         * @param _viewport The name of the viewport
         */
        void Pick(const int _x, const int _y, const int _h, const std::string &_viewport);

        /**
         * @brief Set dragging state during picking operation.
         */
        void SetDragginStateDuringPicking();

        /**
         * @brief Handle mouse events for interaction.
         * @param _button The mouse button clicked
         * @param _state The button click state
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         */
        void Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);

        /**
         * @brief Handle mouse motion events.
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Handle action menu selections.
         * @param _index Action index
         */
        void ActionMenu(const int _index);

        /**
         * @brief Process picking results.
         * @param _hits Number of hits for the given pick
         * @param _slct_buff Selection buffer
         */
        void ProcessPicks(const GLint _hits, GLuint *_slct_bff);

        /**
         * @brief Handle transformations based on x input commands.
         * @param isLowerCase if the input key is lowercase
         */
        void X(const bool isLowerCase);

        /**
         * @brief Handle transformations based on y input commands.
         * @param isLowerCase if the input key is lowercase
         */
        void Y(const bool isLowerCase);

        /**
         * @brief Handle transformations based on z input commands.
         * @param isLowerCase if the input key is lowercase
         */
        void Z(const bool isLowerCase);

        /**
         * @brief Handle transformations based on t input commands.
         * @param isLowerCase if the input key is lowercase
         */
        void T(const bool isLowerCase);

        /**
         * @brief Handle transformations based on l input commands.
         */
        void L();

        /**
         * @brief Start the modeling application.
         */
        void Run();

    private:
        /**
         * @brief Handle mouse mouse moving click down event.
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         */
        void MouseMovingOnClickDown(const int _x, const int _y, const int _w, const int _h);

        /**
         * @brief Handle mouse moving click up event.
         */
        void MouseMovingOnClickUp();

        /**
         * @brief Handle mouse picking click down event.
         * @param _button The mouse button clicked
         * @param _state The button click state
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         */
        void MousePickingOnClickDown(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);

        /**
         * @brief Handle mouse picking click up event.
         */
        void MousePickingOnClickUp();

        /**
         * @brief Handle mouse motion events on quadrant two.
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void MouseMotionQuadrantTwo(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Handle mouse motion events on quadrant three.
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void MouseMotionQuadrantThree(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Handle mouse motion events on quadrant four.
         * @param _x The x coordinate of the mouse
         * @param _y The y coordinate of the mouse
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void MouseMotionQuadrantFour(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Get the Point Light aggregated member.
         * @return PointLight
         */
        PointLight *const GetPointLight();

        /**
         * @brief Get the User Interface aggregated member.
         * @return UserInterface
         */
        UserInterface *GetUserInterface();

        /**
         * @brief Get the Grid aggregated member.
         * @return Grid
         */
        Grid *GetGrid();

        /**
         * @brief Draw the game information in the UI
         */
        void DrawGameInfo();

        /**
         * @brief Draw the game information in the bottom left viewport
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void DrawBottomLeftViewport(GLint _w, GLint _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Draw the game information in the top left viewport
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void DrawTopLeftViewport(GLint _w, GLint _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Draw the game information in the bottom right viewport
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void DrawBottomRightViewport(GLint _w, GLint _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief Draw the game information in the top right viewport
         * @param _w The window width
         * @param _h The window height
         * @param _projOrtho The projection matrix
         */
        void DrawTopRightViewport(GLint _w, GLint _h, const std::array<GLfloat, 16> &_projPerspective);

        boost::asio::thread_pool threadPool_; /**< Thread pool for parallel processing. */

        bool toggleLights_;   /**< Toggle for lights. */
        bool toggleTextures_; /**< Toggle for textures. */

        std::string curViewport_; /**< Current active viewport. */
        bool picking_;            /**< Picking state. */
        bool dragging_;           /**< Dragging state. */
        GLint i_, j_, k_, pickIdx_, ctrlPntIdxCount_, lightIdxCount_;
        GLenum renderMode_;

        bool moving_;
        GLfloat xo_, yo_, xi_, yi_, xf_, yf_, panX_, panY_;
        GLfloat frontX_, frontZ_, sideZ_, sideY_, topX_, topY_;
        GLfloat zPhi_, yTheta_, xPsi_;
    };

} // end namespace _3dmodeler

#endif // _3dmodeler_modeler_h
