#pragma once
#include "Engine.h"

class NoClipController {
public:
	Transform* transform;
	float speed;
	NoClipController() : transform(nullptr), speed(speed) {}
	NoClipController(Transform* transform, float speed = 1.f) : transform(transform), speed(speed) {}

	void Update() {
		if (transform != nullptr) {
			glm::vec3 direction = glm::vec3(0);
			float deltaTime = Engine::Time().deltaTime;
			float multiplier = 1.f;

			if (Engine::GetKey(W).action == PRESS) { direction += glm::vec3(0, 0, 1); }
			if (Engine::GetKey(S).action == PRESS) { direction += glm::vec3(0, 0, -1); }
			if (Engine::GetKey(A).action == PRESS) { direction += glm::vec3(1, 0, 0); }
			if (Engine::GetKey(D).action == PRESS) { direction += glm::vec3(-1, 0, 0); }
			if (Engine::GetKey(S).action == PRESS) { direction += glm::vec3(0, 0, -1); }
			if (Engine::GetKey(Q).action == PRESS) { direction += glm::vec3(0, 1, 0); }
			if (Engine::GetKey(E).action == PRESS) { direction += glm::vec3(0, -1, 0); }
			if (Engine::GetKey(LeftShift).action == PRESS) { multiplier = 2.f; }

			if (direction != glm::vec3(0)) {
				direction = normalize(direction);
				transform->localPosition += direction * speed * multiplier * deltaTime;
			}
		}
	}
};