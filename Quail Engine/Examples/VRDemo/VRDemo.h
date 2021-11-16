#pragma once
#include "Behaviour.h"
#include "OpenVRApplication.h"
#include "NoClipController.h"
class VRDemo :
    public Behaviour
{
public:
	NoClipController controller;
	GameObject* cube;

	GameObject* leftCube;
	GameObject* rightCube;

	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;


	void OnKey(KeyEvent key) override;

};

