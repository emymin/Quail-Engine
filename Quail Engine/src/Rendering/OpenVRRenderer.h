#pragma once
#include "Renderer.h"
#include "FrameBuffer.h"
#include "OpenVRApplication.h"

class OpenVRApplication;

class OpenVRRenderer :
    public Renderer
{
private:
    FrameBuffer* m_leftEyeBuffer;
    FrameBuffer* m_rightEyeBuffer;
    unsigned int m_width, m_height;
    Mesh m_screenMesh;
    Shader* m_screenShader;
public:
    OpenVRApplication* application;
    OpenVRRenderer() :m_screenShader(&Shader::ScreenShader), m_screenMesh(Mesh::Plane(2.f)) {
        m_screenMesh.material = new Material(m_screenShader);
    }
    void Initialize();
    virtual void Clear() const override;
    virtual void Draw(const Scene* scene) const override;
};

