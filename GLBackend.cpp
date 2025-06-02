#include "GLBackend.h"

#include <algorithm>
#include <string>

#include "Entities/Entity.h"
#include "GLGameEmitters.h"
#include "GLBackendWindow.h"

using entity::Entity;

using _3dmodeler::GLBackend;
using _3dmodeler::GLBackendWindow;
using _3dmodeler::GLGameEmitters;

namespace
{
	const int WIN_WIDTH = 600;
	const int WIN_HEIGHT = 480;
	const int NUMBER_KEYS = 256;
	const int INIT_WIN_X = 100;
	const int INIT_WIN_Y = 100;
	const std::string _3DMODELER_TITLE = "3DModeler";
} // end namespace

/*======================== CALLBACK POINTER ==================================*/
GLBackend *GLBackend::callbackInstance_(nullptr);
/*============================================================================*/

GLBackend::~GLBackend() = default;

void GLBackend::TimerCallback(int _idx)
{
	switch (_idx)
	{
	case 0:
		glutPostRedisplay();
		glutTimerFunc(25, TimerCallback, 0);
		break;
	default:
		break;
	}
}

GLBackend::GLBackend(int _argc, char *_argv[]) : Entity()
{
	SetKey(_3DMODELER_TITLE);

	if (!callbackInstance_)
		callbackInstance_ = this;

	std::fill(keysPressed_.begin(), keysPressed_.end(), false);

	InitGlut(_argc, _argv);
	InitActionMenu();
	RegisterCallbacks();
	InitServer();
	InitClient();
}

void GLBackend::Run()
{
	GetEmitters().GetRunEmitter()->Signal()();

	glutMainLoop();
};

GLGameEmitters &GLBackend::GetEmitters()
{
	return emitters_;
}

GLBackendWindow &GLBackend::GetGameWindow()
{
	return gameWindow_;
}

void GLBackend::RegisterCallbacks() const
{
	glutDisplayFunc(DisplayWrapper);
	glutReshapeFunc(ReshapeWrapper);
	glutKeyboardFunc(KeyboardWrapper);
	glutKeyboardUpFunc(KeyboardUpWrapper);
	glutMouseFunc(MouseWrapper);
	glutMotionFunc(MouseMotionWrapper);
}

void GLBackend::InitGlut(int _argc, char *_argv[]) const
{
	glutInit(&_argc, _argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow(_3DMODELER_TITLE.c_str());
}

void GLBackend::InitActionMenu() const
{
	glutCreateMenu(ActionMenuWrapper);
	glutAddMenuEntry("Toggle Pick/Pan", 0);
	glutAddMenuEntry("Quit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GLBackend::InitServer() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0, 1);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void GLBackend::InitClient() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GLBackend::DisplayWrapper()
{
	callbackInstance_->Display();
}

void GLBackend::ReshapeWrapper(const int _w, const int _h)
{
	callbackInstance_->Reshape(_w, _h);
}

void GLBackend::KeyboardWrapper(const unsigned char _chr, const int _x, const int _y)
{
	callbackInstance_->Keyboard(_chr, _x, _y);
}

void GLBackend::KeyboardUpWrapper(const unsigned char _chr, const int _x, const int _y)
{
	callbackInstance_->KeyboardUp(_chr, _x, _y);
}

void GLBackend::PickWrapper(const int _x, const int _y, const std::string &_viewport)
{
	callbackInstance_->Pick(_x, _y, callbackInstance_->GetGameWindow().GetHeight(), _viewport);
}

void GLBackend::MouseWrapper(const int _button, const int _state, const int _x, const int _y)
{
	callbackInstance_->Mouse(_button, _state, _x, _y, callbackInstance_->GetGameWindow().GetWidth(), callbackInstance_->GetGameWindow().GetHeight());
}

void GLBackend::MouseMotionWrapper(const int _x, const int _y)
{
	callbackInstance_->MouseMotion(_x, _y, callbackInstance_->GetGameWindow().GetWidth(), callbackInstance_->GetGameWindow().GetHeight(), callbackInstance_->GetGameWindow().GetProjOrthoMatrix());
}

void GLBackend::ActionMenuWrapper(const int _index)
{
	callbackInstance_->ActionMenu(_index);
}

void GLBackend::Display()
{
	KeyboardUpdateState();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GetEmitters().GetDrawEmitter()->Signal()(GetGameWindow().GetWidth(), GetGameWindow().GetHeight(), GetGameWindow().GetProjOrthoMatrix(), GetGameWindow().GetProjPerspectiveMatrix());

	// RENDER
	glFlush();
	glutSwapBuffers();
}

void GLBackend::Reshape(const int _w, const int _h)
{
	GetGameWindow().SetWidth(_w);
	GetGameWindow().SetHeight(_h);

	GLint i;
	GLdouble projection[16];

	/*========================= ORTHO PROJECTION =============================*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (_w / 2 <= _h / 2)
		glOrtho(-5.0, 5.0, -5.0 * ((GLfloat)(_h / 2) / (GLfloat)(_w / 2)),
				5.0 * ((GLfloat)(_h / 2) / (GLfloat)(_w / 2)), 10.0, -200.0);
	else
		glOrtho(-5.0 * ((GLfloat)(_w / 2) / (GLfloat)(_h / 2)),
				5.0 * ((GLfloat)(_w / 2) / (GLfloat)(_h / 2)), -5.0, 5.0, 10.0, -200.0);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	for (i = 0; i < 16; i++)
		GetGameWindow().SetProjOrthoMatrix(projection[i], i);

	glLoadIdentity();
	//========================= Perspective Projection =====================
	gluPerspective(40.0, (GLdouble)_w / (GLdouble)_h, 0.5, 200.0);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	for (i = 0; i < 16; i++)
		GetGameWindow().SetProjPerspectiveMatrix(projection[i], i);
	glLoadIdentity();

	/*========================= REDISPLAY ====================================*/
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
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
				GetEmitters().GetXEmitter()->Signal()();
				break;
			case 'y':
				GetEmitters().GetYEmitter()->Signal()();
				break;
			case 'z':
				GetEmitters().GetZEmitter()->Signal()();
				break;
			case 't':
				GetEmitters().GetTEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'l':
				GetEmitters().GetLEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'X':
				GetEmitters().GetXCapEmitter()->Signal()();
				break;
			case 'Y':
				GetEmitters().GetYCapEmitter()->Signal()();
				break;
			case 'Z':
				GetEmitters().GetZCapEmitter()->Signal()();
				break;
			case 'T':
				GetEmitters().GetTCapEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'L':
				GetEmitters().GetLCapEmitter()->Signal()();
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
	GetEmitters().GetPickEmitter()->Signal()(_x, _y, _h, _viewport);
}

void GLBackend::Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
{
	GetEmitters().GetMouseEmitter()->Signal()(_button, _state, _x, _y, _w, _h);
}

void GLBackend::MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
{
	GetEmitters().GetMouseMotionEmitter()->Signal()(_x, _y, _w, _h, _projOrtho);
}

void GLBackend::ActionMenu(const int _index)
{
	GetEmitters().GetActionMenuEmitter()->Signal()(_index);
}
