#pragma once
#include "Renderer.h"
#include "FrameBuffer.h"
#include "OpenVRApplication.h"

class OpenVRApplication;

class OpenVRRenderer :
    public Renderer
{
public:
    OpenVRRenderer();
    virtual void Clear() const override;
    virtual void Draw(const Scene* scene) const override;

    void OnResize(unsigned int width, unsigned int height) override;

private:
    FrameBuffer* m_leftEyeBuffer;
    FrameBuffer* m_rightEyeBuffer;
    unsigned int m_width, m_height;

    Mesh m_screenMesh;
    Shader* m_screenShader;

    void DrawToScreen()const;
};


