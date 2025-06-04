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
#include "gl/GLBackendEmitters.h"
#include "gl/GLBackendWindow.h"

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
         * @brief Timer callback function for periodic updates.
         * @param _idx Timer index.
         */
        static void TimerCallback(int _idx);

        /**
         * @brief Get the event emitters associated with the game.
         * @return Reference to the GLBackendEmitters instance.
         */
        GLBackendEmitters &GetEmitters();

        /**
         * @brief Get the game window instance.
         * @return Reference to the GLBackendWindow instance.
         */
        GLBackendWindow &GetGameWindow();

        static GLBackend *callbackInstance_; /**< Static instance for callback functions. */

    private:
        GLBackendEmitters emitters_; /**< Handles input events and actions. */

        // GLUT Initialization
        /**
         * @brief Initialize GLUT with command-line arguments.
         * @param _argc Number of command-line arguments.
         * @param _argv Command-line argument values.
         */
        void InitGlut(int _argc, char *_argv[]) const;

        /**
         * @brief Initialize the action menu.
         */
        void InitActionMenu() const;

        /**
         * @brief Initialize the server component.
         */
        void InitServer() const;

        /**
         * @brief Initialize the client component.
         */
        void InitClient() const;

        // GLUT callbacks
        /**
         * @brief Register GLUT callbacks.
         */
        void RegisterCallbacks() const;

        /**
         * @brief GLUT display function.
         */
        void Display();
        static void DisplayWrapper();

        /**
         * @brief GLUT reshape function.
         * @param _w Window width.
         * @param _h Window height.
         */
        void Reshape(const int _w, const int _h);
        static void ReshapeWrapper(const int _w, const int _h);

        /**
         * @brief GLUT keyboard input function.
         * @param _chr Pressed character.
         * @param _x X-coordinate of the mouse.
         * @param _y Y-coordinate of the mouse.
         */
        void Keyboard(const unsigned char _chr, const int _x, const int _y);
        static void KeyboardWrapper(unsigned char _chr, int _x, int _y);

        /**
         * @brief GLUT keyboard release function.
         * @param _chr Released character.
         * @param _x X-coordinate of the mouse.
         * @param _y Y-coordinate of the mouse.
         */
        void KeyboardUp(const unsigned char _chr, const int _x, const int _y);
        static void KeyboardUpWrapper(const unsigned char _chr, const int _x, const int _y);

        /**
         * @brief GLUT picking function.
         */
        void Pick(const int _x, const int _y, const int _h, const std::string &_viewport);
        static void PickWrapper(const int _x, const int _y, const std::string &_viewport);

        /**
         * @brief GLUT mouse input function.
         */
        void Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);
        static void MouseWrapper(const int _button, const int _state, const int _x, const int _y);

        /**
         * @brief GLUT mouse motion function.
         */
        void MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho);
        static void MouseMotionWrapper(const int _x, const int _y);

        /**
         * @brief GLUT action menu function.
         */
        void ActionMenu(const int _index);
        static void ActionMenuWrapper(const int _index);

        /**
         * @brief Update the keyboard state.
         */
        void KeyboardUpdateState();

        // Members
        GLBackendWindow gameWindow_;        /**< Handles window properties. */
        std::array<bool, 256> keysPressed_; /**< Tracks the state of pressed keys. */
    };

} // end _3dmodeler

#endif // _3dmodeler_glbackend_h
