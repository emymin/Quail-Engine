#include "OpenVRApplication.h"
#include "Console.h"
#include "Engine.h"
#include <glm/gtx/matrix_decompose.hpp>

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

glm::mat4 OpenVRApplication::toGLM(const vr::HmdMatrix34_t& m)
{
	glm::mat4 result = glm::mat4(
		m.m[0][0], m.m[1][0], m.m[2][0], 0.0,
		m.m[0][1], m.m[1][1], m.m[2][1], 0.0,
		m.m[0][2], m.m[1][2], m.m[2][2], 0.0,
		m.m[0][3], m.m[1][3], m.m[2][3], 1.0f);
	return result;
}

vr::HmdMatrix34_t OpenVRApplication::toOpenVR(const glm::mat4& m)
{
	vr::HmdMatrix34_t result;
	for (uint8_t i = 0; i < 3; ++i) {
		for (uint8_t j = 0; j < 4; ++j) {
			result.m[i][j] = m[j][i];
		}
	}
	return result;
}

vr::IVRSystem* OpenVRApplication::m_instance;

std::vector<VRDevice> OpenVRApplication::m_devices;

unsigned int OpenVRApplication::m_height;

unsigned int OpenVRApplication::m_width;


void OpenVRApplication::Initialize()
{
	Console::Log("Initializing OpenVR...");
	
	if (!vr::VR_IsHmdPresent()) {
		Console::Error("VR headset not detected!");
		return;
	}
	if (!vr::VR_IsRuntimeInstalled()) {
		Console::Error("OpenVR runtime not installed!");
		return;
	}

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
			m_devices.push_back(VRDevice{i,type,name,serialNumber,glm::mat4(1.0f)});
			
		}
	}

	if (!vr::VRCompositor()) {
		Console::Error("Failed to initialize VR compositor");
	}



	m_instance->GetRecommendedRenderTargetSize(&m_width, &m_height);
	Console::Log(fmt::format("Recommended resolution: {} {}", m_width, m_height));
	Console::Log("OpenVR initialization finished");

}

void OpenVRApplication::Destroy()
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

	leftTex->Bind();
	vr::Texture_t leftEyeTexture = { (void*)(leftTex->GetRendererID()),textureType,colorSpace };
	rightTex->Bind();
	vr::Texture_t rightEyeTexture = { (void*)(rightTex->GetRendererID()),textureType,colorSpace };

	vr::VRCompositor()->WaitGetPoses(nullptr, 0, nullptr, 0);

	vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	vr::VRCompositor()->PostPresentHandoff();

}

void OpenVRApplication::Update()
{
	if (!m_instance) {
		Console::Warning("OpenVR is not initialized, ignoring");
		return;
	}
	UpdatePoses();

}


unsigned int OpenVRApplication::GetWidth()
{
	return m_width;
}

unsigned int OpenVRApplication::GetHeight()
{
	return m_height;
}

VRDevice* OpenVRApplication::GetHeadset()
{
	return &m_devices[0];
}

glm::mat4 OpenVRApplication::GetProjectionMatrix(vr::Hmd_Eye eye)
{
	vr::HmdMatrix44_t steamvr_proj_matrix = m_instance->GetProjectionMatrix(eye, 0.1f, 15.f);

	return glm::mat4(steamvr_proj_matrix.m[0][0], steamvr_proj_matrix.m[1][0], steamvr_proj_matrix.m[2][0], steamvr_proj_matrix.m[3][0],
		steamvr_proj_matrix.m[0][1], steamvr_proj_matrix.m[1][1], steamvr_proj_matrix.m[2][1], steamvr_proj_matrix.m[3][1],
		steamvr_proj_matrix.m[0][2], steamvr_proj_matrix.m[1][2], steamvr_proj_matrix.m[2][2], steamvr_proj_matrix.m[3][2],
		steamvr_proj_matrix.m[0][3], steamvr_proj_matrix.m[1][3], steamvr_proj_matrix.m[2][3], steamvr_proj_matrix.m[3][3]);
}

glm::mat4 OpenVRApplication::GetViewMatrix(vr::Hmd_Eye eye)
{
	vr::HmdMatrix34_t steamvr_eye_view_matrix = m_instance->GetEyeToHeadTransform(eye);

	glm::mat4 view_matrix = glm::mat4(steamvr_eye_view_matrix.m[0][0], steamvr_eye_view_matrix.m[1][0], steamvr_eye_view_matrix.m[2][0], 0.0f,
		steamvr_eye_view_matrix.m[0][1], steamvr_eye_view_matrix.m[1][1], steamvr_eye_view_matrix.m[2][1], 0.0f,
		steamvr_eye_view_matrix.m[0][2], steamvr_eye_view_matrix.m[1][2], steamvr_eye_view_matrix.m[2][2], 0.0f,
		steamvr_eye_view_matrix.m[0][3], steamvr_eye_view_matrix.m[1][3], steamvr_eye_view_matrix.m[2][3], 1.0f);

	return glm::inverse(view_matrix);
}

void OpenVRApplication::HandleInitError(vr::EVRInitError err)
{
	Console::Error(vr::VR_GetVRInitErrorAsEnglishDescription(err));
}

void OpenVRApplication::UpdatePoses()
{
	vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
	m_instance->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, poses, vr::k_unMaxTrackedDeviceCount);
	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
		if ((poses[i].bDeviceIsConnected) && (poses[i].bPoseIsValid)) {
			vr::HmdMatrix34_t matrix = poses[i].mDeviceToAbsoluteTracking;
			glm::mat4 transform_matrix = toGLM(matrix);
			m_devices[i].transformation_matrix = transform_matrix;
		}
	}
}

