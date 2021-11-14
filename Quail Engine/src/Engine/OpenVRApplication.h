#pragma once
#include <openvr.h>
#include <vector>
#include "Texture.h"
#include "Transform.h"
#include "Behaviour.h"
#include "OpenVRRenderer.h"

enum class ControllerSide {
	Left,
	Right
};
enum class VRDeviceType:int {
	Other=0,
	Headset=1,
	Controller=2,
	Tracker=3
};

struct VRDevice {
	int id;
	VRDeviceType deviceType;
	std::string name;
	std::string serialNumber;
	Transform transform;
};

class OpenVRApplication : Behaviour
{
public:
	OpenVRApplication();
	void OnInitialize()override;
	void OnClose()override;
	void SubmitFrames(Texture* leftTex,Texture* rightTex);
	void OnUpdate()override;

	void OnGui() override;
	void OnKey(KeyEvent key) override;

private:
	unsigned int m_width, m_height;
	void HandleInitError(vr::EVRInitError err);
	void UpdatePoses();
	static std::string GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = NULL);
	vr::IVRSystem* m_instance;
	std::vector<VRDevice> m_devices;

	friend class OpenVRRenderer;
};

