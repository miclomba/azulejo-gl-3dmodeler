#include "Modeler.h"

#include <algorithm>
#include <cstdlib>
#include <future>
#include <memory>
#include <stdio.h>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "filesystem.hpp"

#include <boost/asio/packaged_task.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Events/EventConsumer.h"
#include "test_filesystem_adapters/ContainerResource2D.h"

#include "Common.h"
#include "GLEntityTask.h"
#include "Object.h"

using boost::property_tree::ptree;

using _3dmodeler::Modeler;
using _3dmodeler::GLEntityTask;
using events::EventConsumer;
using entity::Entity;

namespace pt = boost::property_tree;

namespace
{
const std::string _3DMODELER_KEY = "3DModeler";
} // end namespace

Modeler::Modeler() :
	threadPool_(std::thread::hardware_concurrency() > 1 ? std::thread::hardware_concurrency() - 1 : 1)
{
	SetKey(_3DMODELER_KEY);

	AggregateMember(Object::ObjectKey());
	SharedEntity& obj = GetObj();
	obj = std::make_shared<Object>(Object::ObjectKey());

	leftArrowConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->RotateLeft(); });
	rightArrowConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->RotateRight(); });

	drawConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Draw(); });
	runConsumer_ = std::make_shared<EventConsumer<void(void)>>([this]() { this->Run(); });
}

Modeler::~Modeler() = default;

void Modeler::Run()
{
}

Modeler::SharedEntity& Modeler::GetObj()
{
	return GetAggregatedMember(Object::ObjectKey());
}

void Modeler::DrawGLEntities()
{
	std::vector<std::future<GLEntity*>> futures;

	SharedEntity& obj = GetObj();
	if (obj)
	{
		GLEntity* glObj = dynamic_cast<GLEntity*>(obj.get());
		GLEntityTask task([glObj, this]() { /*UpdateShipTask(ship, bulletFutures);*/ return glObj; });
		futures.push_back(task.GetFuture());

		boost::asio::post(threadPool_, task);
	}

	for (std::future<GLEntity*>& future : futures)
		future.get()->Draw();
}

void Modeler::DrawGameInfo()
{
	glColor3f(0.0f, 1.0f, 1.0f);

	GLint i;
	glRasterPos3f(7.5f, -9.0f, 0.0f);
	char reset[16] = { 'P','r','e','s','s',' ','X',' ','t','o',' ',
					  'R','E','S','E','T' };
	for (i = 0; i < 16; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, reset[i]);
}

void Modeler::Draw()
{
	DrawGLEntities();
	DrawGameInfo();
}

void Modeler::RotateLeft()
{
	orientationAngle_ = 0.15f; 
}

void Modeler::RotateRight()
{
	orientationAngle_ = -0.15f; 
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetLeftArrowConsumer()
{
	return leftArrowConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetRightArrowConsumer()
{
	return rightArrowConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetDrawConsumer()
{
	return drawConsumer_;
}

std::shared_ptr<EventConsumer<void(void)>> Modeler::GetRunConsumer()
{
	return runConsumer_;
}
