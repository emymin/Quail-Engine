#pragma once
#include "Game.h"
#include "NoClipController.h"
class Demo2 : public Game
{
public:
	Demo2(){ name = "NekoWave"; }
	std::vector<GameObject*> nekocubes;
	NoClipController controller;
	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;


	void OnKey(KeyEvent key) override;

};

