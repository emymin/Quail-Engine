#pragma once
#include "Engine.h"

class NoClipController {
private:
	bool firstMouse = true;
public:
	Transform* transform;
	float speed;
	float sensitivity = 0.01f;
	MouseInfo lastMouse;
	NoClipController() : transform(nullptr), speed(5.f) {}
	NoClipController(Transform* transform, float speed = 5.f) : transform(transform), speed(speed) {}

	void Update() {
		if (!Engine::IsFocused()) {
			firstMouse = true;
			return;
		}
		if (transform != nullptr) {
			float deltaTime = Engine::Time().deltaTime;

			MouseInfo currentMouse = Engine::GetMouse();
			float dx = currentMouse.xPos - lastMouse.xPos;
			float dy = currentMouse.yPos - lastMouse.yPos;
			lastMouse = currentMouse;

			if (firstMouse) { firstMouse = false; }
			else {
				glm::vec3 yawAxis = glm::vec3(0, 1, 0);
				glm::vec3 pitchAxis = transform->RotateDirection(glm::vec3(1, 0, 0));

				transform->localRotation = glm::angleAxis(sensitivity * dx, yawAxis) * transform->localRotation;
				transform->localRotation = glm::angleAxis(sensitivity * dy, pitchAxis) * transform->localRotation;
			}

			glm::vec3 direction = glm::vec3(0);
			float multiplier = 1.f;

			if (Engine::GetKey(W).action == PRESS) { direction += glm::vec3(0, 0, 1); }
			if (Engine::GetKey(S).action == PRESS) { direction += glm::vec3(0, 0, -1); }
			if (Engine::GetKey(A).action == PRESS) { direction += glm::vec3(-1, 0, 0); }
			if (Engine::GetKey(D).action == PRESS) { direction += glm::vec3(1, 0, 0); }
			if (Engine::GetKey(S).action == PRESS) { direction += glm::vec3(0, 0, -1); }
			if (Engine::GetKey(Q).action == PRESS) { direction += glm::vec3(0, -1, 0); }
			if (Engine::GetKey(E).action == PRESS) { direction += glm::vec3(0, 1, 0); }
			if (Engine::GetKey(LeftShift).action == PRESS) { multiplier = 2.f; }

			if (direction != glm::vec3(0)) {
				direction = normalize(direction);
				direction = transform->RotateDirection(direction);
				transform->localPosition += direction * speed * multiplier * deltaTime;
			}
		}
	}
};