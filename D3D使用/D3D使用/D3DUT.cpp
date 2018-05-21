#pragma once
#include "D3DUT.h"


bool InitWindow(HINSTANCE hInstance, int width, int height, bool windowed)
{
	/*
	初始化窗体参数并注册win窗体
	*/
	WNDCLASS _wc;
	_wc.style = CS_HREDRAW | CS_VREDRAW;		//窗口类的样式，0代表默认
	_wc.lpfnWndProc = (WNDPROC)D3DWndProc;		//指定窗口处理函数
	_wc.cbClsExtra = 0;		//窗口类扩展
	_wc.cbWndExtra = 0;		//窗口的扩展
	_wc.hInstance = hInstance;		//指定窗口的句柄
	_wc.hIcon = LoadIcon(0, IDI_WINLOGO);		//图标句柄
	_wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//加载光标的举兵
	_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//制定画刷颜色
	_wc.lpszMenuName = NULL;		//设置菜单名字
	_wc.lpszClassName = TEXT("MyWndClass");		//设置窗口类的名字

	if (!RegisterClass(&_wc))
	{
		MessageBox(0, L"RegisterClass-FAILED", 0, 0);
		return false;
	}
	

	/*
	实例化窗口
	*/
	_hwnd = CreateWindow(TEXT("MyWndClass"),	//指向已注册的窗口类名
		TEXT("标题"),								//创建的窗口名称  
		WS_OVERLAPPEDWINDOW,						//窗口样式
		CW_USEDEFAULT,								//水平位置
		CW_USEDEFAULT,								//垂直位置
		width,										//窗口宽度
		height,										//窗口高度
		NULL,										//父窗口句柄
		NULL,										//菜单
		hInstance,									//句柄
		NULL);										//用于检测窗口是否创建成功，如果成功则返回窗口句柄，若失败返回null，通常设置为null

	if (_hwnd == 0)
	{
		MessageBox(0, L"CreateWindow()-FAILED", 0, 0);
		return false;
	}
	/*
	显示并更新窗口
	*/
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
	return true;
}


bool InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType, IDirect3DDevice9 ** device)
{
	//--------------初始化DirectX-----------
	IDirect3D9 *_d3d9 = createIDirect3D9Object(D3D_SDK_VERSION);
	if (!_d3d9)
	{
		MessageBox(0, L"DirectX create failed", 0, 0);
		return false;
	}

	int vp = checkHardware(_d3d9);
	D3DPRESENT_PARAMETERS _d3dpp;
	D3DSWAPEFFECTInit(_d3dpp, _hwnd,width,height,windowed);
	_d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, _hwnd, vp, &_d3dpp, device);
	_d3d9->Release();
	return true;
}

LRESULT  D3DWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	//调用缺省的窗口过程来为应用程序没有处理的任何窗口消息提供缺省的处理。  
	//该函数确保每一个消息得到处理  
	return DefWindowProc(hWnd, message, wParam, lParam);
}

IDirect3D9 * createIDirect3D9Object(int _d3dSdkVersion)
{
	return Direct3DCreate9(_d3dSdkVersion);
}

int checkHardware(IDirect3D9 * d3d9)
{
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int vp = 0;
	if (caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	return vp;
}

void D3DSWAPEFFECTInit(D3DPRESENT_PARAMETERS & d3dpp, HWND hwnd, int width, int height, bool windowed)
{
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
