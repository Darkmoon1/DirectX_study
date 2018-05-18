#include "DirectX.h"


IDirect3D9* myDirectX::createIDirect3D9Object(int _d3dSdkVersion)
{
	return Direct3DCreate9(_d3dSdkVersion);
}
/*
const 声明形参表示在函数体中该参数的值不可被修改 ，是用于保护数据的一种方式
*/
int myDirectX::checkHardware(IDirect3D9* d3d9)
{
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, &caps);
	int vp = 0;
	if (caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	return vp;
}
void myDirectX::D3DSWAPEFFECTInit(D3DPRESENT_PARAMETERS &d3dpp,HWND hwnd)
{
	d3dpp.BackBufferWidth = 640;
	d3dpp.BackBufferHeight = 480;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


}

myDirectX::myDirectX()
{
}

myDirectX::~myDirectX()
{
}

