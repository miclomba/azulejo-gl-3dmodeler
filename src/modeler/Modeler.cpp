#include "modeler/Modeler.h"

#include <array>
#include <future>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio/packaged_task.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

#include "configuration/config.h"
#include "configuration/filesystem.h"
#include "gl/GLEntityTask.h"

using _3dmodeler::GLEntityTask;
using _3dmodeler::Grid;
using _3dmodeler::Modeler;
using _3dmodeler::PointLight;
using _3dmodeler::UserInterface;
using entity::Entity;

namespace
{
	const std::string _3DMODELER_KEY = "3DModeler";
	const int NUMBER_KEYS = 256;
	const std::string RESET_MESSAGE = "Press X to RESET";
	GLdouble PROJECTION[16];
	GLdouble MODELVIEW[16];
	GLint VIEWPORT[4];
	GLdouble MOUSEX, MOUSEY, MOUSEZ;
} // end namespace

Modeler::Modeler() : GLEntity(),
					 threadPool_(std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() - 1 : 1)
{
	SetKey(_3DMODELER_KEY);

	SharedEntity pointLight = std::make_shared<PointLight>();
	pointLight->SetKey(PointLight::PointLightKey());
	AggregateMember(pointLight);

	SharedEntity ui = std::make_shared<UserInterface>();
	ui->SetKey(UserInterface::UserInterfaceKey());
	AggregateMember(ui);

	SharedEntity grid = std::make_shared<Grid>();
	grid->SetKey(Grid::GridKey());
	AggregateMember(grid);

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

PointLight *const Modeler::GetPointLight()
{
	SharedEntity &entity = GetAggregatedMember(PointLight::PointLightKey());
	return dynamic_cast<PointLight *>(entity.get());
}

UserInterface *Modeler::GetUserInterface()
{
	SharedEntity &entity = GetAggregatedMember(UserInterface::UserInterfaceKey());
	return dynamic_cast<UserInterface *>(entity.get());
}

Grid *Modeler::GetGrid()
{
	SharedEntity &entity = GetAggregatedMember(Grid::GridKey());
	return dynamic_cast<Grid *>(entity.get());
}

void Modeler::DrawGameInfo()
{
	glColor3f(0.0f, 1.0f, 1.0f);
	glRasterPos3f(7.5f, -9.0f, 0.0f);
	for (size_t i = 0; i < RESET_MESSAGE.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, RESET_MESSAGE[i]);
}

void Modeler::Draw(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)
{
	DrawGameInfo();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	GetUserInterface()->Draw(w_, h_);

	glEnable(GL_SCISSOR_TEST);

	DrawBottomLeftViewport(w_, h_, projOrtho_);
	DrawTopLeftViewport(w_, h_, projOrtho_);
	DrawBottomRightViewport(w_, h_, projOrtho_);
	DrawTopRightViewport(w_, h_, projPerspective_);

	glDisable(GL_SCISSOR_TEST);
}

void Modeler::DrawTopRightViewport(GLint w, GLint h, const std::array<GLfloat, 16> &projPerspective)
{
	glViewport(w / 2 + 1, h / 2 + 1, w / 2, h / 2);
	glScissor(w / 2 + 1, h / 2 + 1, w / 2, h / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projPerspective.data());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-10, 0, -10, 0, 0, 0, 0, 1, 0);
	glRotatef(zPhi_, 0.0f, 0.0f, 1.0f);
	glRotatef(yTheta_, 0.0f, 1.0f, 0.0f);
	glRotatef(xPsi_, 1.0f, 0.0f, 0.0f);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	GetPointLight()->Draw(renderMode_);
	if (toggleLights_ == true)
		glEnable(GL_LIGHTING);
	if (toggleTextures_ == true)
		glEnable(GL_TEXTURE_2D);
	GetGrid()->Draw(renderMode_);
	glLoadIdentity();
}

