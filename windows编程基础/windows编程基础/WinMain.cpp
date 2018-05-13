#include <Windows.h>
#include <iostream>

using namespace std;
/*
win32����Ĭ�Ͻ��뺯��
hInstance ��ǰӦ�ó����ʵ�����
hPrevInstance �Ѿ�����̭�Ĳ�������Ҫд�ϣ���Ϊnull
lpCmdLIne �Կ���ֹ���ַ�����ָ�����ݸ�Ӧ�ó���������в�����
nCmdLine ָ��Ӧ�ó��򴰿ڵ���ʾ��ʽ�������أ���󻯣���С���ȣ���ֵ��ΪShowWindow�����Ĳ���ʹ�á�
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
	while (_msg.message!=WM_QUIT)
	{
		if (PeekMessage(&_msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}
	}
	//ѭ�����̣���ͬ��Ϸ��ʵʱ��Ⱦ�͹���
}


/*
ִ�й����еĻص�����
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR* text = TEXT("Hello Windows!");//�ڴ�����Ҫ��ʾ���ַ���  

	switch (message)
	{
	case WM_PAINT:
	{
		//get the dimensions of the window  
		RECT rt;
		GetClientRect(hWnd, &rt);

		//start drawing on device context  
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//draw some text  
		DrawText(hdc,text, -1, &rt, DT_CENTER);

		//draw 1000 random pixels  
		for (int n = 0; n<3000; n++)
		{
			int x = rand() % (rt.right - rt.left);
			int y = rand() % (rt.bottom - rt.top);
			COLORREF c = RGB(rand() % 256, rand() % 256, rand() % 256);
			SetPixel(hdc, x, y, c);
		}

		//stop drawing  
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}