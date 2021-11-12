#pragma once
#include "Behaviour.h"
#include "OpenVRApplication.h"
class VRDemo :
    public Behaviour
{
public:
	OpenVRApplication application;

	void OnInitialize() override;


	void OnUpdate() override;


	void OnGui() override;


	void OnClose() override;


	void OnKey(KeyEvent key) override;

};

