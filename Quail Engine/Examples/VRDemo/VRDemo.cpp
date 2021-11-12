#include "VRDemo.h"

void VRDemo::OnInitialize()
{
	application.Initialize();
}

void VRDemo::OnUpdate()
{
	application.Update();
}

void VRDemo::OnGui()
{
}

void VRDemo::OnClose()
{
	application.Destroy();
}

void VRDemo::OnKey(KeyEvent key)
{
}
