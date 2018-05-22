#pragma once

#include "MyD3D.h"
#include <Windows.h>



/*
win32程序默认进入函数
hInstance 当前应用程序的实例句柄
hPrevInstance 已经被淘汰的参数，需要写上，设为null
lpCmdLIne 以空终止的字符串，指定传递给应用程序的命令行参数。
nCmdLine 指定应用程序窗口的显示方式，如隐藏，最大化，最小哈等，其值作为ShowWindow函数的参数使用。
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
	消息循环
	WINUSERAPI BOOL WINAPI GetMessage(
	_out LPMSG lpMSG,				指向消息结构体的指针，该结构体保存了取自消息队列的消息
	_in_opt HWND hWnd,				指定消息所属的窗口，NULL表示接受属于当前线程所有的窗口的消息
	_in UINT wMsgFilterMin,			指定指定要接受的消息的最小值，一般设为0
	_in UINT wMsgFilterMax			指定要接受的消息的最大值，如果MIN和MAX均为0 表示接受所有的消息

	PeekMessage()前四个参数入GetMessage相同，后两个依次为消息处理之后不在消息队列中删除，处理后删除
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
	//循环过程，如同游戏的实时渲染和过程

	_device.Release();
	return 0;
}


/*
执行过程中的回调函数
*/

