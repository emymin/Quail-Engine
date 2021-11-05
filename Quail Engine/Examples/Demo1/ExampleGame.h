#pragma once
#include "Behaviour.h"
#include "NoClipController.h"
class ExampleGame : public Behaviour
{

public:
	ExampleGame() { name = "Quail Test"; }

	NoClipController controller;

	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;


	void OnKey(KeyEvent key) override;

};

