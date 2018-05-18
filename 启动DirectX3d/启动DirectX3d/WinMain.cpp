#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include "DirectX.h"

using namespace std;

/*
win32����Ĭ�Ͻ��뺯��
hInstance ��ǰӦ�ó����ʵ�����
hPrevInstance �Ѿ�����̭�Ĳ�������Ҫд�ϣ���Ϊnull
lpCmdLIne �Կ���ֹ���ַ�����ָ�����ݸ�Ӧ�ó���������в�����
nCmdLine ָ��Ӧ�ó��򴰿ڵ���ʾ��ʽ�������أ���󻯣���С���ȣ���ֵ��ΪShowWindow�����Ĳ���ʹ�á�
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

IDirect3DDevice9* Device = 0;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	/*
	��ʼ�����������ע��win����
	*/
	WNDCLASS _wc;
	_wc.style = CS_HREDRAW | CS_VREDRAW;		//���������ʽ��0����Ĭ��
	_wc.lpfnWndProc = (WNDPROC)WndProc;		//ָ�����ڴ�����
	_wc.cbClsExtra = 0;		//��������չ
	_wc.cbWndExtra = 0;		//���ڵ���չ
	_wc.hInstance = hInstance;		//ָ�����ڵľ��
	_wc.hIcon = LoadIcon(0, IDI_WINLOGO);		//ͼ����
	_wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���ع��ľٱ�
	_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//�ƶ���ˢ��ɫ
	_wc.lpszMenuName = NULL;		//���ò˵�����
	_wc.lpszClassName = TEXT("MyWndClass");		//���ô����������

	RegisterClass(&_wc);

	/*
	ʵ��������
	*/
	HWND _hwnd = CreateWindow(TEXT("MyWndClass"),	//ָ����ע��Ĵ�������
		TEXT("����"),								//�����Ĵ�������  
		WS_OVERLAPPEDWINDOW,						//������ʽ
		CW_USEDEFAULT,								//ˮƽλ��
		CW_USEDEFAULT,								//��ֱλ��
		640,										//���ڿ��
		480,										//���ڸ߶�
		NULL,										//�����ھ��
		NULL,										//�˵�
		hInstance,									//���
		NULL);										//���ڼ�ⴰ���Ƿ񴴽��ɹ�������ɹ��򷵻ش��ھ������ʧ�ܷ���null��ͨ������Ϊnull
	
	if (_hwnd == 0)
	{
		cout << "���ڴ���ʧ��" << endl;
		return 1;
	}
	/*
	��ʾ�����´���
	*/
	ShowWindow(_hwnd, nCmdShow);
	UpdateWindow(_hwnd);

	//--------------��ʼ��DirectX-----------

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
	//ѭ�����̣���ͬ��Ϸ��ʵʱ��Ⱦ�͹���

	Device->Release();
	return 0;
}


/*
ִ�й����еĻص�����
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

	//����ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д�����κδ�����Ϣ�ṩȱʡ�Ĵ���  
	//�ú���ȷ��ÿһ����Ϣ�õ�����  
	return DefWindowProc(hWnd, message, wParam, lParam);
}