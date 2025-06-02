/**
 * @file GLBackendEmitters.h
 * @brief Declaration of the GLBackendEmitters class which manages input event emitters for a 3D modeling application.
 */

#ifndef _3dmodeler_glgame_emitters_h
#define _3dmodeler_glgame_emitters_h

#include <array>
#include <memory>
#include <string>

#include "Entities/Entity.h"
#include "Events/EventEmitter.h"
#include "config.h"

namespace _3dmodeler
{

    /**
     * @class GLBackendEmitters
     * @brief A class for managing input event emitters in the 3D modeler application.
     *
     * This class provides various event emitters for handling user input and graphical operations,
     * including keyboard, mouse, and rendering events.
     */
    class _3DMODELER_DLL_EXPORT GLBackendEmitters : public entity::Entity
    {
    public:
        /**
         * @brief Default constructor.
         */
        GLBackendEmitters();

        /**
         * @brief Destructor.
         */
        virtual ~GLBackendEmitters();

        GLBackendEmitters(const GLBackendEmitters &) = delete;
        GLBackendEmitters(GLBackendEmitters &&) = delete;
        GLBackendEmitters &operator=(const GLBackendEmitters &) = delete;
        GLBackendEmitters &operator=(GLBackendEmitters &&) = delete;

        /**
         * @brief Getters for x keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetXEmitter();

        /**
         * @brief Getters for y keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetYEmitter();

        /**
         * @brief Getters for z keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetZEmitter();

        /**
         * @brief Getters for t keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetTEmitter();

        /**
         * @brief Getters for l keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetLEmitter();

        /**
         * @brief Getters for X keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetXCapEmitter();

        /**
         * @brief Getters for Y keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetYCapEmitter();

        /**
         * @brief Getters for Z keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetZCapEmitter();

        /**
         * @brief Getters for T keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetTCapEmitter();

        /**
         * @brief Getters for L keyboard input event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetLCapEmitter();

        /**
         * @brief Getter for the Draw event emitters.
         */
        std::shared_ptr<events::EventEmitter<
            void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>
        GetDrawEmitter();

        /**
         * @brief Getter for the Pick event emitters.
         */
        std::shared_ptr<events::EventEmitter<
            void(const int _x, const int _y, const int _h, const std::string &_viewport)>>
        GetPickEmitter();

        /**
         * @brief Getter for the Mouse event emitters.
         */
        std::shared_ptr<events::EventEmitter<
            void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>
        GetMouseEmitter();

        /**
         * @brief Getter for the Mouse Motion event emitters.
         */
        std::shared_ptr<events::EventEmitter<
            void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>
        GetMouseMotionEmitter();

        /**
         * @brief Getter for the Action Menu event emitters.
         */
        std::shared_ptr<events::EventEmitter<
            void(const int _index)>>
        GetActionMenuEmitter();

        /**
         * @brief Getter for the Run event emitters.
         */
        std::shared_ptr<events::EventEmitter<void(void)>> GetRunEmitter();

    private:
        // Keyboard input emitters
        std::shared_ptr<events::EventEmitter<void(void)>> xEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> yEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> zEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> tEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> lEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> xCapEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> yCapEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> zCapEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> tCapEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> lCapEmitter_;

        // Other emitters
        std::shared_ptr<events::EventEmitter<
            void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>
            drawEmitter_;
        std::shared_ptr<events::EventEmitter<
            void(const int _x, const int _y, const int _h, const std::string &_viewport)>>
            pickEmitter_;
        std::shared_ptr<events::EventEmitter<
            void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>
            mouseEmitter_;
        std::shared_ptr<events::EventEmitter<
            void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>
            mouseMotionEmitter_;
        std::shared_ptr<events::EventEmitter<
            void(const int _index)>>
            actionMenuEmitter_;
        std::shared_ptr<events::EventEmitter<void(void)>> runEmitter_;
    };

} // end namespace _3dmodeler

#endif // _3dmodeler_glgame_emitters_h
