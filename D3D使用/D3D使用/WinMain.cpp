#pragma once

#include "MyD3D.h"
#include <Windows.h>



/*
win32����Ĭ�Ͻ��뺯��
hInstance ��ǰӦ�ó����ʵ�����
hPrevInstance �Ѿ�����̭�Ĳ�������Ҫд�ϣ���Ϊnull
lpCmdLIne �Կ���ֹ���ַ�����ָ�����ݸ�Ӧ�ó���������в�����
nCmdLine ָ��Ӧ�ó��򴰿ڵ���ʾ��ʽ�������أ���󻯣���С���ȣ���ֵ��ΪShowWindow�����Ĳ���ʹ�á�
*/

//IDirect3DDevice9* Device = 0;
MyD3D _device;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int width = 720;
	int height = 480;
	bool windowed = true;

	if (_device.CreateDevice(hInstance, width, height))
	{
		_device.Initialize();
	}

	
	/*
	��Ϣѭ��
	WINUSERAPI BOOL WINAPI GetMessage(
	_out LPMSG lpMSG,				ָ����Ϣ�ṹ���ָ�룬�ýṹ�屣����ȡ����Ϣ���е���Ϣ
	_in_opt HWND hWnd,				ָ����Ϣ�����Ĵ��ڣ�NULL��ʾ�������ڵ�ǰ�߳����еĴ��ڵ���Ϣ
	_in UINT wMsgFilterMin,			ָ��ָ��Ҫ���ܵ���Ϣ����Сֵ��һ����Ϊ0
	_in UINT wMsgFilterMax			ָ��Ҫ���ܵ���Ϣ�����ֵ�����MIN��MAX��Ϊ0 ��ʾ�������е���Ϣ

	PeekMessage()ǰ�ĸ�������GetMessage��ͬ������������Ϊ��Ϣ����֮������Ϣ������ɾ���������ɾ��
	*/
	MSG _msg;
	ZeroMemory(&_msg, sizeof(MSG));
	
	static float _lastTime = (float)timeGetTime();


	while (_msg.message!=WM_QUIT)
	{
		if (PeekMessage(&_msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}
		else
		{
			//if (Device)
			//{
			//	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

			//	Device->Present(0, 0, 0, 0);
			//}

			float _currTime = (float)timeGetTime();
			float _deltaTime = (_currTime - _lastTime)*0.001f;

			
			_device.FrameMove(_deltaTime);
			_device.Render();

			
			_lastTime = _currTime;
		}
	}
	//ѭ�����̣���ͬ��Ϸ��ʵʱ��Ⱦ�͹���

	_device.Release();
	return 0;
}


/*
ִ�й����еĻص�����
*/

