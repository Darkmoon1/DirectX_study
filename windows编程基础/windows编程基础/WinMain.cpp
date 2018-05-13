#include <Windows.h>
#include <iostream>

using namespace std;
/*
win32程序默认进入函数
hInstance 当前应用程序的实例句柄
hPrevInstance 已经被淘汰的参数，需要写上，设为null
lpCmdLIne 以空终止的字符串，指定传递给应用程序的命令行参数。
nCmdLine 指定应用程序窗口的显示方式，如隐藏，最大化，最小哈等，其值作为ShowWindow函数的参数使用。
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
	while (_msg.message!=WM_QUIT)
	{
		if (PeekMessage(&_msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}
	}
	//循环过程，如同游戏的实时渲染和过程
}


/*
执行过程中的回调函数
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR* text = TEXT("Hello Windows!");//在窗口中要显示的字符串  

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