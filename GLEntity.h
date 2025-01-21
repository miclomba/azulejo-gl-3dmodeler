#ifndef _3dmodeler_glentity_h 
#define _3dmodeler_glentity_h	

#include "config.h"

#include "Entities/Entity.h"
#include "test_filesystem_adapters/ContainerResource2D.h"

namespace _3dmodeler {

using Resource2DGLfloat = ContainerResource2D<GLfloat>;

class _3DMODELER_DLL_EXPORT GLEntity: public entity::Entity {
public:
    GLEntity();
	~GLEntity();
	GLEntity(const GLEntity&);
	GLEntity(GLEntity&&);
	GLEntity& operator=(const GLEntity&);
	GLEntity& operator=(GLEntity&&);

	virtual void Draw();

	Resource2DGLfloat& GetFrame();

	const Resource2DGLfloat& SMatrix() const;
	const Resource2DGLfloat& TMatrix() const;
	const Resource2DGLfloat& RMatrix() const;

	void SetFrame(int i, int j, GLfloat val);
	void SetFrame(const Resource2DGLfloat& frame);

protected:
	Resource2DGLfloat S_;
	Resource2DGLfloat T_;
	Resource2DGLfloat R_;

private:

	Resource2DGLfloat frame_;
};

} // end _3dmodeler

#endif // _3dmodeler_glentity_h	
