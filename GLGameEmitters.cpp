#include "GLGameEmitters.h"

#include <array>
#include <memory>
#include <string>

#include "Events/EventEmitter.h"

using events::EventEmitter;
using entity::Entity;

using _3dmodeler::GLGameEmitters;

namespace
{
const std::string GL_GAME_EMITTERS_KEY = "GLGameEmittersKey";
} // end namespace

GLGameEmitters::~GLGameEmitters() = default;

GLGameEmitters::GLGameEmitters() : Entity()
{
	SetKey(GL_GAME_EMITTERS_KEY);

	xEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	yEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	zEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	tEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	lEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();

	xCapEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	yCapEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	zCapEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	tCapEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
	lCapEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();

	drawEmitter_ = std::make_shared<events::EventEmitter<
		void(GLint w_, GLint h_, const std::array<GLfloat, 16>& projOrtho_, const std::array<GLfloat, 16>& projPerspective_)
	>>();
	pickEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _x, const int _y, const int _h, const std::string & _viewport)
	>>();
	mouseEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>>();
	mouseMotionEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho)
	>>();
	actionMenuEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _index)
	>>();
	runEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetXEmitter()
{
	return xEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetYEmitter()
{
	return yEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetZEmitter()
{
	return zEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetTEmitter()
{
	return tEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetLEmitter()
{
	return lEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetXCapEmitter()
{
	return xCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetYCapEmitter()
{
	return yCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetZCapEmitter()
{
	return zCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetTCapEmitter()
{
	return tCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetLCapEmitter()
{
	return lCapEmitter_;
}

std::shared_ptr<EventEmitter<
	void(GLint w_, GLint h_, const std::array<GLfloat, 16>& projOrtho_, const std::array<GLfloat, 16>& projPerspective_)
>> GLGameEmitters::GetDrawEmitter()
{
	return drawEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _x, const int _y, const int _h, const std::string& _viewport)
>> GLGameEmitters::GetPickEmitter()
{
	return pickEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> GLGameEmitters::GetMouseEmitter()
{
	return mouseEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho)
	>> GLGameEmitters::GetMouseMotionEmitter()
{
	return mouseMotionEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _index)
	>> GLGameEmitters::GetActionMenuEmitter()
{
	return actionMenuEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGameEmitters::GetRunEmitter()
{
	return runEmitter_;
}
