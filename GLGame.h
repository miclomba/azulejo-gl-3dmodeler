#ifndef _3dmodeler_glgame_h
#define _3dmodeler_glgame_h

#include <array>
#include <memory>

#include "Events/EventEmitter.h"

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT GLGame
{
public:
	GLGame(int _argc, char* _argv[]);
	~GLGame();
	GLGame(const GLGame&) = delete;
	GLGame(GLGame&&) = delete;
	GLGame& operator=(const GLGame&) = delete;
	GLGame& operator=(GLGame&&) = delete;

	void Run();
	static void TimerCallback(int _idx);

	std::shared_ptr<events::EventEmitter<void(void)>> GetXEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetYEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetZEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetTEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetLEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetXCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetYCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetZCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetTCapEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetLCapEmitter();

	std::shared_ptr<events::EventEmitter<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> GetDrawEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> GetPickEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> GetMouseEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> GetMouseMotionEmitter();
	std::shared_ptr<events::EventEmitter<
		void(const int _index)
	>> GetActionMenuEmitter();
	std::shared_ptr<events::EventEmitter<void(void)>> GetRunEmitter();

	static GLGame* callbackInstance_;

private:
	// GLUT Initialization
	void InitGlut(int _argc, char* _argv[]) const;
	void InitActionMenu() const;
	void InitServer() const;
	void InitClient() const;

	// GLUT callbacks
	void RegisterCallbacks() const;

	void Display();
	static void DisplayWrapper();

	void Reshape(const int _w, const int _h);
	static void ReshapeWrapper(const int _w, const int _h);

	void Keyboard(const unsigned char _chr, const int _x, const int _y);
	static void KeyboardWrapper(unsigned char _chr, int _x, int _y);

	void KeyboardUp(const unsigned char _chr, const int _x, const int _y);
	static void KeyboardUpWrapper(const unsigned char _chr, const int _x, const int _y);

	void Pick(const int _x, const int _y, const int _h, const std::string& _viewport);
	static void PickWrapper(const int _x, const int _y, const std::string& _viewport);

	void Mouse(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h);
	static void MouseWrapper(const int _button, const int _state, const int _x, const int _y);

	void MouseMotion(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho);
	static void MouseMotionWrapper(const int _x, const int _y);

	void ActionMenu(const int _index);
	static void ActionMenuWrapper(const int _index);

	// helper functions
	void KeyboardUpdateState();

	// keyboard input emitters
	std::shared_ptr<events::EventEmitter<void(void)>> xEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> yEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> zEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> tEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> lEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> xCapEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> yCapEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> zCapEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> tCapEmitter_;
	std::shared_ptr<events::EventEmitter<void(void)>> lCapEmitter_;

	// other emitters
	std::shared_ptr<events::EventEmitter<
		void(GLint w_, GLint h_, GLfloat* projOrtho_, GLfloat* projPerspective_)
	>> drawEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _h, const std::string& _viewport)
	>> pickEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
	>> mouseEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _x, const int _y, const int _w, const int _h, GLfloat* const _projOrtho)
	>> mouseMotionEmitter_;
	std::shared_ptr<events::EventEmitter<
		void(const int _index)
	>> actionMenuEmitter_;

	std::shared_ptr<events::EventEmitter<void(void)>> runEmitter_;

	// members
	std::array<bool, 256> keysPressed_;

	// window and projection
	GLint w_;
	GLint h_;
	GLfloat projOrtho_[16];
	GLfloat projPerspective_[16];
};

} // end _3dmodeler
#endif // _3dmodeler_glgame_h
