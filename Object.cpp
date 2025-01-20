#include "Object.h"

#include <future>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "filesystem.hpp"

#include <boost/asio/post.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "test_filesystem_adapters/ContainerResource.h"
#include "test_filesystem_adapters/ContainerResource2D.h"

#include "Common.h"
#include "GLEntityTask.h"
#include "Object.h"

using boost::property_tree::ptree;
using _3dmodeler::GLEntity;
using _3dmodeler::GLEntityTask;
using _3dmodeler::Object;

using ResourceGLubyte = ContainerResource<GLubyte>;
using Resource2DGLfloat = ContainerResource2D<GLfloat>;

namespace
{
const std::string OBJECT_VERTICES_KEY = "object_vertices";
const std::string OBJECT_INDICES_KEY = "object_indices";
} // end namespace

std::string Object::ObjectKey()
{
	return "Object";
}

Object::Object() :
	GLEntity()
{
	objectVertices_ = Resource2DGLfloat({
		{-0.5f,-0.5f,0.5f}, {0.5f,-0.0f,0.5f},
		{0.5f,0.0f,0.5f}, {-0.5f,0.5f,0.5f},
		{-0.5f,-0.5f,1.0f}, {0.1f,-0.0f,1.0f},
		{0.1f,0.0f,1.0f}, {-0.5f,0.5f,1.0f}
	});

	objectIndices_ = ResourceGLubyte({ 0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4 });
}

Object::Object(const Object::Key& key) :
	Object()
{
	SetKey(key);
}

Object::~Object() = default;
Object::Object(const Object&) = default;
Object::Object(Object&&) = default;
Object& Object::operator=(const Object&) = default;
Object& Object::operator=(Object&&) = default;

void Object::Draw()
{
	// TODO: Draw Grid, PointLight, and UI instead
	//glPushMatrix();

	//glVertexPointer(3, GL_FLOAT, 0, objectVertices_.Data());
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glLoadIdentity();
	//glTranslatef(GetFrame().GetData(0,0), GetFrame().GetData(1,0), GetFrame().GetData(2,0));
	////glRotatef(orientationAngle_*(180.0f / M_PI), 0.0f, 0.0f, 1.0f);
	//glDrawElements(GL_LINE_LOOP, 24, GL_UNSIGNED_BYTE, objectIndices_.Data());

	//glPopMatrix();
}

const Resource2DGLfloat& Object::GetObjectVertices() const
{
	return objectVertices_;
}

const ResourceGLubyte& Object::GetObjectIndices() const
{
	return objectIndices_;
}
