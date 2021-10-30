#pragma once
#include "Game.h"
class Demo2 : public Game
{
public:
	std::vector<GameObject*> nekocubes;
	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;

};

