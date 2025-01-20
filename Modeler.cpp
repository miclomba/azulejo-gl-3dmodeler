#include "Modeler.h"

#include <algorithm>
#include <cstdlib>
#include <future>
#include <memory>
#include <stdio.h>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "filesystem.hpp"

#include <boost/asio/packaged_task.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Events/EventConsumer.h"
#include "test_filesystem_adapters/ContainerResource2D.h"

#include "Common.h"
#include "GLEntityTask.h"
#include "Object.h"

using boost::property_tree::ptree;

using _3dmodeler::Modeler;
using _3dmodeler::GLEntityTask;
using events::EventConsumer;
using entity::Entity;

namespace pt = boost::property_tree;

namespace
{
const std::string _3DMODELER_KEY = "3DModeler";
const int NUMBER_KEYS = 256;
} // end namespace

Modeler::Modeler() :
	threadPool_(std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() - 1 : 1)
{
	SetKey(_3DMODELER_KEY);

	// TODO: Dummy place holder object that will be replaced by Grid, PointLight, and UI
	AggregateMember(Object::ObjectKey());
	SharedEntity& obj = GetObj();
	obj = std::make_shared<Object>(Object::ObjectKey());

	xConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->X(true); });
	yConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Y(true); });
	zConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Z(true); });
	tConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->T(true); });
	lConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->L(); });
	xCapConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->X(false); });
	yCapConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Y(false); });
	zCapConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Z(false); });
	tCapConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->T(false); });
	lCapConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->L(); });

	drawConsumer_ = std::make_shared<EventConsumer<
        void(GLint w_, GLint h_, GLfloat * projOrtho_, GLfloat * projPerspective_)
    >>(
        [this](GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_) { 
            this->Draw(w_, h_, projOrtho_, projPerspective_); 
        }
    );

	pickConsumer_ = std::make_shared<EventConsumer<
		void(const int _x, const int _y, const int _h, const std::string & _viewport)
	>>(
		[this](const int _x, const int _y, const int _h, const std::string& _viewport) {
			this->Pick(_x, _y, _h, _viewport);
		}
	);

	mouseConsumer_ = std::make_shared<EventConsumer<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>>(
		[this](const int _button, const int _state, const int _x, const int _y, const int _w, const int _h) {
			this->Mouse(_button, _state, _x, _y, _w, _h);
		}
	);

	mouseMotionConsumer_ = std::make_shared<EventConsumer<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>>(
		[this](const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho) {
			this->MouseMotion(_x, _y, _w, _h, _projOrtho);
		}
	);

	actionMenuConsumer_ = std::make_shared<EventConsumer<
		void(const int _index)
	>>(
		[this](const int _index) {
			this->ActionMenu(_index);
		}
	);

	runConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Run(); });

	// refactor here
	grid_ = std::make_unique<Grid>();
	lights_ = std::make_unique<PointLight>();
	userInterf_ = std::make_unique<UserInterface>();

	toggleLights_ = true;
	toggleTextures_ = true;

	curViewport_ = "";
	picking_ = true;
	dragging_ = false;
	i_ = -1;
	j_ = -1;
	k_ = -1;
	pickIdx_ = 0;
	ctrlPntIdxCount_ = 16;
	lightIdxCount_ = 2;
	renderMode_ = GL_RENDER;

	moving_ = false;
	xo_ = 0;
	yo_ = 0;
	xi_ = 0;
	yi_ = 0;
	xf_ = 0;
	yf_ = 0;
	panX_ = 0;
	panY_ = 0;
	frontX_ = 0;
	frontZ_ = 0;
	sideZ_ = 0;
	sideY_ = 0;
	topX_ = 0;
	topY_ = 0;

	zPhi_ = 0;
	yTheta_ = 45;
	xPsi_ = 225;
}

Modeler::~Modeler() = default;

void Modeler::Run()
{
}

Modeler::SharedEntity& Modeler::GetObj()
{
	return GetAggregatedMember(Object::ObjectKey());
}

void Modeler::DrawGLEntities()
{
	std::vector<std::future<GLEntity*>> futures;

	SharedEntity& obj = GetObj();
	if (obj)
	{
		GLEntity* glObj = dynamic_cast<GLEntity*>(obj.get());
		GLEntityTask task([glObj, this]() { return glObj; });
		futures.push_back(task.GetFuture());

		boost::asio::post(threadPool_, task);
	}

	for (std::future<GLEntity*>& future : futures)
		future.get()->Draw();
}

