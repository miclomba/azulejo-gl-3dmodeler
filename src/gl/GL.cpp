#include "gl/GL.h"
#include "gl/GLBackend.h"
#include "gl/GLWindow.h"

#include <algorithm>
#include <string>

using _3dmodeler::GL;
using _3dmodeler::GLBackend;
using _3dmodeler::GLWindow;

namespace
{
	const int TIME = 25;
	const int VAL = 0;
	const int WIN_WIDTH = 600;
	const int WIN_HEIGHT = 480;
	const int INIT_WIN_X = 100;
	const int INIT_WIN_Y = 100;
	const std::string _3DMODELER_TITLE = "3DModeler";
} // end namespace

GL::~GL() = default;

void GL::TimerCallback(int _idx)
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

GL::GL(int _argc, char *_argv[])
{
	InitGlut(_argc, _argv);
	InitActionMenu();
	RegisterCallbacks();
	InitServer();
	InitClient();
}

void GL::Run()
{
	glutMainLoop();
};

void GL::DisplayClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL::DisplayFlush()
{
	glFlush();
	glutSwapBuffers();
}

GLWindow &GL::GetGameWindow()
{
	return gameWindow_;
}

void GL::RegisterCallbacks() const
{
	glutDisplayFunc(GLBackend::DisplayWrapper);
	glutReshapeFunc(GLBackend::ReshapeWrapper);
	glutKeyboardFunc(GLBackend::KeyboardWrapper);
	glutKeyboardUpFunc(GLBackend::KeyboardUpWrapper);
	glutMouseFunc(GLBackend::MouseWrapper);
	glutMotionFunc(GLBackend::MouseMotionWrapper);
}

void GL::InitGlut(int _argc, char *_argv[]) const
{
	glutInit(&_argc, _argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow(_3DMODELER_TITLE.c_str());
	glutTimerFunc(TIME, TimerCallback, VAL);
}

void GL::InitActionMenu() const
{
	glutCreateMenu(GLBackend::ActionMenuWrapper);
	glutAddMenuEntry("Toggle Pick/Pan", 0);
	glutAddMenuEntry("Quit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GL::InitServer() const
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

void GL::InitClient() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GL::Reshape(const int _w, const int _h)
{
	gameWindow_.SetWidth(_w);
	gameWindow_.SetHeight(_h);

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
	for (GLint i = 0; i < 16; i++)
		gameWindow_.SetProjOrthoMatrix(projection[i], i);

	glLoadIdentity();
	//========================= Perspective Projection =====================
	gluPerspective(40.0, (GLdouble)_w / (GLdouble)_h, 0.5, 200.0);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	for (GLint i = 0; i < 16; i++)
		gameWindow_.SetProjPerspectiveMatrix(projection[i], i);
	glLoadIdentity();

	/*========================= REDISPLAY ====================================*/
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
