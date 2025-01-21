#include <memory>
#include <string>

#include "Events/EventChannel.h"

#include "Modeler.h"
#include "ModelerConsumers.h"
#include "GLGame.h"
#include "GLGameEmitters.h"

using _3dmodeler::Modeler;
using _3dmodeler::ModelerConsumers;
using _3dmodeler::GLGame;
using _3dmodeler::GLGameEmitters;
using events::EventChannel;

namespace
{
const int TIME = 25;
const int VAL = 0;
const std::string X_EVENT = "x_event";
const std::string X_ACTION = "x_action";
const std::string Y_EVENT = "y_event";
const std::string Y_ACTION = "y_action";
const std::string Z_EVENT = "z_event";
const std::string Z_ACTION = "z_action";
const std::string T_EVENT = "t_event";
const std::string T_ACTION = "t_action";
const std::string L_EVENT = "l_event";
const std::string L_ACTION = "l_action";
const std::string X_CAP_EVENT = "x_cap_event";
const std::string X_CAP_ACTION = "x_cap_action";
const std::string Y_CAP_EVENT = "y_cap_event";
const std::string Y_CAP_ACTION = "y_cap_action";
const std::string Z_CAP_EVENT = "z_cap_event";
const std::string Z_CAP_ACTION = "z_cap_action";
const std::string T_CAP_EVENT = "t_cap_event";
const std::string T_CAP_ACTION = "t_cap_action";
const std::string L_CAP_EVENT = "l_cap_event";
const std::string L_CAP_ACTION = "l_cap_action";

const std::string DRAW_EVENT = "draw_event";
const std::string DRAW_ACTION = "draw_action";
const std::string PICK_EVENT = "pick_event";
const std::string PICK_ACTION = "pick_action";
const std::string MOUS_EVENT = "mouse_event";
const std::string MOUS_ACTION = "mouse_action";
const std::string MOUSE_MOTION_EVENT = "mouse_motion_event";
const std::string MOUSE_MOTION_ACTION = "mouse_motion_action";
const std::string ACTION_MENU_EVENT = "action_menu_event";
const std::string ACTION_MENU_ACTION = "action_menu_action";
const std::string RUN_EVENT = "run_event";
const std::string RUN_ACTION = "run_action";
}

void RegisterEvents(ModelerConsumers& consumers, GLGameEmitters& emitters, EventChannel& channel)
{
	channel.RegisterEmitter(X_EVENT, emitters.GetXEmitter());
	channel.RegisterConsumer(X_ACTION, X_EVENT, consumers.GetXConsumer());
	channel.RegisterEmitter(Y_EVENT, emitters.GetYEmitter());
	channel.RegisterConsumer(Y_ACTION, Y_EVENT, consumers.GetYConsumer());
	channel.RegisterEmitter(Z_EVENT, emitters.GetZEmitter());
	channel.RegisterConsumer(Z_ACTION, Z_EVENT, consumers.GetZConsumer());
	channel.RegisterEmitter(T_EVENT, emitters.GetTEmitter());
	channel.RegisterConsumer(T_ACTION, T_EVENT, consumers.GetTConsumer());
	channel.RegisterEmitter(L_EVENT, emitters.GetLEmitter());
	channel.RegisterConsumer(L_ACTION, L_EVENT, consumers.GetLConsumer());

	channel.RegisterEmitter(X_CAP_EVENT, emitters.GetXCapEmitter());
	channel.RegisterConsumer(X_CAP_ACTION, X_CAP_EVENT, consumers.GetXCapConsumer());
	channel.RegisterEmitter(Y_CAP_EVENT, emitters.GetYCapEmitter());
	channel.RegisterConsumer(Y_CAP_ACTION, Y_CAP_EVENT, consumers.GetYCapConsumer());
	channel.RegisterEmitter(Z_CAP_EVENT, emitters.GetZCapEmitter());
	channel.RegisterConsumer(Z_CAP_ACTION, Z_CAP_EVENT, consumers.GetZCapConsumer());
	channel.RegisterEmitter(T_CAP_EVENT, emitters.GetTCapEmitter());
	channel.RegisterConsumer(T_CAP_ACTION, T_CAP_EVENT, consumers.GetTCapConsumer());
	channel.RegisterEmitter(L_CAP_EVENT, emitters.GetLCapEmitter());
	channel.RegisterConsumer(L_CAP_ACTION, L_CAP_EVENT, consumers.GetLCapConsumer());

	channel.RegisterEmitter(DRAW_EVENT, emitters.GetDrawEmitter());
	channel.RegisterConsumer(DRAW_ACTION, DRAW_EVENT, consumers.GetDrawConsumer());
	channel.RegisterEmitter(PICK_EVENT, emitters.GetPickEmitter());
	channel.RegisterConsumer(PICK_ACTION, PICK_EVENT, consumers.GetPickConsumer());
	channel.RegisterEmitter(MOUS_EVENT, emitters.GetMouseEmitter());
	channel.RegisterConsumer(MOUS_ACTION, MOUS_EVENT, consumers.GetMouseConsumer());
	channel.RegisterEmitter(MOUSE_MOTION_EVENT, emitters.GetMouseMotionEmitter());
	channel.RegisterConsumer(MOUSE_MOTION_ACTION, MOUSE_MOTION_EVENT, consumers.GetMouseMotionConsumer());
	channel.RegisterEmitter(ACTION_MENU_EVENT, emitters.GetActionMenuEmitter());
	channel.RegisterConsumer(ACTION_MENU_ACTION, ACTION_MENU_EVENT, consumers.GetActionMenuConsumer());

	channel.RegisterEmitter(RUN_EVENT, emitters.GetRunEmitter());
	channel.RegisterConsumer(RUN_ACTION, RUN_EVENT, consumers.GetRunConsumer());
}

int main(int _argc, char* _argv[]) 
{
	GLGame game(_argc,_argv);
	glutTimerFunc(TIME,game.TimerCallback,VAL);
	GLGameEmitters& emitters = game.GetEmitters();

	auto modeler = std::make_shared<Modeler>();
	ModelerConsumers consumers(modeler);
	EventChannel channel;

	RegisterEvents(consumers, game.GetEmitters(), channel);

	game.Run();
}
