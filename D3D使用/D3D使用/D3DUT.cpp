#pragma once
#include "D3DUT.h"


bool InitWindow(HINSTANCE hInstance, int width, int height, bool windowed)
{
	/*
	��ʼ�����������ע��win����
	*/
	WNDCLASS _wc;
	_wc.style = CS_HREDRAW | CS_VREDRAW;		//���������ʽ��0����Ĭ��
	_wc.lpfnWndProc = (WNDPROC)D3DWndProc;		//ָ�����ڴ�����
	_wc.cbClsExtra = 0;		//��������չ
	_wc.cbWndExtra = 0;		//���ڵ���չ
	_wc.hInstance = hInstance;		//ָ�����ڵľ��
	_wc.hIcon = LoadIcon(0, IDI_WINLOGO);		//ͼ����
	_wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���ع��ľٱ�
	_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//�ƶ���ˢ��ɫ
	_wc.lpszMenuName = NULL;		//���ò˵�����
	_wc.lpszClassName = TEXT("MyWndClass");		//���ô����������

	if (!RegisterClass(&_wc))
	{
		MessageBox(0, L"RegisterClass-FAILED", 0, 0);
		return false;
	}
	

	/*
	ʵ��������
	*/
	_hwnd = CreateWindow(TEXT("MyWndClass"),	//ָ����ע��Ĵ�������
		TEXT("����"),								//�����Ĵ�������  
		WS_OVERLAPPEDWINDOW,						//������ʽ
		CW_USEDEFAULT,								//ˮƽλ��
		CW_USEDEFAULT,								//��ֱλ��
		width,										//���ڿ��
		height,										//���ڸ߶�
		NULL,										//�����ھ��
		NULL,										//�˵�
		hInstance,									//���
		NULL);										//���ڼ�ⴰ���Ƿ񴴽��ɹ�������ɹ��򷵻ش��ھ������ʧ�ܷ���null��ͨ������Ϊnull

	if (_hwnd == 0)
	{
		MessageBox(0, L"CreateWindow()-FAILED", 0, 0);
		return false;
	}
	/*
	��ʾ�����´���
	*/
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
	return true;
}


bool InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType, IDirect3DDevice9 ** device)
{
	//--------------��ʼ��DirectX-----------
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

	//����ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д�����κδ�����Ϣ�ṩȱʡ�Ĵ���  
	//�ú���ȷ��ÿһ����Ϣ�õ�����  
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
