#include "gl/GLBackendEmitters.h"

#include <array>
#include <memory>
#include <string>

#include "Events/EventEmitter.h"

using entity::Entity;
using events::EventEmitter;

using _3dmodeler::GLBackendEmitters;
using StdEmitter = EventEmitter<void(void)>;

namespace
{
	const std::string GL_GAME_EMITTERS_KEY = "GLBackendEmittersKey";
} // end namespace

GLBackendEmitters::~GLBackendEmitters() = default;

GLBackendEmitters::GLBackendEmitters() : Entity(),
										 xEmitter_(std::make_shared<StdEmitter>()),
										 yEmitter_(std::make_shared<StdEmitter>()),
										 zEmitter_(std::make_shared<StdEmitter>()),
										 tEmitter_(std::make_shared<StdEmitter>()),
										 lEmitter_(std::make_shared<StdEmitter>()),
										 xCapEmitter_(std::make_shared<StdEmitter>()),
										 yCapEmitter_(std::make_shared<StdEmitter>()),
										 zCapEmitter_(std::make_shared<StdEmitter>()),
										 tCapEmitter_(std::make_shared<StdEmitter>()),
										 lCapEmitter_(std::make_shared<StdEmitter>()),
										 runEmitter_(std::make_shared<StdEmitter>()),
										 drawEmitter_(std::make_shared<events::EventEmitter<
														  void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>()),
										 pickEmitter_(std::make_shared<events::EventEmitter<
														  void(const int _x, const int _y, const int _h, const std::string &_viewport)>>()),
										 mouseEmitter_(std::make_shared<events::EventEmitter<
														   void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>()),
										 mouseMotionEmitter_(std::make_shared<events::EventEmitter<
																 void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>()),
										 actionMenuEmitter_(std::make_shared<events::EventEmitter<
																void(const int _index)>>())
{
	SetKey(GL_GAME_EMITTERS_KEY);
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetXEmitter()
{
	return xEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetYEmitter()
{
	return yEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetZEmitter()
{
	return zEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetTEmitter()
{
	return tEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetLEmitter()
{
	return lEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetXCapEmitter()
{
	return xCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetYCapEmitter()
{
	return yCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetZCapEmitter()
{
	return zCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetTCapEmitter()
{
	return tCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetLCapEmitter()
{
	return lCapEmitter_;
}

std::shared_ptr<EventEmitter<
	void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>
GLBackendEmitters::GetDrawEmitter()
{
	return drawEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _x, const int _y, const int _h, const std::string &_viewport)>>
GLBackendEmitters::GetPickEmitter()
{
	return pickEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>
GLBackendEmitters::GetMouseEmitter()
{
	return mouseEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>
GLBackendEmitters::GetMouseMotionEmitter()
{
	return mouseMotionEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _index)>>
GLBackendEmitters::GetActionMenuEmitter()
{
	return actionMenuEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLBackendEmitters::GetRunEmitter()
{
	return runEmitter_;
}
