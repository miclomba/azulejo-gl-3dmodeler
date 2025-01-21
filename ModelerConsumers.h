#ifndef _3dmodeler_modeler_consumers_h
#define	_3dmodeler_modeler_consumers_h

#include <memory>
#include <string>

#include "Entities/Entity.h"
#include "Events/EventConsumer.h"

#include "config.h"
#include "Modeler.h"

namespace _3dmodeler{

class _3DMODELER_DLL_EXPORT ModelerConsumers : public entity::Entity
{
public:
	ModelerConsumers(std::shared_ptr<Modeler> modeler);
	~ModelerConsumers();
	ModelerConsumers(const ModelerConsumers&) = delete;
	ModelerConsumers(ModelerConsumers&&) = delete;
	ModelerConsumers & operator=(const ModelerConsumers&) = delete;
	ModelerConsumers & operator=(ModelerConsumers&&) = delete;

	std::shared_ptr<events::EventConsumer<void(void)>> GetXConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetYConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetZConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetTConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetLConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetXCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetYCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetZCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetTCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetLCapConsumer();

	std::shared_ptr<events::EventConsumer<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> GetDrawConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> GetPickConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> GetMouseConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> GetMouseMotionConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _index)
	>> GetActionMenuConsumer();

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
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> drawConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> pickConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> mouseConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> mouseMotionConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _index)
	>> actionMenuConsumer_;

	std::shared_ptr<events::EventConsumer<void(void)>> runConsumer_;
};

} // end _3dmodeler
#endif	// _3dmodeler_modeler_consumers_h

