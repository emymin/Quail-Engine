#pragma once
#include <openvr.h>
#include "Texture.h"


class OpenVRApplication
{
public:
	OpenVRApplication();
	void Initialize();
	void Destroy();
	void SubmitFrames(Texture* leftTex,Texture* rightTex);
	void Update();
private:
	void PrintTrackedDevices();
	void HandleInitError(vr::EVRInitError err);
	static std::string GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = NULL);
	vr::IVRSystem* hmd;
	unsigned int width, height;
};

