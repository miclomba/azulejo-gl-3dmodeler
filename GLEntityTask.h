#ifndef _3dmodeler_glentitytask_h
#define	_3dmodeler_glentitytask_h

#include <functional>
#include <future>
#include <memory>

#include "config.h"

namespace _3dmodeler {

class GLEntity;

struct _3DMODELER_DLL_EXPORT GLEntityTask
{
	GLEntityTask(std::function<GLEntity*()> lambda);

	void operator()();

	std::future<GLEntity*> GetFuture();

private:
	std::shared_ptr<std::packaged_task<GLEntity*()>> task_;
};

} // _3dmodeler

#endif // _3dmodeler_glentitytask