void Modeler::DrawBottomRightViewport(GLint w, GLint h, const std::array<GLfloat, 16> &projOrtho)
{
	glViewport(w / 2 + 1, 0, w / 2, h / 2);
	glScissor(w / 2 + 1, 0, w / 2, h / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projOrtho.data());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (moving_ == true && dragging_ == true && curViewport_ == "front")
	{
		frontZ_ = yo_ + panY_ / 20;
		frontX_ = xo_ - panX_ / 20;
	}
	gluLookAt(frontX_, -1, frontZ_, frontX_, 0, frontZ_, 0, 0, 1);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	GetPointLight()->Draw(renderMode_);
	if (toggleLights_ == true)
		glEnable(GL_LIGHTING);
	if (toggleTextures_ == true)
		glEnable(GL_TEXTURE_2D);
	GetGrid()->Draw(renderMode_);
	glLoadIdentity();
}

void Modeler::DrawTopLeftViewport(GLint w, GLint h, const std::array<GLfloat, 16> &projOrtho)
{
	glViewport(0, h / 2 + 1, w / 2, h / 2);
	glScissor(0, h / 2 + 1, w / 2, h / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projOrtho.data());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (moving_ == true && dragging_ == true && curViewport_ == "side")
	{
		sideY_ = yo_ + panY_ / 20;
		sideZ_ = xo_ - panX_ / 20;
	}
	gluLookAt(-1, sideY_, sideZ_, 0, sideY_, sideZ_, 0, 1, 0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	GetPointLight()->Draw(renderMode_);
	if (toggleLights_ == true)
		glEnable(GL_LIGHTING);
	if (toggleTextures_ == true)
		glEnable(GL_TEXTURE_2D);
	GetGrid()->Draw(renderMode_);
	glLoadIdentity();
}

void Modeler::DrawBottomLeftViewport(GLint w, GLint h, const std::array<GLfloat, 16> &projOrtho)
{
	glViewport(0, 0, w / 2, h / 2);
	glScissor(0, 0, w / 2, h / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projOrtho.data());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (moving_ == true && dragging_ == true && curViewport_ == "top")
	{
		topY_ = yo_ + panY_ / 20;
		topX_ = xo_ - panX_ / 20;
	}
	gluLookAt(topX_, topY_, 1, topX_, topY_, 0, 0, 1, 0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	GetPointLight()->Draw(renderMode_);
	if (toggleLights_ == true)
		glEnable(GL_LIGHTING);
	if (toggleTextures_ == true)
		glEnable(GL_TEXTURE_2D);
	GetGrid()->Draw(renderMode_);
	glLoadIdentity();
}

void Modeler::Pick(const int _x, const int _y, const int _h, const std::string &_viewport)
{
	glGetIntegerv(GL_VIEWPORT, VIEWPORT);

	static GLuint select_buff[NUMBER_KEYS];
	glSelectBuffer(NUMBER_KEYS, select_buff);

	renderMode_ = GL_SELECT;
	glRenderMode(renderMode_);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((GLdouble)_x, (GLdouble)(_h - _y), 8, 8, VIEWPORT);

	if ((VIEWPORT[2]) <= (VIEWPORT[3]))
		glOrtho(-5.0, 5.0,
				-5.0 * ((GLfloat)(VIEWPORT[3]) / (GLfloat)(VIEWPORT[2])),
				5.0 * ((GLfloat)(VIEWPORT[3]) / (GLfloat)(VIEWPORT[2])),
				5.0, -200.0);
	else
		glOrtho(-5.0 * ((GLfloat)(VIEWPORT[2]) / (GLfloat)(VIEWPORT[3])),
				5.0 * ((GLfloat)(VIEWPORT[2]) / (GLfloat)(VIEWPORT[3])),
				-5.0, 5.0, 5.0, -200.0);

	glMatrixMode(GL_MODELVIEW);
	if (_viewport == "top")
	{
		glLoadIdentity();
		gluLookAt(topX_, topY_, 1, topX_, topY_, 0, 0, 1, 0);
	}
	else if (_viewport == "side")
	{
		glLoadIdentity();
		gluLookAt(-1, sideY_, sideZ_, 0, sideY_, sideZ_, 0, 1, 0);
	}
	else if (_viewport == "front")
	{
		glLoadIdentity();
		gluLookAt(frontX_, -1, frontZ_, frontX_, 0, frontZ_, 0, 0, 1);
	}

	glInitNames();
	glPushName(0);
	GetGrid()->DrawControlPoints(renderMode_);
	GetPointLight()->Draw(renderMode_);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	renderMode_ = GL_RENDER;
	GLint hits = glRenderMode(renderMode_);
	ProcessPicks(hits, select_buff);
	SetDragginStateDuringPicking();

	glMatrixMode(GL_MODELVIEW);
}

void Modeler::SetDragginStateDuringPicking()
{
	i_ = -1;
	j_ = -1;
	k_ = -1;
	for (GLint i = 0; i < 4; i++)
	{
		GLint j;
		for (j = 0; j < 4; j++)
		{
			if ((GLfloat)(i * 4 + j + 1) == pickIdx_)
			{
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
	for (GLint i = 1; i <= lightIdxCount_; i++)
	{
		if (pickIdx_ == ctrlPntIdxCount_ + i)
		{
			k_ = i - 1;
			dragging_ = true;
			break;
		}
	}
}

void Modeler::ProcessPicks(const GLint _hits, GLuint *_slct_bff)
{
	GLuint *select_buff = _slct_bff;
	/*====== First GLuint in select_buff is number of names in this hit ======*/
	GLuint names = *select_buff;
	/*======================== Skip min and max depth ========================*/
	select_buff += 3;

	pickIdx_ = 0;

	for (GLint i = 0; i < _hits; i++)
	{
		for (GLint j = 0; j < (GLint)names; j++)
		{
			for (GLint k = 1; k <= ctrlPntIdxCount_ + lightIdxCount_; k++)
			{
				if (*select_buff == (GLuint)k)
				{
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

void Modeler::MousePickingOnClickDown(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
{
	//========================= Quadrant 1 Click ===========================
	if (_x > _w / 2 && _y < _h / 2)
	{
		// Do Nothing.
	}
	//========================= Quadrant 2 Click ===========================
	else if (_x < _w / 2 && _y < _h / 2)
	{
		glViewport(0, _h / 2 + 1, _w / 2, _h / 2);
		curViewport_ = "side";
		Pick(_x, _y, _h, "side");
	}
	//========================= Quadrant 3 Click ===========================
	else if (_x < _w / 2 && _y > _h / 2)
	{
		glViewport(0, 0, _w / 2, _h / 2);
		curViewport_ = "top";
		Pick(_x, _y, _h, "top");
	}
	//========================= Quadrant 4 Click ===========================
	else if (_x > _w / 2 && _y > _h / 2)
	{
		glViewport(_w / 2 + 1, 0, _w / 2, _h / 2);
		curViewport_ = "front";
		Pick(_x, _y, _h, "front");
	}
}

void Modeler::MousePickingOnClickUp()
{
	dragging_ = false;
	curViewport_ = "";
}

void Modeler::MouseMovingOnClickDown(const int _x, const int _y, const int _w, const int _h)
{
	dragging_ = true;
	xi_ = _x;
	yi_ = _y;
	panX_ = 0;
	panY_ = 0;
	//========================= Quadrant 1 Click ===========================
	if (_x > _w / 2 && _y < _h / 2)
	{
		// Do Nothing.
	}
	//========================= Quadrant 2 Click ===========================
	else if (_x < _w / 2 && _y < _h / 2)
	{
		glViewport(0, _h / 2 + 1, _w / 2, _h / 2);
		curViewport_ = "side";
		xo_ = sideZ_;
		yo_ = sideY_;
	}
	//========================= Quadrant 3 Click ===========================
	else if (_x < _w / 2 && _y > _h / 2)
	{
		glViewport(0, 0, _w / 2, _h / 2);
		curViewport_ = "top";
		xo_ = topX_;
		yo_ = topY_;
	}
	//========================= Quadrant 4 Click ===========================
	else if (_x > _w / 2 && _y > _h / 2)
	{
		glViewport(_w / 2 + 1, 0, _w / 2, _h / 2);
		curViewport_ = "front";
		xo_ = frontX_;
		yo_ = frontZ_;
	}
}

void Modeler::MouseMovingOnClickUp()
{
	dragging_ = false;
	xi_ = 0;
	yi_ = 0;
	xf_ = 0;
	yf_ = 0;
	curViewport_ = "";
}

void Modeler::Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
{
	if (picking_ == true && _button == GLUT_LEFT_BUTTON && _state == GLUT_DOWN)
	{
		MousePickingOnClickDown(_button, _state, _x, _y, _w, _h);
	}
	else if (picking_ == true && dragging_ == true &&
			 _button == GLUT_LEFT_BUTTON && _state == GLUT_UP)
	{
		MousePickingOnClickUp();
	}
	else if (moving_ == true &&
			 _button == GLUT_LEFT_BUTTON && _state == GLUT_DOWN)
	{
		MouseMovingOnClickDown(_x, _y, _w, _h);
	}
	else if (moving_ == true && dragging_ == true &&
			 _button == GLUT_LEFT_BUTTON && _state == GLUT_UP)
	{
		MouseMovingOnClickUp();
	}
}

void Modeler::MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
{
	if (picking_ == true && dragging_ == true)
	{
		//========================= Quadrant 1 Motion ==========================
		if (_x > _w / 2 && _y < _h / 2)
		{
			// Do Nothing
		}
		//========================= Quadrant 2 Motion ==========================
		else if (curViewport_ == "side" &&
				 _x < _w / 2 && _y < _h / 2 && _x > 0 && _y > 0)
		{
			MouseMotionQuadrantTwo(_x, _y, _w, _h, _projOrtho);
		}
		//========================= Quadrant 3 Motion ==========================
		else if (curViewport_ == "top" &&
				 _x < _w / 2 && _y > _h / 2 && _x > 0 && _y < _h)
		{
			MouseMotionQuadrantThree(_x, _y, _w, _h, _projOrtho);
		}
		//========================= Quadrant 4 Motion ==========================
		else if (curViewport_ == "front" &&
				 _x > _w / 2 && _y > _h / 2 && _x < _w && _y < _h)
		{
			MouseMotionQuadrantFour(_x, _y, _w, _h, _projOrtho);
		}
	}
	else if (moving_ == true && dragging_ == true)
	{
		xf_ = _x;
		yf_ = _y;
		panX_ = xf_ - xi_;
		panY_ = yf_ - yi_;
	}
}

void Modeler::MouseMotionQuadrantTwo(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
{
	glViewport(0, _h / 2 + 1, _w / 2, _h / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_projOrtho.data());
	glGetDoublev(GL_PROJECTION_MATRIX, PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1, sideY_, sideZ_, 0, sideY_, sideZ_, 0, 1, 0);
	glGetDoublev(GL_MODELVIEW_MATRIX, MODELVIEW);
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, VIEWPORT);

	GLint success = gluUnProject(_x, _y, 0,
								 MODELVIEW, PROJECTION, VIEWPORT,
								 &MOUSEX, &MOUSEY, &MOUSEZ);

	if (success == 1)
	{
		MOUSEY += 10;
		MOUSEY *= -1;
		MOUSEY += 2 * sideY_;
	}

	if (k_ == -1)
	{
		GetGrid()->SetControlPoint((GLfloat)MOUSEY, i_, j_, 1);
		GetGrid()->SetControlPoint((GLfloat)MOUSEZ, i_, j_, 2);
	}
	else
	{
		GetPointLight()->GetPosition()[k_][1] = (GLfloat)MOUSEY;
		GetPointLight()->GetPosition()[k_][2] = (GLfloat)MOUSEZ;
		glLightfv(GL_LIGHT0, GL_POSITION, GetPointLight()->GetPosition()[0].data());
		glLightfv(GL_LIGHT1, GL_POSITION, GetPointLight()->GetPosition()[1].data());
	}
}
void Modeler::MouseMotionQuadrantThree(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
{
	glViewport(0, 0, _w / 2, _h / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_projOrtho.data());
	glGetDoublev(GL_PROJECTION_MATRIX, PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(topX_, topY_, 1, topX_, topY_, 0, 0, 1, 0);
	glGetDoublev(GL_MODELVIEW_MATRIX, MODELVIEW);
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, VIEWPORT);

	GLint success = gluUnProject(_x, _y, 0,
								 MODELVIEW, PROJECTION, VIEWPORT,
								 &MOUSEX, &MOUSEY, &MOUSEZ);

	if (success == 1)
	{
		MOUSEY = 10 - MOUSEY;
		MOUSEY += 2 * topY_;
	}

	if (k_ == -1)
	{
		GetGrid()->SetControlPoint((GLfloat)MOUSEX, i_, j_, 0);
		GetGrid()->SetControlPoint((GLfloat)MOUSEY, i_, j_, 1);
	}
	else
	{
		GetPointLight()->GetPosition()[k_][0] = (GLfloat)MOUSEX;
		GetPointLight()->GetPosition()[k_][1] = (GLfloat)MOUSEY;
		glLightfv(GL_LIGHT0, GL_POSITION, GetPointLight()->GetPosition()[0].data());
		glLightfv(GL_LIGHT1, GL_POSITION, GetPointLight()->GetPosition()[1].data());
	}
}
void Modeler::MouseMotionQuadrantFour(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
{
	glViewport(_w / 2 + 1, 0, _w / 2, _h / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_projOrtho.data());
	glGetDoublev(GL_PROJECTION_MATRIX, PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(frontX_, -1, frontZ_, frontX_, 0, frontZ_, 0, 0, 1);
	glGetDoublev(GL_MODELVIEW_MATRIX, MODELVIEW);
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, VIEWPORT);

	GLint success = gluUnProject(_x, _y, 0,
								 MODELVIEW, PROJECTION, VIEWPORT,
								 &MOUSEX, &MOUSEY, &MOUSEZ);

	if (success == 1)
	{
		MOUSEZ -= 10;
		MOUSEZ *= -1;
		MOUSEZ += 2 * frontZ_;
	}

	if (k_ == -1)
	{
		GetGrid()->SetControlPoint((GLfloat)MOUSEX, i_, j_, 0);
		GetGrid()->SetControlPoint((GLfloat)MOUSEZ, i_, j_, 2);
	}
	else
	{
		GetPointLight()->GetPosition()[k_][0] = (GLfloat)MOUSEX;
		GetPointLight()->GetPosition()[k_][2] = (GLfloat)MOUSEZ;
		glLightfv(GL_LIGHT0, GL_POSITION, GetPointLight()->GetPosition()[0].data());
		glLightfv(GL_LIGHT1, GL_POSITION, GetPointLight()->GetPosition()[1].data());
	}
}

void Modeler::ActionMenu(const int _index)
{
	switch (_index)
	{
	case 0:
		picking_ = !picking_;
		moving_ = !moving_;
		if (picking_ == false)
		{
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

void Modeler::X(const bool isLowerCase)
{
	if (isLowerCase)
	{
		xPsi_ += 1.5f;
		if (xPsi_ > 360.0f)
			xPsi_ -= 360.0f;
	}
	else
	{
		xPsi_ += -1.5f;
		if (xPsi_ < -360.0f)
			xPsi_ += 360.0f;
	}
}

void Modeler::Y(const bool isLowerCase)
{
	if (isLowerCase)
	{
		yTheta_ += 1.5f;
		if (yTheta_ > 360.0f)
			yTheta_ -= 360.0f;
	}
	else
	{
		yTheta_ += -1.5f;
		if (yTheta_ < -360.0f)
			yTheta_ += 360.0f;
	}
}

void Modeler::Z(const bool isLowerCase)
{
	if (isLowerCase)
	{
		zPhi_ += 1.5f;
		if (zPhi_ > 360.0f)
			zPhi_ -= 360.0f;
	}
	else
	{
		zPhi_ += -1.5f;
		if (zPhi_ < -360.0f)
			zPhi_ += 360.0f;
	}
}

void Modeler::T(const bool isLowerCase)
{
	if (isLowerCase)
	{
		toggleTextures_ = !toggleTextures_;
	}
	else
	{
		GetGrid()->ChangeTextures();
	}
	glutPostRedisplay();
}

void Modeler::L()
{
	toggleLights_ = !toggleLights_;
	glutPostRedisplay();
}
