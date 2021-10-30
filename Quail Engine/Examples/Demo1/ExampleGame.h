#pragma once
#include "Game.h"
class ExampleGame : public Game
{

public:
	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;

};

