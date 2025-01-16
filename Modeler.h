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

	std::shared_ptr<events::EventConsumer<void(void)>> GetLeftArrowConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetRightArrowConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetDrawConsumer();
	std::shared_ptr<events::EventConsumer<void(void)>> GetRunConsumer();

private:
	// commands
	void Draw() override;
	void RotateLeft();
	void RotateRight();
	void Run();

	SharedEntity& GetObj();

	void DrawGLEntities();
	void DrawGameInfo();

	GLfloat orientationAngle_{ 0.0f };

	boost::asio::thread_pool threadPool_;

	std::shared_ptr<events::EventConsumer<void(void)>> leftArrowConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> rightArrowConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> drawConsumer_;
	std::shared_ptr<events::EventConsumer<void(void)>> runConsumer_;
};

} // end _3dmodeler
#endif	// _3dmodeler_3dmodeler_h

