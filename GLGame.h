#ifndef _3dmodeler_glgame_h
#define _3dmodeler_glgame_h

#include <array>
#include <memory>

#include "Entities/Entity.h"

#include "config.h"

#include "GLGameEmitters.h"
#include "GLGameWindow.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT GLGame : public entity::Entity
{
public:
	GLGame(int _argc, char* _argv[]);
	virtual ~GLGame();
	GLGame(const GLGame&) = delete;
	GLGame(GLGame&&) = delete;
	GLGame& operator=(const GLGame&) = delete;
	GLGame& operator=(GLGame&&) = delete;

	void Run();
	static void TimerCallback(int _idx);

	GLGameEmitters& GetEmitters();
	GLGameWindow& GetGameWindow();

	static GLGame* callbackInstance_;

private:
	GLGameEmitters emitters_;

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

	void MouseMotion(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16>& _projOrtho);
	static void MouseMotionWrapper(const int _x, const int _y);

	void ActionMenu(const int _index);
	static void ActionMenuWrapper(const int _index);

	// helper functions
	void KeyboardUpdateState();

	// members
	GLGameWindow gameWindow_;

	std::array<bool, 256> keysPressed_;
};

} // end _3dmodeler
#endif // _3dmodeler_glgame_h
