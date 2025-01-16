#ifndef _3dmodeler_object_h
#define	_3dmodeler_object_h

#include <array>
#include <future>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <boost/asio/thread_pool.hpp>
#include <boost/property_tree/ptree.hpp>

#include "test_filesystem_adapters/ContainerResource.h"
#include "test_filesystem_adapters/ContainerResource2D.h"

#include "config.h"
#include "GLEntity.h"

namespace _3dmodeler {

using ResourceGLubyte = ContainerResource<GLubyte>;
using ResourceGLfloat = ContainerResource<GLfloat>;
using Resource2DGLfloat = ContainerResource2D<GLfloat>;

class _3DMODELER_DLL_EXPORT Object : public GLEntity
{
public:
	Object();
	Object(const Object::Key& key);
	~Object();
	Object(const Object&);
	Object(Object&&);
	Object& operator=(const Object&);
	Object& operator=(Object&&);

	void Draw() override;

	static std::string ObjectKey();

	const Resource2DGLfloat& GetObjectVertices() const;
	const ResourceGLubyte& GetObjectIndices() const;

private:

    Resource2DGLfloat objectVertices_;
	ResourceGLubyte objectIndices_;
};

} // end object
#endif	// _3dmodeler_object_h 

