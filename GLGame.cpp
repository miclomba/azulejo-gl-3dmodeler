#include "GLGame.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "Events/EventEmitter.h"

using events::EventEmitter;

using _3dmodeler::GLGame;

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

GLGame::GLGame(int _argc, char* _argv[])
{
	if (!callbackInstance_)
		callbackInstance_ = this;

	std::fill(keysPressed_.begin(), keysPressed_.end(), false);

	InitGlut(_argc, _argv);
	InitActionMenu();
	RegisterCallbacks();
	InitServer();
	InitClient();

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
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>>();
	pickEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _x, const int _y, const int _h, const std::string & _viewport)
	>>();
	mouseEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>>();
	mouseMotionEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>>();
	actionMenuEmitter_ = std::make_shared<events::EventEmitter<
		void(const int _index)
	>>();
	runEmitter_ = std::make_shared<events::EventEmitter<void(void)>>();

	// window and projection
	w_ = WIN_WIDTH;
	h_ = WIN_HEIGHT;

	for (int i = 0; i < 16; i++) {
		projOrtho_[i] = 0;
		projPerspective_[i] = 0;
	}
}

void GLGame::Run()
{
	runEmitter_->Signal()();

	glutMainLoop();
};

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
	callbackInstance_->Pick(_x, _y, callbackInstance_->h_, _viewport);
}

void GLGame::MouseWrapper(const int _button, const int _state, const int _x, const int _y) {
	callbackInstance_->Mouse(_button, _state, _x, _y, callbackInstance_->w_, callbackInstance_->h_);
}

void GLGame::MouseMotionWrapper(const int _x, const int _y) {
	callbackInstance_->MouseMotion(_x, _y, callbackInstance_->w_, callbackInstance_->h_, callbackInstance_->projOrtho_);
}

void GLGame::ActionMenuWrapper(const int _index) {
	callbackInstance_->ActionMenu(_index);
}

void GLGame::Display()
{
	KeyboardUpdateState();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawEmitter_->Signal()(w_, h_, projOrtho_, projPerspective_);

	// RENDER
	glFlush();
	glutSwapBuffers();
}

void GLGame::Reshape(const int _w, const int _h)
{
	w_ = _w;
	h_ = _h;

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
	for (i = 0; i < 16; i++) projOrtho_[i] = projection[i];

	glLoadIdentity();
	//========================= Perspective Projection =====================
	gluPerspective(40.0, (GLdouble)_w / (GLdouble)_h, 0.5, 200.0);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	for (i = 0; i < 16; i++) projPerspective_[i] = projection[i];
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
				xEmitter_->Signal()(); break;
			case 'y':
				yEmitter_->Signal()(); break;
			case 'z':
				zEmitter_->Signal()(); break;
			case 't':
				tEmitter_->Signal()(); 
				keysPressed_[i] = false;
				break;
			case 'l':
				lEmitter_->Signal()();
				keysPressed_[i] = false;
				break;
			case 'X':
				xCapEmitter_->Signal()(); break;
			case 'Y':
				yCapEmitter_->Signal()(); break;
			case 'Z':
				zCapEmitter_->Signal()(); break;
			case 'T':
				tCapEmitter_->Signal()(); 
				keysPressed_[i] = false;
				break;
			case 'L':
				lCapEmitter_->Signal()(); 
				keysPressed_[i] = false;
				break;
			default:
				break;
			}
		}
	}
}

void GLGame::Pick(const int _x, const int _y, const int _h, const std::string& _viewport) {
	pickEmitter_->Signal()(_x, _y, _h, _viewport);
}

void GLGame::Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h) {
	mouseEmitter_->Signal()(_button, _state, _x, _y, _w, _h);
}

void GLGame::MouseMotion(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho) {
	mouseMotionEmitter_->Signal()(_x, _y, _w, _h, _projOrtho);
}

void GLGame::ActionMenu(const int _index) {
	actionMenuEmitter_->Signal()(_index);
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetXEmitter()
{
	return xEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetYEmitter()
{
	return yEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetZEmitter()
{
	return zEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetTEmitter()
{
	return tEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetLEmitter()
{
	return lEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetXCapEmitter()
{
	return xCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetYCapEmitter()
{
	return yCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetZCapEmitter()
{
	return zCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetTCapEmitter()
{
	return tCapEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetLCapEmitter()
{
	return lCapEmitter_;
}

std::shared_ptr<EventEmitter<
	void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
>> GLGame::GetDrawEmitter()
{
	return drawEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _x, const int _y, const int _h, const std::string& _viewport)
>> GLGame::GetPickEmitter()
{
	return pickEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> GLGame::GetMouseEmitter()
{
	return mouseEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> GLGame::GetMouseMotionEmitter()
{
	return mouseMotionEmitter_;
}

std::shared_ptr<EventEmitter<
	void(const int _index)
	>> GLGame::GetActionMenuEmitter()
{
	return actionMenuEmitter_;
}

std::shared_ptr<EventEmitter<void(void)>> GLGame::GetRunEmitter()
{
	return runEmitter_;
}
