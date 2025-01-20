#include <stdlib.h>
#include <string>

#include "Events/EventChannel.h"

#include "Modeler.h"
#include "GLGame.h"

using _3dmodeler::Modeler;
using _3dmodeler::GLGame;
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

void RegisterEvents(Modeler& modeler, GLGame& game, EventChannel& channel)
{
	channel.RegisterEmitter(X_EVENT, game.GetXEmitter());
	channel.RegisterConsumer(X_ACTION, X_EVENT, modeler.GetXConsumer());
	channel.RegisterEmitter(Y_EVENT, game.GetYEmitter());
	channel.RegisterConsumer(Y_ACTION, Y_EVENT, modeler.GetYConsumer());
	channel.RegisterEmitter(Z_EVENT, game.GetZEmitter());
	channel.RegisterConsumer(Z_ACTION, Z_EVENT, modeler.GetZConsumer());
	channel.RegisterEmitter(T_EVENT, game.GetTEmitter());
	channel.RegisterConsumer(T_ACTION, T_EVENT, modeler.GetTConsumer());
	channel.RegisterEmitter(L_EVENT, game.GetLEmitter());
	channel.RegisterConsumer(L_ACTION, L_EVENT, modeler.GetLConsumer());

	channel.RegisterEmitter(X_CAP_EVENT, game.GetXCapEmitter());
	channel.RegisterConsumer(X_CAP_ACTION, X_CAP_EVENT, modeler.GetXCapConsumer());
	channel.RegisterEmitter(Y_CAP_EVENT, game.GetYCapEmitter());
	channel.RegisterConsumer(Y_CAP_ACTION, Y_CAP_EVENT, modeler.GetYCapConsumer());
	channel.RegisterEmitter(Z_CAP_EVENT, game.GetZCapEmitter());
	channel.RegisterConsumer(Z_CAP_ACTION, Z_CAP_EVENT, modeler.GetZCapConsumer());
	channel.RegisterEmitter(T_CAP_EVENT, game.GetTCapEmitter());
	channel.RegisterConsumer(T_CAP_ACTION, T_CAP_EVENT, modeler.GetTCapConsumer());
	channel.RegisterEmitter(L_CAP_EVENT, game.GetLCapEmitter());
	channel.RegisterConsumer(L_CAP_ACTION, L_CAP_EVENT, modeler.GetLCapConsumer());

	channel.RegisterEmitter(DRAW_EVENT, game.GetDrawEmitter());
	channel.RegisterConsumer(DRAW_ACTION, DRAW_EVENT, modeler.GetDrawConsumer());
	channel.RegisterEmitter(PICK_EVENT, game.GetPickEmitter());
	channel.RegisterConsumer(PICK_ACTION, PICK_EVENT, modeler.GetPickConsumer());
	channel.RegisterEmitter(MOUS_EVENT, game.GetMouseEmitter());
	channel.RegisterConsumer(MOUS_ACTION, MOUS_EVENT, modeler.GetMouseConsumer());
	channel.RegisterEmitter(MOUSE_MOTION_EVENT, game.GetMouseMotionEmitter());
	channel.RegisterConsumer(MOUSE_MOTION_ACTION, MOUSE_MOTION_EVENT, modeler.GetMouseMotionConsumer());
	channel.RegisterEmitter(ACTION_MENU_EVENT, game.GetActionMenuEmitter());
	channel.RegisterConsumer(ACTION_MENU_ACTION, ACTION_MENU_EVENT, modeler.GetActionMenuConsumer());

	channel.RegisterEmitter(RUN_EVENT, game.GetRunEmitter());
	channel.RegisterConsumer(RUN_ACTION, RUN_EVENT, modeler.GetRunConsumer());
}

int main(int _argc, char* _argv[]) 
{
	GLGame game(_argc,_argv);
	glutTimerFunc(TIME,game.TimerCallback,VAL);

	Modeler modeler;
	EventChannel channel;

	RegisterEvents(modeler, game, channel);

	game.Run();
}
