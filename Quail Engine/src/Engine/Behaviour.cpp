#include "Behaviour.h"
#include "Engine.h"

Behaviour::Behaviour()
{
	Engine::RegisterBehaviour(this);
}

