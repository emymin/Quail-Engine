#include "OpenVRApplication.h"
#include "Console.h"
#include "Engine.h"

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

OpenVRApplication::OpenVRApplication() : m_width(0),m_height(0),m_instance(nullptr)
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

void OpenVRApplication::OnInitialize()
{
	Console::Log("Initializing OpenVR...");

	vr::EVRInitError err = vr::VRInitError_None;
	m_instance = vr::VR_Init(&err, vr::VRApplication_Scene);
	if (err != vr::VRInitError_None) {
		HandleInitError(err);
	}

	for (int i = vr::k_unTrackedDeviceIndex_Hmd; i < vr::k_unMaxTrackedDeviceCount; i++) {
		vr::ETrackedDeviceClass td_class = m_instance->GetTrackedDeviceClass(i);
		if (td_class != 0) {
			std::string name = GetTrackedDeviceString(m_instance, i, vr::Prop_TrackingSystemName_String);
			std::string serialNumber = GetTrackedDeviceString(m_instance, i, vr::Prop_SerialNumber_String);
			VRDeviceType type;
			if (td_class > 3) { type = VRDeviceType::Other; }
			else {
				type = (VRDeviceType)td_class;
			}
			m_devices.push_back(VRDevice{i,type,name,serialNumber,Transform()});
			
		}
	}

	if (!vr::VRCompositor()) {
		Console::Error("Failed to initialize VR compositor");
	}



	m_instance->GetRecommendedRenderTargetSize(&m_width, &m_height);
	Console::Log(fmt::format("Recommended resolution: {} {}", m_width, m_height));
	Console::Log("OpenVR initialization finished");

}

void OpenVRApplication::OnClose()
{
	if (m_instance)
	{
		vr::VR_Shutdown();
		m_instance = NULL;
	}
}

void OpenVRApplication::SubmitFrames(Texture* leftTex, Texture* rightTex)
{
	if (!m_instance) {
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

	((OpenVRRenderer*)Engine::GetRenderer())->application = this;
}

void OpenVRApplication::OnUpdate()
{
	if (!m_instance) {
		Console::Warning("OpenVR is not initialized, ignoring");
		return;
	}
	vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
	m_instance->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, poses, vr::k_unMaxTrackedDeviceCount);
	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
		if ((poses[i].bDeviceIsConnected) && (poses[i].bPoseIsValid)) {
			glm::vec3 position = glm::vec3(
				poses[i].mDeviceToAbsoluteTracking.m[0][3],
				poses[i].mDeviceToAbsoluteTracking.m[1][3],
				poses[i].mDeviceToAbsoluteTracking.m[2][3]
			);
			m_devices[i].transform.localPosition = position;
		}
	}

}


void OpenVRApplication::OnGui()
{
}

void OpenVRApplication::OnKey(KeyEvent key)
{
}

void OpenVRApplication::HandleInitError(vr::EVRInitError err)
{
	Console::Error(vr::VR_GetVRInitErrorAsEnglishDescription(err));
}

