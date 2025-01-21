#include "GLGame.h"

#include <algorithm>
#include <string>

#include "Entities/Entity.h"
#include "GLGameEmitters.h"
#include "GLGameWindow.h"

using entity::Entity;

using _3dmodeler::GLGame;
using _3dmodeler::GLGameEmitters;
using _3dmodeler::GLGameWindow;

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
GLGame* GLGame::callbackInstance_(nullptr);
/*============================================================================*/

GLGame::~GLGame() = default;

void GLGame::TimerCallback(int _idx)
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

GLGame::GLGame(int _argc, char* _argv[]) : Entity()
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

void GLGame::Run()
{
	emitters_.GetRunEmitter()->Signal()();

	glutMainLoop();
};

GLGameEmitters& GLGame::GetEmitters() {
	return emitters_;
}

GLGameWindow& GLGame::GetGameWindow() {
	return gameWindow_;
}

void GLGame::RegisterCallbacks() const
{
	glutDisplayFunc(DisplayWrapper);   
	glutReshapeFunc(ReshapeWrapper);
	glutKeyboardFunc(KeyboardWrapper); 
	glutKeyboardUpFunc(KeyboardUpWrapper);
	glutMouseFunc(MouseWrapper);
	glutMotionFunc(MouseMotionWrapper);
}

void GLGame::InitGlut(int _argc, char* _argv[]) const
{
	glutInit(&_argc, _argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow(_3DMODELER_TITLE.c_str());
}

void GLGame::InitActionMenu() const
{
	glutCreateMenu(ActionMenuWrapper);
		glutAddMenuEntry("Toggle Pick/Pan", 0);
		glutAddMenuEntry("Quit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GLGame::InitServer() const
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

void GLGame::InitClient() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GLGame::DisplayWrapper()
{
	callbackInstance_->Display();
}

void GLGame::ReshapeWrapper(const int _w, const int _h)
{
	callbackInstance_->Reshape(_w, _h);
}

void GLGame::KeyboardWrapper(const unsigned char _chr, const int _x, const int _y)
{
	callbackInstance_->Keyboard(_chr, _x, _y);
}

void GLGame::KeyboardUpWrapper(const unsigned char _chr, const int _x, const int _y)
{
	callbackInstance_->KeyboardUp(_chr, _x, _y);
}

void GLGame::PickWrapper(const int _x, const int _y, const std::string& _viewport) {
	callbackInstance_->Pick(_x, _y, callbackInstance_->GetGameWindow().GetHeight(), _viewport);
}

void GLGame::MouseWrapper(const int _button, const int _state, const int _x, const int _y) {
	callbackInstance_->Mouse(_button, _state, _x, _y, callbackInstance_->GetGameWindow().GetWidth(), callbackInstance_->GetGameWindow().GetHeight());
}

void GLGame::MouseMotionWrapper(const int _x, const int _y) {
	callbackInstance_->MouseMotion(_x, _y, callbackInstance_->GetGameWindow().GetWidth(), callbackInstance_->GetGameWindow().GetHeight(), callbackInstance_->GetGameWindow().GetProjOrthoMatrix());
}

void GLGame::ActionMenuWrapper(const int _index) {
	callbackInstance_->ActionMenu(_index);
}

void GLGame::Display()
{
	KeyboardUpdateState();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	emitters_.GetDrawEmitter()->Signal()(GetGameWindow().GetWidth(), GetGameWindow().GetHeight(), GetGameWindow().GetProjOrthoMatrix(), GetGameWindow().GetProjPerspectiveMatrix());

	// RENDER
	glFlush();
	glutSwapBuffers();
}

void GLGame::Reshape(const int _w, const int _h)
{
	GetGameWindow().SetWidth(_w);
	GetGameWindow().SetHeight(_h);

	GLint i;
	GLdouble projection[16];

	//========================= DEFINE VIEWPORT ==============================*/
	//glViewport(0, 0, _w, _h);
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
	for (i = 0; i < 16; i++) GetGameWindow().SetProjOrthoMatrix(projection[i], i);

	glLoadIdentity();
	//========================= Perspective Projection =====================
	gluPerspective(40.0, (GLdouble)_w / (GLdouble)_h, 0.5, 200.0);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	for (i = 0; i < 16; i++) GetGameWindow().SetProjPerspectiveMatrix(projection[i], i);
	glLoadIdentity();

	/*========================= REDISPLAY ====================================*/
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void GLGame::Keyboard(const unsigned char _chr, const int _x, const int _y)
{
	keysPressed_[_chr] = true;
}

void GLGame::KeyboardUp(const unsigned char _chr, const int _x, const int _y)
{
	keysPressed_[_chr] = false;
}

void GLGame::KeyboardUpdateState()
{
	for (int i = 0; i < NUMBER_KEYS; i++)
	{
		if (keysPressed_[i]) 
		{
			switch (i)
			{
			case 'x':
				emitters_.GetXEmitter()->Signal()(); break;
			case 'y':
				emitters_.GetYEmitter()->Signal()(); break;
			case 'z':
				emitters_.GetZEmitter()->Signal()(); break;
			case 't':
				emitters_.GetTEmitter()->Signal()(); 
				keysPressed_[i] = false;
				break;
			case 'l':
				emitters_.GetLEmitter()->Signal()();
				keysPressed_[i] = false;
				break;
			case 'X':
				emitters_.GetXCapEmitter()->Signal()(); break;
			case 'Y':
				emitters_.GetYCapEmitter()->Signal()(); break;
			case 'Z':
				emitters_.GetZCapEmitter()->Signal()(); break;
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

void GLGame::Pick(const int _x, const int _y, const int _h, const std::string& _viewport) {
	emitters_.GetPickEmitter()->Signal()(_x, _y, _h, _viewport);
}

void GLGame::Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h) {
	emitters_.GetMouseEmitter()->Signal()(_button, _state, _x, _y, _w, _h);
}

void GLGame::MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho) {
	emitters_.GetMouseMotionEmitter()->Signal()(_x, _y, _w, _h, _projOrtho);
}

void GLGame::ActionMenu(const int _index) {
	emitters_.GetActionMenuEmitter()->Signal()(_index);
}
