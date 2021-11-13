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
public:
    OpenVRApplication* application;
    OpenVRRenderer();
    void Initialize();
    virtual void Clear() const override;
    virtual void Draw(const Scene* scene) const override;
};

