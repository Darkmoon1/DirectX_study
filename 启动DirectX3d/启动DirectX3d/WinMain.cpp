#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include "DirectX.h"

using namespace std;

/*
win32程序默认进入函数
hInstance 当前应用程序的实例句柄
hPrevInstance 已经被淘汰的参数，需要写上，设为null
lpCmdLIne 以空终止的字符串，指定传递给应用程序的命令行参数。
nCmdLine 指定应用程序窗口的显示方式，如隐藏，最大化，最小哈等，其值作为ShowWindow函数的参数使用。
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

IDirect3DDevice9* Device = 0;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	/*
	初始化窗体参数并注册win窗体
	*/
	WNDCLASS _wc;
	_wc.style = CS_HREDRAW | CS_VREDRAW;		//窗口类的样式，0代表默认
	_wc.lpfnWndProc = (WNDPROC)WndProc;		//指定窗口处理函数
	_wc.cbClsExtra = 0;		//窗口类扩展
	_wc.cbWndExtra = 0;		//窗口的扩展
	_wc.hInstance = hInstance;		//指定窗口的句柄
	_wc.hIcon = LoadIcon(0, IDI_WINLOGO);		//图标句柄
	_wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//加载光标的举兵
	_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//制定画刷颜色
	_wc.lpszMenuName = NULL;		//设置菜单名字
	_wc.lpszClassName = TEXT("MyWndClass");		//设置窗口类的名字

	RegisterClass(&_wc);

	/*
	实例化窗口
	*/
	HWND _hwnd = CreateWindow(TEXT("MyWndClass"),	//指向已注册的窗口类名
		TEXT("标题"),								//创建的窗口名称  
		WS_OVERLAPPEDWINDOW,						//窗口样式
		CW_USEDEFAULT,								//水平位置
		CW_USEDEFAULT,								//垂直位置
		640,										//窗口宽度
		480,										//窗口高度
		NULL,										//父窗口句柄
		NULL,										//菜单
		hInstance,									//句柄
		NULL);										//用于检测窗口是否创建成功，如果成功则返回窗口句柄，若失败返回null，通常设置为null
	
	if (_hwnd == 0)
	{
		cout << "窗口创建失败" << endl;
		return 1;
	}
	/*
	显示并更新窗口
	*/
	ShowWindow(_hwnd, nCmdShow);
	UpdateWindow(_hwnd);

	//--------------初始化DirectX-----------

	myDirectX _myDirect;
	IDirect3D9 *_d3d9 = _myDirect.createIDirect3D9Object(D3D_SDK_VERSION);
	if (!_d3d9)
	{
		MessageBox(0, L"DirectX create failed", 0, 0);
		return 1;
	}

	int vp = _myDirect.checkHardware(_d3d9);
	D3DPRESENT_PARAMETERS _d3dpp;
	_myDirect.D3DSWAPEFFECTInit(_d3dpp, _hwnd);
	_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, vp, &_d3dpp, &Device);













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
			if (Device)
			{
				Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

				Device->Present(0, 0, 0, 0);
			}

			float _currTime = (float)timeGetTime();
			float _deltaTime = (_currTime - _lastTime)*0.001f;

			/*
			_device.FrameMove(_deltaTime);
			_device.Render();

			*/
			_lastTime = _currTime;
		}
	}
	//循环过程，如同游戏的实时渲染和过程

	Device->Release();
	return 0;
}


/*
执行过程中的回调函数
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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