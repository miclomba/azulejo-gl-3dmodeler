/**
 * @file GLBackend.h
 * @brief Declaration of the GLBackend class for managing the main game loop and event handling in the 3D modeler application.
 */

#ifndef _3dmodeler_glbackend_h
#define _3dmodeler_glbackend_h

#include <array>
#include <memory>

#include "Entities/Entity.h"
#include "configuration/config.h"
#include "gl/GL.h"
#include "gl/GLBackendEmitters.h"

namespace _3dmodeler
{

    /**
     * @class GLBackend
     * @brief A class responsible for managing the main game loop and event handling.
     *
     * This class initializes GLUT, handles rendering and user input events, and manages game emitters
     * and window properties.
     */
    class _3DMODELER_DLL_EXPORT GLBackend : public entity::Entity
    {
    public:
        /**
         * @brief Constructor for GLBackend.
         * @param _argc Number of command-line arguments.
         * @param _argv Command-line argument values.
         */
        GLBackend(int _argc, char *_argv[]);

        /**
         * @brief Destructor for GLBackend.
         */
        virtual ~GLBackend();

        GLBackend(const GLBackend &) = delete;
        GLBackend(GLBackend &&) = delete;
        GLBackend &operator=(const GLBackend &) = delete;
        GLBackend &operator=(GLBackend &&) = delete;

        /**
         * @brief Start the main game loop.
         */
        void Run();

        /**
         * @brief Get the event emitters associated with the game.
         * @return Reference to the GLBackendEmitters instance.
         */
        GLBackendEmitters &GetEmitters();

        static void DisplayWrapper();
        static void ReshapeWrapper(const int _w, const int _h);
        static void KeyboardWrapper(unsigned char _chr, int _x, int _y);
        static void KeyboardUpWrapper(const unsigned char _chr, const int _x, const int _y);
        static void ActionMenuWrapper(const int _index);
        static void PickWrapper(const int _x, const int _y, const std::string &_viewport);
        static void MouseWrapper(const int _button, const int _state, const int _x, const int _y);
        static void MouseMotionWrapper(const int _x, const int _y);

    private:
        /**
         * @brief Get the game window instance.
         * @return Reference to the GLBackendWindow instance.
         */
        GLBackendWindow &GetGameWindow();

        static GLBackend *callbackInstance_; /**< Static instance for callback functions. */

        GLBackendEmitters emitters_; /**< Handles input events and actions. */

        /**
         * @brief GLUT display function.
         */
        void Display();

        /**
         * @brief GLUT reshape function.
         * @param _w Window width.
         * @param _h Window height.
         */
        void Reshape(const int _w, const int _h);

        /**
         * @brief GLUT keyboard input function.
         * @param _chr Pressed character.
         * @param _x X-coordinate of the mouse.
         * @param _y Y-coordinate of the mouse.
         */
        void Keyboard(const unsigned char _chr, const int _x, const int _y);

        /**
         * @brief GLUT keyboard release function.
         * @param _chr Released character.
         * @param _x X-coordinate of the mouse.
         * @param _y Y-coordinate of the mouse.
         */
        void KeyboardUp(const unsigned char _chr, const int _x, const int _y);

        /**
         * @brief GLUT picking function.
         */
        void Pick(const int _x, const int _y, const int _h, const std::string &_viewport);

        /**
         * @brief GLUT mouse input function.
         */
        void Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);

        /**
         * @brief GLUT mouse motion function.
         */
        void MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho);

        /**
         * @brief GLUT action menu function.
         */
        void ActionMenu(const int _index);

        /**
         * @brief Update the keyboard state.
         */
        void KeyboardUpdateState();

        // Members
        std::unique_ptr<GL> gl_;            /**< Graphics library wrapper. */
        std::array<bool, 256> keysPressed_; /**< Tracks the state of pressed keys. */
    };

} // end _3dmodeler

#endif // _3dmodeler_glbackend_h
