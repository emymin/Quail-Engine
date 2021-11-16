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

class VRDevice {
public:
	int id;
	VRDeviceType deviceType;
	std::string name;
	std::string serialNumber;
	glm::mat4 GetPose() const { return transformation_matrix; }
	Transform transform;
private:
	VRDevice(int id, VRDeviceType type, std::string name, std::string serialNumber) : id(id), deviceType(type), name(name), serialNumber(serialNumber) {}
	glm::mat4 transformation_matrix;
	friend class OpenVRApplication;
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
	static VRDevice* GetLeftController();
	static VRDevice* GetRightController();

	static glm::mat4 GetProjectionMatrix(vr::Hmd_Eye eye);
	static glm::mat4 GetHeadToEyeMatrix(vr::Hmd_Eye eye);

	inline static glm::mat4 toGLM(const vr::HmdMatrix34_t& m);
	inline static vr::HmdMatrix34_t toOpenVR(const glm::mat4& m);
	inline static glm::quat toQuaternion(const vr::HmdMatrix34_t& matrix);

	static void UpdatePoses();

	static glm::mat4 leftProjectionMatrix;
	static glm::mat4 rightProjectionMatrix;
	static glm::mat4 leftHeadtoEyeMatrix;
	static glm::mat4 rightHeadtoEyeMatrix;

	static Transform playSpace;

private:
	static void HandleInitError(vr::EVRInitError err);
	static std::string GetTrackedDeviceString(vr::IVRSystem* pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError* peError = NULL);
	

	static unsigned int m_width, m_height;
	static vr::IVRSystem* m_instance;
	static std::vector<VRDevice> m_devices;
	static vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
};

