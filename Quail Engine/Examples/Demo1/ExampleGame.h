#pragma once
#include "Game.h"
class ExampleGame : public Game
{

public:
	ExampleGame() { name = "Quail Test"; }

	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;

};

