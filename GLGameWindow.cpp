#include "GLGameWindow.h"

#include <array>
#include <string>

#include "Entities/Entity.h"

using entity::Entity;

using _3dmodeler::GLGameWindow;

namespace
{
const std::string GAME_WIN_KEY = "GameWindow";
const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 480;
const int INIT_WIN_X = 100;
const int INIT_WIN_Y = 100;
} // end namespace

GLGameWindow::~GLGameWindow() = default;

GLGameWindow::GLGameWindow() : Entity()
{
	SetKey(GAME_WIN_KEY);

	std::fill(projOrtho_.begin(), projOrtho_.end(), 0.0f);
	std::fill(projPerspective_.begin(), projPerspective_.end(), 0.0f);

	w_ = WIN_WIDTH;
	h_ = WIN_HEIGHT;
}

void GLGameWindow::SetHeight(const GLint h) {
	h_ = h;
}

void GLGameWindow::SetWidth(const GLint w) {
	w_ = w;
}

void GLGameWindow::SetProjOrthoMatrix(std::array<GLfloat, 16> projOrtho) {
	projOrtho_ = std::move(projOrtho);
}

void GLGameWindow::SetProjOrthoMatrix(const GLfloat val, const int index) {
	projOrtho_[index] = val;
}

void GLGameWindow::SetProjPerspectiveMatrix(std::array<GLfloat, 16> projPerspective) {
	projPerspective_ = std::move(projPerspective);
}

void GLGameWindow::SetProjPerspectiveMatrix(const GLfloat val, const int index) {
	projPerspective_[index] = val;
}

GLint GLGameWindow::GetHeight() const {
	return h_;
}

GLint GLGameWindow::GetWidth() const {
	return w_;
}

const std::array<GLfloat, 16>& GLGameWindow::GetProjOrthoMatrix() const {
	return projOrtho_;
}

const std::array<GLfloat, 16>& GLGameWindow::GetProjPerspectiveMatrix() const {
	return projPerspective_;
}