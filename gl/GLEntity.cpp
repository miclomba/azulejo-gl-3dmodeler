#include <string>

#include "test_filesystem_adapters/ContainerResource2D.h"

#include "Common.h"
#include "GLEntity.h"

using entity::Entity;
using _3dmodeler::GLEntity;

using Resource2DGLfloat = ContainerResource2D<GLfloat>;

namespace
{
const std::string FRAME_KEY = "frame";
const std::string S_KEY = "S";
const std::string T_KEY = "T";
const std::string R_KEY = "R";
} // end namespace

GLEntity::GLEntity() : Entity()
{
	frame_ = Resource2DGLfloat({
		{0.0,0.0,0.0,0.0},
		{0.0,0.0,0.0,0.0},
		{0.0,0.0,0.0,0.0},
		{0.0,0.0,0.0,0.0}
		});

	S_ = frame_;
	R_ = frame_;
	T_ = frame_;
}

GLEntity::~GLEntity() = default;
GLEntity::GLEntity(const GLEntity&) = default;
GLEntity::GLEntity(GLEntity&&) = default;
GLEntity& GLEntity::operator=(const GLEntity&) = default;
GLEntity& GLEntity::operator=(GLEntity&&) = default;

void GLEntity::Draw()
{
}

Resource2DGLfloat& GLEntity::GetFrame()
{
	return frame_;
}

const Resource2DGLfloat& GLEntity::SMatrix() const
{
	return S_;
}

const Resource2DGLfloat& GLEntity::TMatrix() const
{
	return T_;
}

const Resource2DGLfloat& GLEntity::RMatrix() const
{
	return R_;
}

void GLEntity::SetFrame(const int i, const int j, const GLfloat val)
{
	frame_.GetData(i,j) = val;
}

void GLEntity::SetFrame(const Resource2DGLfloat& frame)
{
	frame_ = frame;
}
