#include "Behaviour.h"

class EngineUI : Behaviour {

public:
	EngineUI() {
		name = "EngineUI";
	}

	void OnInitialize() override
	{
	}


	void OnUpdate() override
	{
	}


	void OnGui() override
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Quail Engine"))
			{
				ImGui::EndMenu();
			}

			ImGui::Text("Framerate: %1.f Render time: %.3f ms", Engine::Time().fps, Engine::Time().lastRenderTime * 1000.f);

			ImGui::EndMainMenuBar();
		}
	}


	void OnClose() override
	{
	}


	void OnKey(KeyEvent key) override
	{
		if (key.action == KeyAction::PRESS) {
			switch (key.key) {
			case Key::Esc: {Engine::SetShouldClose(); break; }
			default: {break; }
			}
		}
	}

};