void Modeler::DrawGameInfo()
{
	glColor3f(0.0f, 1.0f, 1.0f);

	GLint i;
	glRasterPos3f(7.5f, -9.0f, 0.0f);
	char reset[16] = { 'P','r','e','s','s',' ','X',' ','t','o',' ',
					  'R','E','S','E','T' };
	for (i = 0; i < 16; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, reset[i]);
}

void Modeler::Draw(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
{
	DrawGLEntities();
	DrawGameInfo();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //===================== Display a user interface ===========================
    userInterf_->display(w_, h_);

    glEnable(GL_SCISSOR_TEST);

    //===================== Draw bottom left viewport ======================
    glViewport(0, 0, w_ / 2, h_ / 2);
    glScissor(0, 0, w_ / 2, h_ / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(projOrtho_);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (moving_ == true && dragging_ == true && curViewport_ == "top") {
        topY_ = yo_ + panY_ / 20;
        topX_ = xo_ - panX_ / 20;
    }
    gluLookAt(topX_, topY_, 1, topX_, topY_, 0, 0, 1, 0);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    lights_->display(renderMode_);
    if (toggleLights_ == true)
        glEnable(GL_LIGHTING);
    if (toggleTextures_ == true)
        glEnable(GL_TEXTURE_2D);
    grid_->display(renderMode_);
    glLoadIdentity();

    //===================== Draw top left viewport =========================
    glViewport(0, h_ / 2 + 1, w_ / 2, h_ / 2);
    glScissor(0, h_ / 2 + 1, w_ / 2, h_ / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(projOrtho_);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (moving_ == true && dragging_ == true && curViewport_ == "side") {
        sideY_ = yo_ + panY_ / 20;
        sideZ_ = xo_ - panX_ / 20;
    }
    gluLookAt(-1, sideY_, sideZ_, 0, sideY_, sideZ_, 0, 1, 0);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    lights_->display(renderMode_);
    if (toggleLights_ == true)
        glEnable(GL_LIGHTING);
    if (toggleTextures_ == true)
        glEnable(GL_TEXTURE_2D);
    grid_->display(renderMode_);
    glLoadIdentity();

    //===================== Draw bottom right viewport =====================
    glViewport(w_ / 2 + 1, 0, w_ / 2, h_ / 2);
    glScissor(w_ / 2 + 1, 0, w_ / 2, h_ / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(projOrtho_);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (moving_ == true && dragging_ == true && curViewport_ == "front") {
        frontZ_ = yo_ + panY_ / 20;
        frontX_ = xo_ - panX_ / 20;
    }
    gluLookAt(frontX_, -1, frontZ_, frontX_, 0, frontZ_, 0, 0, 1);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    lights_->display(renderMode_);
    if (toggleLights_ == true)
        glEnable(GL_LIGHTING);
    if (toggleTextures_ == true)
        glEnable(GL_TEXTURE_2D);
    grid_->display(renderMode_);
    glLoadIdentity();

    //===================== Draw top right viewport ========================
    glViewport(w_ / 2 + 1, h_ / 2 + 1, w_ / 2, h_ / 2);
    glScissor(w_ / 2 + 1, h_ / 2 + 1, w_ / 2, h_ / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(projPerspective_);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-10, 0, -10, 0, 0, 0, 0, 1, 0);
    glRotatef(zPhi_, 0.0f, 0.0f, 1.0f);
    glRotatef(yTheta_, 0.0f, 1.0f, 0.0f);
    glRotatef(xPsi_, 1.0f, 0.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    lights_->display(renderMode_);
    if (toggleLights_ == true)
        glEnable(GL_LIGHTING);
    if (toggleTextures_ == true)
        glEnable(GL_TEXTURE_2D);
    grid_->display(renderMode_);
    glLoadIdentity();

    glDisable(GL_SCISSOR_TEST);
}

void Modeler::Pick(const int _x, const int _y, const int _h, const std::string& _viewport) {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLuint select_buff[NUMBER_KEYS];
	glSelectBuffer(NUMBER_KEYS, select_buff);

	renderMode_ = GL_SELECT;
	glRenderMode(renderMode_);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((GLdouble)_x, (GLdouble)(_h - _y), 8, 8, viewport);

	if ((viewport[2]) <= (viewport[3]))
		glOrtho(-5.0, 5.0,
			-5.0 * ((GLfloat)(viewport[3]) / (GLfloat)(viewport[2])),
			5.0 * ((GLfloat)(viewport[3]) / (GLfloat)(viewport[2])),
			5.0, -200.0);
	else
		glOrtho(-5.0 * ((GLfloat)(viewport[2]) / (GLfloat)(viewport[3])),
			5.0 * ((GLfloat)(viewport[2]) / (GLfloat)(viewport[3])),
			-5.0, 5.0, 5.0, -200.0);

	glMatrixMode(GL_MODELVIEW);
	if (_viewport == "top") {
		glLoadIdentity();
		gluLookAt(topX_, topY_, 1, topX_, topY_, 0, 0, 1, 0);
	}
	else if (_viewport == "side") {
		glLoadIdentity();
		gluLookAt(-1, sideY_, sideZ_, 0, sideY_, sideZ_, 0, 1, 0);
	}
	else if (_viewport == "front") {
		glLoadIdentity();
		gluLookAt(frontX_, -1, frontZ_, frontX_, 0, frontZ_, 0, 0, 1);
	}
	glInitNames();
	glPushName(0);
	grid_->displayControlPoints(renderMode_);
	lights_->display(renderMode_);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	renderMode_ = GL_RENDER;
	GLint hits = glRenderMode(renderMode_);
	ProcessPicks(hits, select_buff);

	GLint i, j;
	i_ = -1;
	j_ = -1;
	k_ = -1;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if ((GLfloat)(i * 4 + j + 1) == pickIdx_) {
				dragging_ = true;
				i_ = i;
				j_ = j;
				break;
			}
		}

		j--;
		if (i * 4 + j + 1 == pickIdx_)
			break;
	}
	for (i = 1; i <= lightIdxCount_; i++) {
		if (pickIdx_ == ctrlPntIdxCount_ + i) {
			k_ = i - 1;
			dragging_ = true;
			break;
		}
	}

	glMatrixMode(GL_MODELVIEW);
}

void Modeler::ProcessPicks(const GLint _hits, GLuint* _slct_bff) {
	GLuint* select_buff = _slct_bff;
	/*====== First GLuint in select_buff is number of names in this hit ======*/
	GLuint names = *select_buff;
	/*======================== Skip min and max depth ========================*/
	select_buff += 3;

	pickIdx_ = 0;

	GLint i, j, k;
	for (i = 0; i < _hits; i++)
	{
		for (j = 0; j < (GLint)names; j++)
		{
			for (k = 1; k <= ctrlPntIdxCount_ + lightIdxCount_; k++) {
				if (*select_buff == (GLuint)k) {
					pickIdx_ = k;
					break;
				}
			}
			if (pickIdx_ != 0)
				break;
			select_buff++;
		}
	}
}

void Modeler::Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h) {
	if (picking_ == true && _button == GLUT_LEFT_BUTTON && _state == GLUT_DOWN) {
		//========================= Quadrant 1 Click ===========================
		if (_x > _w / 2 && _y < _h / 2) {
			//Do Nothing.
		}
		//========================= Quadrant 2 Click ===========================
		else if (_x < _w / 2 && _y < _h / 2) {
			glViewport(0, _h / 2 + 1, _w / 2, _h / 2);
			curViewport_ = "side";
			Pick(_x, _y, _h, "side");
		}
		//========================= Quadrant 3 Click ===========================
		else if (_x < _w / 2 && _y > _h / 2) {
			glViewport(0, 0, _w / 2, _h / 2);
			curViewport_ = "top";
			Pick(_x, _y, _h, "top");
		}
		//========================= Quadrant 4 Click ===========================
		else if (_x > _w / 2 && _y > _h / 2) {
			glViewport(_w / 2 + 1, 0, _w / 2, _h / 2);
			curViewport_ = "front";
			Pick(_x, _y, _h, "front");
		}
	}
	else if (picking_ == true && dragging_ == true &&
		_button == GLUT_LEFT_BUTTON && _state == GLUT_UP) {
		dragging_ = false;
		curViewport_ = "";
	}
	else if (moving_ == true &&
		_button == GLUT_LEFT_BUTTON && _state == GLUT_DOWN) {
		dragging_ = true;
		xi_ = _x;
		yi_ = _y;
		panX_ = 0;
		panY_ = 0;
		//========================= Quadrant 1 Click ===========================
		if (_x > _w / 2 && _y < _h / 2) {
			//Do Nothing.
		}
		//========================= Quadrant 2 Click ===========================
		else if (_x < _w / 2 && _y < _h / 2) {
			glViewport(0, _h / 2 + 1, _w / 2, _h / 2);
			curViewport_ = "side";
			xo_ = sideZ_;
			yo_ = sideY_;
		}
		//========================= Quadrant 3 Click ===========================
		else if (_x < _w / 2 && _y > _h / 2) {
			glViewport(0, 0, _w / 2, _h / 2);
			curViewport_ = "top";
			xo_ = topX_;
			yo_ = topY_;
		}
		//========================= Quadrant 4 Click ===========================
		else if (_x > _w / 2 && _y > _h / 2) {
			glViewport(_w / 2 + 1, 0, _w / 2, _h / 2);
			curViewport_ = "front";
			xo_ = frontX_;
			yo_ = frontZ_;
		}
	}
	else if (moving_ == true && dragging_ == true &&
		_button == GLUT_LEFT_BUTTON && _state == GLUT_UP) {
		dragging_ = false;
		xi_ = 0;
		yi_ = 0;
		xf_ = 0;
		yf_ = 0;
		curViewport_ = "";
	}
}

void Modeler::MouseMotion(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho) {
	if (picking_ == true && dragging_ == true) {
		//========================= Quadrant 1 Motion ==========================
		if (_x > _w / 2 && _y < _h / 2) {
			//Do Nothing
		}
		//========================= Quadrant 2 Motion ==========================
		else if (curViewport_ == "side" &&
			_x < _w / 2 && _y < _h / 2 && _x > 0 && _y > 0) {

			glViewport(0, _h / 2 + 1, _w / 2, _h / 2);

			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(_projOrtho);
			GLdouble projection[16];
			glGetDoublev(GL_PROJECTION_MATRIX, projection);
			glLoadIdentity();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(-1, sideY_, sideZ_, 0, sideY_, sideZ_, 0, 1, 0);
			GLdouble modelView[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			glLoadIdentity();

			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			GLdouble mouseX, mouseY, mouseZ;

			GLint success = gluUnProject(_x, _y, 0,
				modelView, projection, viewport,
				&mouseX, &mouseY, &mouseZ);

			if (success == 1) {
				mouseY += 10;
				mouseY *= -1;
				mouseY += 2 * sideY_;
			}

			if (k_ == -1) {
				grid_->controlPoints_[i_][j_][1] = (GLfloat)mouseY;
				grid_->controlPoints_[i_][j_][2] = (GLfloat)mouseZ;
			}
			else {
				lights_->position_[k_][1] = (GLfloat)mouseY;
				lights_->position_[k_][2] = (GLfloat)mouseZ;
				glLightfv(GL_LIGHT0, GL_POSITION, lights_->position_[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, lights_->position_[1]);
			}
		}
		//========================= Quadrant 3 Motion ==========================
		else if (curViewport_ == "top" &&
			_x < _w / 2 && _y > _h / 2 && _x > 0 && _y < _h) {

			glViewport(0, 0, _w / 2, _h / 2);

			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(_projOrtho);
			GLdouble projection[16];
			glGetDoublev(GL_PROJECTION_MATRIX, projection);
			glLoadIdentity();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(topX_, topY_, 1, topX_, topY_, 0, 0, 1, 0);
			GLdouble modelView[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			glLoadIdentity();

			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			GLdouble mouseX, mouseY, mouseZ;

			GLint success = gluUnProject(_x, _y, 0,
				modelView, projection, viewport,
				&mouseX, &mouseY, &mouseZ);

			if (success == 1) {
				mouseY = 10 - mouseY;
				mouseY += 2 * topY_;
			}

			if (k_ == -1) {
				grid_->controlPoints_[i_][j_][0] = (GLfloat)mouseX;
				grid_->controlPoints_[i_][j_][1] = (GLfloat)mouseY;
			}
			else {
				lights_->position_[k_][0] = (GLfloat)mouseX;
				lights_->position_[k_][1] = (GLfloat)mouseY;
				glLightfv(GL_LIGHT0, GL_POSITION, lights_->position_[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, lights_->position_[1]);
			}
		}
		//========================= Quadrant 4 Motion ==========================
		else if (curViewport_ == "front" &&
			_x > _w / 2 && _y > _h / 2 && _x < _w && _y < _h) {

			glViewport(_w / 2 + 1, 0, _w / 2, _h / 2);

			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(_projOrtho);
			GLdouble projection[16];
			glGetDoublev(GL_PROJECTION_MATRIX, projection);
			glLoadIdentity();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(frontX_, -1, frontZ_, frontX_, 0, frontZ_, 0, 0, 1);
			GLdouble modelView[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			glLoadIdentity();

			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			GLdouble mouseX, mouseY, mouseZ;

			GLint success = gluUnProject(_x, _y, 0,
				modelView, projection, viewport,
				&mouseX, &mouseY, &mouseZ);

			if (success == 1) {
				mouseZ -= 10;
				mouseZ *= -1;
				mouseZ += 2 * frontZ_;
			}

			if (k_ == -1) {
				grid_->controlPoints_[i_][j_][0] = (GLfloat)mouseX;
				grid_->controlPoints_[i_][j_][2] = (GLfloat)mouseZ;
			}
			else {
				lights_->position_[k_][0] = (GLfloat)mouseX;
				lights_->position_[k_][2] = (GLfloat)mouseZ;
				glLightfv(GL_LIGHT0, GL_POSITION, lights_->position_[0]);
				glLightfv(GL_LIGHT1, GL_POSITION, lights_->position_[1]);
			}
		}
	}
	else if (moving_ == true && dragging_ == true) {
		xf_ = _x;
		yf_ = _y;
		panX_ = xf_ - xi_;
		panY_ = yf_ - yi_;
	}
}

void Modeler::ActionMenu(const int _index) {
	switch (_index) {
	case 0:
		picking_ = !picking_;
		moving_ = !moving_;
		if (picking_ == false) {
			i_ = 0;
			j_ = 0;
		}
		break;
	case 1:
		exit(1);
		break;
	default:
		break;
	}
}

void Modeler::X(const bool isLowerCase) {
	if (isLowerCase) {
		xPsi_ += 1.5f;
		if (xPsi_ > 360.0f)
			xPsi_ -= 360.0f;
	}
	else {
		xPsi_ += -1.5f;
		if (xPsi_ < -360.0f)
			xPsi_ += 360.0f;
	}
}

void Modeler::Y(const bool isLowerCase) {
	if (isLowerCase) {
		yTheta_ += 1.5f;
		if (yTheta_ > 360.0f)
			yTheta_ -= 360.0f;
	}
	else {
		yTheta_ += -1.5f;
		if (yTheta_ < -360.0f)
			yTheta_ += 360.0f;
	}
}

void Modeler::Z(const bool isLowerCase) {
	if (isLowerCase) {
		zPhi_ += 1.5f;
		if (zPhi_ > 360.0f)
			zPhi_ -= 360.0f;
	}
	else {
		zPhi_ += -1.5f;
		if (zPhi_ < -360.0f)
			zPhi_ += 360.0f;
	}
}

void Modeler::T(const bool isLowerCase) {
	if (isLowerCase) {
		toggleTextures_ = !toggleTextures_;
	}
	else {
		grid_->changeTextures();
	}
	glutPostRedisplay();
}

void Modeler::L() {
	toggleLights_ = !toggleLights_;
	glutPostRedisplay();
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetXConsumer()
{
	return xConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetYConsumer()
{
	return yConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetZConsumer()
{
	return zConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetTConsumer()
{
	return tConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetLConsumer()
{
	return lConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetXCapConsumer()
{
	return xCapConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetYCapConsumer()
{
	return yCapConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetZCapConsumer()
{
	return zCapConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetTCapConsumer()
{
	return tCapConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetLCapConsumer()
{
	return lCapConsumer_;
}

std::shared_ptr<EventConsumer<
    void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
>> Modeler::GetDrawConsumer()
{
	return drawConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> Modeler::GetPickConsumer()
{
	return pickConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> Modeler::GetMouseConsumer()
{
	return mouseConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> Modeler::GetMouseMotionConsumer()
{
	return mouseMotionConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _index)
	>> Modeler::GetActionMenuConsumer()
{
	return actionMenuConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetRunConsumer()
{
	return runConsumer_;
}
