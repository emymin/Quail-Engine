#pragma once
#include "Behaviour.h"
class RotateBehaviour : Behaviour {
private:
	Transform* target;
	glm::vec3 axis;
	float speed;
public:
	RotateBehaviour(Transform* transform, glm::vec3 axis=glm::vec3(0,1,0),float speed=1.f) : target(transform), axis(axis),speed(speed) {}

	void OnUpdate() override
	{
		target->Rotate(speed*Engine::Time().deltaTime, axis);
	}



	void OnInitialize() override
	{
	}


	void OnGui() override
	{
	}


	void OnClose() override
	{
	}


	void OnKey(KeyEvent key) override
	{
	}

};