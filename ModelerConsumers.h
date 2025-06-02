/**
 * @file ModelerConsumers.h
 * @brief Declaration of the ModelerConsumers class which handles event consumption for the 3D modeler application.
 */

#ifndef _3dmodeler_modeler_consumers_h
#define _3dmodeler_modeler_consumers_h

#include <array>
#include <memory>
#include <string>

#include "Entities/Entity.h"
#include "Events/EventConsumer.h"
#include "configuration/config.h"
#include "Modeler.h"

namespace _3dmodeler
{

    /**
     * @class ModelerConsumers
     * @brief A class that manages event consumers for various actions in the 3D modeling application.
     *
     * This class provides mechanisms to handle events triggered by user input and other actions,
     * allowing the Modeler instance to respond accordingly.
     */
    class _3DMODELER_DLL_EXPORT ModelerConsumers : public entity::Entity
    {
    public:
        /**
         * @brief Constructs a ModelerConsumers object with a given Modeler instance.
         * @param modeler A shared pointer to the Modeler instance.
         */
        ModelerConsumers(std::shared_ptr<Modeler> modeler);

        /**
         * @brief Destructor for ModelerConsumers.
         */
        ~ModelerConsumers();

        ModelerConsumers(const ModelerConsumers &) = delete;
        ModelerConsumers(ModelerConsumers &&) = delete;
        ModelerConsumers &operator=(const ModelerConsumers &) = delete;
        ModelerConsumers &operator=(ModelerConsumers &&) = delete;

        /**
         * @brief Getters for x keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetXConsumer();

        /**
         * @brief Getters for y keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetYConsumer();

        /**
         * @brief Getters for z keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetZConsumer();

        /**
         * @brief Getters for t keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetTConsumer();

        /**
         * @brief Getters for l keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetLConsumer();

        /**
         * @brief Getters for X keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetXCapConsumer();

        /**
         * @brief Getters for Ykeyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetYCapConsumer();

        /**
         * @brief Getters for Z keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetZCapConsumer();

        /**
         * @brief Getters for T keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetTCapConsumer();

        /**
         * @brief Getters for L keyboard input event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetLCapConsumer();

        /**
         * @brief Getters for Draw event consumer.
         */
        std::shared_ptr<events::EventConsumer<
            void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>
        GetDrawConsumer();

        /**
         * @brief Getters for Pick event consumer.
         */
        std::shared_ptr<events::EventConsumer<
            void(const int _x, const int _y, const int _h, const std::string &_viewport)>>
        GetPickConsumer();

        /**
         * @brief Getters for Mouse event consumer.
         */
        std::shared_ptr<events::EventConsumer<
            void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>
        GetMouseConsumer();

        /**
         * @brief Getters for Mouse Motion event consumer.
         */
        std::shared_ptr<events::EventConsumer<
            void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>
        GetMouseMotionConsumer();

        /**
         * @brief Getters for Action Menu event consumer.
         */
        std::shared_ptr<events::EventConsumer<
            void(const int _index)>>
        GetActionMenuConsumer();

        /**
         * @brief Getters for Run event consumer.
         */
        std::shared_ptr<events::EventConsumer<void(void)>> GetRunConsumer();

    private:
        std::shared_ptr<events::EventConsumer<void(void)>> xConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> yConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> zConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> tConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> lConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> xCapConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> yCapConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> zCapConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> tCapConsumer_;
        std::shared_ptr<events::EventConsumer<void(void)>> lCapConsumer_;

        std::shared_ptr<events::EventConsumer<
            void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>
            drawConsumer_;

        std::shared_ptr<events::EventConsumer<
            void(const int _x, const int _y, const int _h, const std::string &_viewport)>>
            pickConsumer_;

        std::shared_ptr<events::EventConsumer<
            void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>
            mouseConsumer_;

        std::shared_ptr<events::EventConsumer<
            void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>
            mouseMotionConsumer_;

        std::shared_ptr<events::EventConsumer<
            void(const int _index)>>
            actionMenuConsumer_;

        std::shared_ptr<events::EventConsumer<void(void)>> runConsumer_;
    };

} // end namespace _3dmodeler

#endif // _3dmodeler_modeler_consumers_h
