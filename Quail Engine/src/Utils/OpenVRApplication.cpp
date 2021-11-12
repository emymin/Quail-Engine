#include "OpenVRApplication.h"
#include "Console.h"

std::string OpenVRApplication::GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError /*= NULL*/)
{
	uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, NULL, 0, peError);
	if (unRequiredBufferLen == 0)
		return "";

	char* pchBuffer = new char[unRequiredBufferLen];
	unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, pchBuffer, unRequiredBufferLen, peError);
	std::string sResult = pchBuffer;
	delete[] pchBuffer;
	return sResult;
}

OpenVRApplication::OpenVRApplication() : width(0),height(0),hmd(nullptr)
{
	if (!vr::VR_IsHmdPresent()) {
		Console::Error("VR headset not detected!");
		return;
	}
	if (!vr::VR_IsRuntimeInstalled()) {
		Console::Error("OpenVR runtime not installed!");
		return;
	}
}

void OpenVRApplication::Initialize()
{
	vr::EVRInitError err = vr::VRInitError_None;
	hmd = vr::VR_Init(&err, vr::VRApplication_Scene);
	if (err != vr::VRInitError_None) {
		HandleInitError(err);
	}

	PrintTrackedDevices();

	if (!vr::VRCompositor()) {
		Console::Error("Failed to initialize VR compositor");
	}

	hmd->GetRecommendedRenderTargetSize(&width, &height);
	Console::Log(fmt::format("Recommended resolution: {} {}", width, height));
	Console::Log("OpenVR initialization finished");

}

void OpenVRApplication::Destroy()
{
	if (hmd)
	{
		vr::VR_Shutdown();
		hmd = NULL;
	}
}

void OpenVRApplication::SubmitFrames(Texture* leftTex, Texture* rightTex)
{
	if (!hmd) {
		Console::Warning("Submitting frames to uninitialized headset, ignoring...");
		return;
	}

	vr::EColorSpace colorSpace = vr::ColorSpace_Gamma;
	vr::ETextureType textureType = vr::TextureType_OpenGL;

	vr::Texture_t leftEyeTexture = { (void*)leftTex->GetRendererID(),textureType,colorSpace };
	vr::Texture_t rightEyeTexture = { (void*)rightTex->GetRendererID(),textureType,colorSpace };

	vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	vr::VRCompositor()->PostPresentHandoff();
}

void OpenVRApplication::Update()
{
	if (!hmd) {
		Console::Warning("OpenVR is not initialized, ignoring");
		return;
	}
	vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
	hmd->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, poses, vr::k_unMaxTrackedDeviceCount);
	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
		if ((poses[i].bDeviceIsConnected) && (poses[i].bPoseIsValid)) {
			glm::vec3 position = glm::vec3(
				poses[i].mDeviceToAbsoluteTracking.m[0][3],
				poses[i].mDeviceToAbsoluteTracking.m[1][3],
				poses[i].mDeviceToAbsoluteTracking.m[2][3]
			);
			Console::Log(fmt::format("Device ID {} position: {} {} {}", i, position.x,position.y,position.z));
		}
	}
}

void OpenVRApplication::PrintTrackedDevices()
{
	for (int i = vr::k_unTrackedDeviceIndex_Hmd; i < vr::k_unMaxTrackedDeviceCount; i++) {

		vr::ETrackedDeviceClass td_class = hmd->GetTrackedDeviceClass(i);
		if (td_class != 0) {
			std::string classname;
			switch (td_class) {
			case 1: {
				classname = "HMD";
				break;
			}
			case 2: {
				classname = "Controller";
				break;
			}
			case 3: {
				classname = "Tracker";
				break;
			}
			default: {
				classname = "Other";
				break;
			}
			}

			std::string td_name = GetTrackedDeviceString(hmd, i, vr::Prop_TrackingSystemName_String);
			Console::Log(fmt::format("Device ID {}: {} {}",i, classname, td_name));

		}
	}
}

void OpenVRApplication::HandleInitError(vr::EVRInitError err)
{
	Console::Error(vr::VR_GetVRInitErrorAsEnglishDescription(err));
}

