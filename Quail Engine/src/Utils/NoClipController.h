#pragma once
#include "Engine.h"

class NoClipController {
private:
	bool firstMouse = true;
public:
	Transform* transform;
	float speed;
	float sensitivity = 0.007f;
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
				dx *= sensitivity;
				dy *= sensitivity;

				glm::vec3 yawAxis = glm::vec3(0, 1, 0);
				glm::vec3 pitchAxis = transform->Right();

				glm::vec3 euler = transform->eulerAngles();
				float dirSign = glm::dot(transform->Forward(), glm::vec3(0, 1, 0)) > 0 ? 1 : -1;

				if ( (abs(euler.x) <= (PI / 2.f)) || (dirSign * dy < 0)){
					transform->Rotate(-dy, pitchAxis);
				}
				transform->Rotate(-dx, yawAxis);
			}

			glm::vec3 direction = glm::vec3(0);
			float multiplier = 1.f;

			if (Engine::GetKey(Key::W).action == KeyAction::PRESS) { direction += -transform->Forward(); }
			if (Engine::GetKey(Key::S).action == KeyAction::PRESS) { direction += transform->Forward(); }
			if (Engine::GetKey(Key::A).action == KeyAction::PRESS) { direction += -transform->Right(); }
			if (Engine::GetKey(Key::D).action == KeyAction::PRESS) { direction += transform->Right(); }
			if (Engine::GetKey(Key::Q).action == KeyAction::PRESS) { direction += -transform->Up(); }
			if (Engine::GetKey(Key::E).action == KeyAction::PRESS) { direction += transform->Up(); }
			if (Engine::GetKey(Key::LeftShift).action == KeyAction::PRESS) { multiplier = 2.f; }

			if (direction != glm::vec3(0)) {
				direction = normalize(direction);
				transform->localPosition += direction * speed * multiplier * deltaTime;
			}
		}
	}
};