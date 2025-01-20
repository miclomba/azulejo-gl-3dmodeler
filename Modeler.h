#ifndef _3dmodeler_3dmodeler_h
#define	_3dmodeler_3dmodeler_h

#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <boost/asio/thread_pool.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Events/EventConsumer.h"

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

	std::shared_ptr<events::EventConsumer<void(void)>> GetXConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetYConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetZConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetTConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetLConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetXCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetYCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetZCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetTCapConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetLCapConsumer();

	std::shared_ptr<events::EventConsumer<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> GetDrawConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> GetPickConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> GetMouseConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> GetMouseMotionConsumer();
	std::shared_ptr<events::EventConsumer<
		void(const int _index)
	>> GetActionMenuConsumer();

	std::shared_ptr<events::EventConsumer<void(void)>> GetRunConsumer();

private:
	// commands
	void Draw(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_);
	void Pick(const int _x, const int _y, const int _h, const std::string& _viewport);
	void Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);
	void MouseMotion(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho);
	void ActionMenu(const int _index);
	void ProcessPicks(const GLint _hits, GLuint* _slct_bff);

	void X(const bool isLowerCase);
	void Y(const bool isLowerCase);
	void Z(const bool isLowerCase);
	void T(const bool isLowerCase);
	void L();

	void Run();

	SharedEntity& GetObj();

	void DrawGLEntities();
	void DrawGameInfo();

	boost::asio::thread_pool threadPool_;

	std::shared_ptr<events::EventConsumer<void(void)>> xConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> yConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> zConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> tConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> lConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> xCapConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> yCapConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> zCapConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> tCapConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> lCapConsumer_;

	std::shared_ptr<events::EventConsumer<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> drawConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> pickConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> mouseConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> mouseMotionConsumer_;
	std::shared_ptr<events::EventConsumer<
		void(const int _index)
	>> actionMenuConsumer_;

	std::shared_ptr<events::EventConsumer<void(void)>> runConsumer_;

	// geometry members
	std::unique_ptr<Grid> grid_;
	std::unique_ptr<PointLight> lights_;
	std::unique_ptr<UserInterface> userInterf_;

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
#endif	// _3dmodeler_3dmodeler_h

