#include "modeler/ModelerConsumers.h"

#include <array>
#include <memory>
#include <string>

#include "Entities/Entity.h"
#include "Events/EventConsumer.h"

#include "configuration/config.h"
#include "configuration/filesystem.h"
#include "modeler/Modeler.h"

using _3dmodeler::Modeler;
using _3dmodeler::ModelerConsumers;
using entity::Entity;
using events::EventConsumer;
using StdConsumer = EventConsumer<void(void)>;

namespace
{
	const std::string MODELER_CONSUMERS_KEY = "ModelerConsumers";
} // end namespace

ModelerConsumers::ModelerConsumers(std::shared_ptr<Modeler> modeler) : Entity(),
																	   xConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												{ modeler->X(true); })),
																	   yConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												{ modeler->Y(true); })),
																	   zConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												{ modeler->Z(true); })),
																	   tConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												{ modeler->T(true); })),
																	   lConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												{ modeler->L(); })),
																	   xCapConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												   { modeler->X(false); })),
																	   yCapConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												   { modeler->Y(false); })),
																	   zCapConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												   { modeler->Z(false); })),
																	   tCapConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												   { modeler->T(false); })),
																	   lCapConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												   { modeler->L(); })),
																	   runConsumer_(std::make_shared<StdConsumer>([this, modeler]()
																												  { modeler->Run(); })),
																	   drawConsumer_(std::make_shared<EventConsumer<
																						 void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>(
																		   [this, modeler](GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)
																		   {
																			   modeler->Draw(w_, h_, projOrtho_, projPerspective_);
																		   })),

																	   pickConsumer_(std::make_shared<EventConsumer<
																						 void(const int _x, const int _y, const int _h, const std::string &_viewport)>>(
																		   [this, modeler](const int _x, const int _y, const int _h, const std::string &_viewport)
																		   {
																			   modeler->Pick(_x, _y, _h, _viewport);
																		   })),

																	   mouseConsumer_(std::make_shared<EventConsumer<
																						  void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>(
																		   [this, modeler](const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)
																		   {
																			   modeler->Mouse(_button, _state, _x, _y, _w, _h);
																		   })),

																	   mouseMotionConsumer_(std::make_shared<EventConsumer<
																								void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>(
																		   [this, modeler](const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)
																		   {
																			   modeler->MouseMotion(_x, _y, _w, _h, _projOrtho);
																		   })),

																	   actionMenuConsumer_(std::make_shared<EventConsumer<
																							   void(const int _index)>>(
																		   [this, modeler](const int _index)
																		   {
																			   modeler->ActionMenu(_index);
																		   }))
{
	SetKey(MODELER_CONSUMERS_KEY);
}

ModelerConsumers::~ModelerConsumers() = default;

std::shared_ptr<StdConsumer> ModelerConsumers::GetXConsumer()
{
	return xConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetYConsumer()
{
	return yConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetZConsumer()
{
	return zConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetTConsumer()
{
	return tConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetLConsumer()
{
	return lConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetXCapConsumer()
{
	return xCapConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetYCapConsumer()
{
	return yCapConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetZCapConsumer()
{
	return zCapConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetTCapConsumer()
{
	return tCapConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetLCapConsumer()
{
	return lCapConsumer_;
}

std::shared_ptr<EventConsumer<
	void(GLint w_, GLint h_, const std::array<GLfloat, 16> &projOrtho_, const std::array<GLfloat, 16> &projPerspective_)>>
ModelerConsumers::GetDrawConsumer()
{
	return drawConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _x, const int _y, const int _h, const std::string &_viewport)>>
ModelerConsumers::GetPickConsumer()
{
	return pickConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _button, const int _state, const int _x, const int _y, const int _w, const int _h)>>
ModelerConsumers::GetMouseConsumer()
{
	return mouseConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _x, const int _y, const int _w, const int _h, const std::array<GLfloat, 16> &_projOrtho)>>
ModelerConsumers::GetMouseMotionConsumer()
{
	return mouseMotionConsumer_;
}

std::shared_ptr<EventConsumer<
	void(const int _index)>>
ModelerConsumers::GetActionMenuConsumer()
{
	return actionMenuConsumer_;
}

std::shared_ptr<StdConsumer> ModelerConsumers::GetRunConsumer()
{
	return runConsumer_;
}
