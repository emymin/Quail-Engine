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
	glm::mat4 transformation_matrix;
	glm::vec3 GetPosition() { return transformation_matrix[3]; }
};

class OpenVRApplication
{
public:
	static void Initialize();
	static void Destroy();
	static void SubmitFrames(Texture* leftTex,Texture* rightTex);

	static unsigned int GetWidth();
	static unsigned int GetHeight();

	static VRDevice* GetDevice(unsigned int index);
	static VRDevice* GetHeadset();

	static glm::mat4 GetProjectionMatrix(vr::Hmd_Eye eye);
	static glm::mat4 GetHeadToEyeMatrix(vr::Hmd_Eye eye);

	inline static glm::mat4 toGLM(const vr::HmdMatrix34_t& m);
	inline static vr::HmdMatrix34_t toOpenVR(const glm::mat4& m);

	static void UpdatePoses();
private:
	static void HandleInitError(vr::EVRInitError err);
	static std::string GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = NULL);
	

	static unsigned int m_width, m_height;
	static vr::IVRSystem* m_instance;
	static std::vector<VRDevice> m_devices;
	static vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
};

