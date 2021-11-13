#pragma once
#include "Renderer.h"
#include "OpenVRApplication.h"

class OpenVRApplication;

class OpenVRRenderer :
    public Renderer
{
public:
    OpenVRApplication* application;
    virtual void Clear() const override;
    virtual void Draw(const Scene* scene) const override;
};

