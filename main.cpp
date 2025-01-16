#include <stdlib.h>
#include <string>

#include "Events/EventChannel.h"

#include "Modeler.h"
#include "GLGame.h"
#include "MeshEditor.h"

using _3dmodeler::Modeler;
using _3dmodeler::GLGame;
using _3dmodeler::MeshEditor;
using events::EventChannel;

namespace
{
const int TIME = 25;
const int VAL = 0;
const std::string LEFT_EVENT = "left_event";
const std::string LEFT_ACTION = "left_action";
const std::string RIGHT_EVENT = "right_event";
const std::string RIGHT_ACTION = "right_action";

const std::string DRAW_EVENT = "draw_event";
const std::string DRAW_ACTION = "draw_action";
const std::string RUN_EVENT = "run_event";
const std::string RUN_ACTION = "run_action";
}

void RegisterEvents(Modeler& modeler, GLGame& game, EventChannel& channel)
{
	channel.RegisterEmitter(LEFT_EVENT, game.GetLeftArrowEmitter());
	channel.RegisterConsumer(LEFT_ACTION, LEFT_EVENT, modeler.GetLeftArrowConsumer());
	channel.RegisterEmitter(RIGHT_EVENT, game.GetRightArrowEmitter());
	channel.RegisterConsumer(RIGHT_ACTION, RIGHT_EVENT, modeler.GetRightArrowConsumer());

	channel.RegisterEmitter(DRAW_EVENT, game.GetDrawEmitter());
	channel.RegisterConsumer(DRAW_ACTION, DRAW_EVENT, modeler.GetDrawConsumer());
	channel.RegisterEmitter(RUN_EVENT, game.GetRunEmitter());
	channel.RegisterConsumer(RUN_ACTION, RUN_EVENT, modeler.GetRunConsumer());
}

int main(int _argc, char* _argv[]) 
{
	//GLGame game(_argc,_argv);
	//glutTimerFunc(TIME,game.TimerCallback,VAL);

	//Modeler modeler;
	//EventChannel channel;

	//RegisterEvents(modeler, game, channel);

	//game.Run();

	MeshEditor editor(_argc, _argv);
	editor.run();
}
