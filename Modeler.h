#ifndef _3dmodeler_modeler_h
#define	_3dmodeler_modeler_h

#include <array>
#include <memory>
#include <string>

#include <boost/asio/thread_pool.hpp>

#include "config.h"
#include "GLEntity.h"

#include "Grid.h"
#include "PointLight.h"
#include "UserInterface.h"

namespace _3dmodeler{

class _3DMODELER_DLL_EXPORT Modeler : public GLEntity
{
public:
	Modeler();
	~Modeler();
	Modeler(const Modeler&) = delete;
	Modeler(Modeler&&) = delete;
	Modeler & operator=(const Modeler&) = delete;
	Modeler & operator=(Modeler&&) = delete;

	void Draw(GLint w_, GLint h_, const std::array<GLfloat, 16>& projOrtho_, const std::array<GLfloat, 16>& projPerspective_);
	
	void Pick(const int _x, const int _y, const int _h, const std::string& _viewport);
	void SetDragginStateDuringPicking();

	void Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);
	void MouseMovingOnClickDown(const int _x, const int _y, const int _w, const int _h);
	void MouseMovingOnClickUp();
	void MousePickingOnClickDown(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);
	void MousePickingOnClickUp();

	void MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho);
	void MouseMotionQuadrantTwo(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho);
	void MouseMotionQuadrantThree(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho);
	void MouseMotionQuadrantFour(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho);
	
	void ActionMenu(const int _index);
	void ProcessPicks(const GLint _hits, GLuint* _slct_bff);

	void X(const bool isLowerCase);
	void Y(const bool isLowerCase);
	void Z(const bool isLowerCase);
	void T(const bool isLowerCase);
	void L();

	void Run();

private:
	PointLight* const GetPointLight();
	UserInterface* GetUserInterface();
	Grid* GetGrid();

	void DrawGameInfo();
	void DrawBottomLeftViewport(GLint w, GLint h, const std::array<GLfloat, 16>& projOrtho);
	void DrawTopLeftViewport(GLint w, GLint h, const std::array<GLfloat, 16>& projOrtho);
	void DrawBottomRightViewport(GLint w, GLint h, const std::array<GLfloat, 16>& projOrtho);
	void DrawTopRightViewport(GLint w, GLint h, const std::array<GLfloat, 16>& projPerspective);

	boost::asio::thread_pool threadPool_;

	bool toggleLights_;
	bool toggleTextures_;

	std::string curViewport_;
	bool picking_;
	bool dragging_;
	GLint i_;
	GLint j_;
	GLint k_;
	GLint pickIdx_;
	GLint ctrlPntIdxCount_;
	GLint lightIdxCount_;
	GLenum renderMode_;

	bool moving_;
	GLfloat xo_;
	GLfloat yo_;
	GLfloat xi_;
	GLfloat yi_;
	GLfloat xf_;
	GLfloat yf_;
	GLfloat panX_;
	GLfloat panY_;
	GLfloat frontX_;
	GLfloat frontZ_;
	GLfloat sideZ_;
	GLfloat sideY_;
	GLfloat topX_;
	GLfloat topY_;

	GLfloat zPhi_;
	GLfloat yTheta_;
	GLfloat xPsi_;
};

} // end _3dmodeler
#endif	// _3dmodeler_modeler_h

