#ifndef _3dmodeler_glgame_emitters_h
#define _3dmodeler_glgame_emitters_h

#include <memory>
#include <string>

#include "Entities/Entity.h"
#include "Events/EventEmitter.h"

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT GLGameEmitters : public entity::Entity
{
public:
	GLGameEmitters();
	virtual ~GLGameEmitters();
	GLGameEmitters(const GLGameEmitters&) = delete;
	GLGameEmitters(GLGameEmitters&&) = delete;
	GLGameEmitters& operator=(const GLGameEmitters&) = delete;
	GLGameEmitters& operator=(GLGameEmitters&&) = delete;

	std::shared_ptr<events::EventEmitter<void(void)>> GetXEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetYEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetZEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetTEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetLEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetXCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetYCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetZCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetTCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetLCapEmitter();

	std::shared_ptr<events::EventEmitter<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> GetDrawEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> GetPickEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> GetMouseEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> GetMouseMotionEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _index)
	>> GetActionMenuEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetRunEmitter();

private:
	// keyboard input emitters
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

	// other emitters
	std::shared_ptr<events::EventEmitter<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> drawEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> pickEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> mouseEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> mouseMotionEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _index)
	>> actionMenuEmitter_;

	std::shared_ptr<events::EventEmitter<void(void)>> runEmitter_;
};

} // end _3dmodeler
#endif // _3dmodeler_glgame_emitters_h
