#ifndef _3dmodeler_glgame_window_h
#define _3dmodeler_glgame_window_h

#include <array>
#include <memory>

#include "Entities/Entity.h"

#include "config.h"

namespace _3dmodeler {

	class _3DMODELER_DLL_EXPORT GLGameWindow : public entity::Entity
	{
	public:
		GLGameWindow();
		virtual ~GLGameWindow();
		GLGameWindow(const GLGameWindow&) = delete;
		GLGameWindow(GLGameWindow&&) = delete;
		GLGameWindow& operator=(const GLGameWindow&) = delete;
		GLGameWindow& operator=(GLGameWindow&&) = delete;

		GLint GetWidth() const;
		GLint GetHeight() const;
		const std::array<GLfloat, 16>& GetProjOrthoMatrix() const;
		const std::array<GLfloat, 16>& GetProjPerspectiveMatrix() const;

		void SetWidth(const GLint w);
		void SetHeight(const GLint h);
		void SetProjOrthoMatrix(std::array<GLfloat, 16> projOrtho);
		void SetProjPerspectiveMatrix(std::array<GLfloat, 16> projPerspective);
		void SetProjOrthoMatrix(const GLfloat val, const int index);
		void SetProjPerspectiveMatrix(const GLfloat val, const int index);

	private:
		GLint w_;
		GLint h_;
		std::array<GLfloat, 16> projOrtho_;
		std::array<GLfloat, 16> projPerspective_;
	};

} // end _3dmodeler
#endif // _3dmodeler_glgame_window_h
