#include "gl/GLBackend.h"

#include <algorithm>
#include <string>

#include "Entities/Entity.h"
#include "gl/GL.h"
#include "gl/GLBackendEmitters.h"
#include "gl/GLProjectionInfo.h"

using entity::Entity;

using _3dmodeler::GL;
using _3dmodeler::GLBackend;
using _3dmodeler::GLBackendEmitters;
using _3dmodeler::GLProjectionInfo;

namespace
{
	const int NUMBER_KEYS = 256;
	const std::string _3DMODELER_TITLE = "3DModeler";
} // end namespace

std::unique_ptr<GLBackend> GLBackend::callbackInstance_ = nullptr;

GLBackend &GLBackend::Get(int _argc, char *_argv[])
{
	if (!GLBackend::callbackInstance_)
	{
		GLBackend::callbackInstance_.reset(new GLBackend(_argc, _argv));
	}
	return *GLBackend::callbackInstance_;
}

GLBackend::~GLBackend() = default;

GLBackend::GLBackend(int _argc, char *_argv[]) : Entity(), keysPressed_({})
{
	SetKey(_3DMODELER_TITLE);

	// Initialize the graphics library singleton
	GL::Get(_argc, _argv);
}

void GLBackend::Run()
{
	emitters_.GetRunEmitter()->Signal()();

	GL::Get().Run();
};

GLBackendEmitters &GLBackend::GetEmitters()
{
	return emitters_;
}

void GLBackend::DisplayCallback()
{
	callbackInstance_->Display();
}

void GLBackend::ReshapeCallback(const int _w, const int _h)
{
	callbackInstance_->Reshape(_w, _h);
}

void GLBackend::KeyboardCallback(const unsigned char _chr, const int _x, const int _y)
{
	callbackInstance_->Keyboard(_chr, _x, _y);
}

void GLBackend::KeyboardUpCallback(const unsigned char _chr, const int _x, const int _y)
{
	callbackInstance_->KeyboardUp(_chr, _x, _y);
}

void GLBackend::PickCallback(const int _x, const int _y, const std::string &_viewport)
{
	callbackInstance_->Pick(_x, _y, GL::Get().GetGameProjectionInfo().GetHeight(), _viewport);
}

void GLBackend::MouseCallback(const int _button, const int _state, const int _x, const int _y)
{
	GLProjectionInfo &gameProjInfo = GL::Get().GetGameProjectionInfo();
	callbackInstance_->Mouse(_button, _state, _x, _y, gameProjInfo.GetWidth(), gameProjInfo.GetHeight());
}

void GLBackend::MouseMotionCallback(const int _x, const int _y)
{
	GLProjectionInfo &gameProjInfo = GL::Get().GetGameProjectionInfo();
	callbackInstance_->MouseMotion(_x, _y, gameProjInfo.GetWidth(), gameProjInfo.GetHeight(), gameProjInfo.GetProjOrthoMatrix());
}

void GLBackend::ActionMenuCallback(const int _index)
{
	callbackInstance_->ActionMenu(_index);
}

void GLBackend::Display()
{
	KeyboardUpdateState();

	GL &gl = GL::Get();
	gl.DisplayClear();

	GLProjectionInfo &gameProjInfo = gl.GetGameProjectionInfo();
	emitters_.GetDrawEmitter()->Signal()(gameProjInfo.GetWidth(), gameProjInfo.GetHeight(), gameProjInfo.GetProjOrthoMatrix(), gameProjInfo.GetProjPerspectiveMatrix());

	gl.DisplayFlush();
}

void GLBackend::Reshape(const int _w, const int _h)
{
	GL::Get().Reshape(_w, _h);
}

void GLBackend::Keyboard(const unsigned char _chr, const int _x, const int _y)
{
	keysPressed_[_chr] = true;
}

void GLBackend::KeyboardUp(const unsigned char _chr, const int _x, const int _y)
{
	keysPressed_[_chr] = false;
}

void GLBackend::KeyboardUpdateState()
{
	for (int i = 0; i < NUMBER_KEYS; i++)
	{
		if (keysPressed_[i])
		{
			switch (i)
			{
			case 'x':
				emitters_.GetXEmitter()->Signal()();
				break;
			case 'y':
				emitters_.GetYEmitter()->Signal()();
				break;
			case 'z':
				emitters_.GetZEmitter()->Signal()();
				break;
			case 't':
				emitters_.GetTEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'l':
				emitters_.GetLEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'X':
				emitters_.GetXCapEmitter()->Signal()();
				break;
			case 'Y':
				emitters_.GetYCapEmitter()->Signal()();
				break;
			case 'Z':
				emitters_.GetZCapEmitter()->Signal()();
				break;
			case 'T':
				emitters_.GetTCapEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'L':
				emitters_.GetLCapEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			default:
				break;
			}
		}
	}
}

void GLBackend::Pick(const int _x, const int _y, const int _h, const std::string &_viewport)
{
	emitters_.GetPickEmitter()->Signal()(_x, _y, _h, _viewport);
}

void GLBackend::Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
{
	emitters_.GetMouseEmitter()->Signal()(_button, _state, _x, _y, _w, _h);
}

void GLBackend::MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
{
	emitters_.GetMouseMotionEmitter()->Signal()(_x, _y, _w, _h, _projOrtho);
}

void GLBackend::ActionMenu(const int _index)
{
	emitters_.GetActionMenuEmitter()->Signal()(_index);
}
