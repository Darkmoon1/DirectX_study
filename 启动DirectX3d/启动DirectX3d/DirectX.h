#pragma once
#include <d3d9.h>
class  myDirectX
{
public:
	 myDirectX();
	~ myDirectX();
	/*
	创建IDirect3D9接口指针对象，用来显示3d图形的物理硬件设备对象
	*/
	IDirect3D9* createIDirect3D9Object(int _d3dSdkVersion);
	/*
	设备性能检查， 通过GetDeviceCaps（）函数将获取到的硬件设备信息保存到一个D3DCAPS9结构中实现的。
	在Direct3D和HAL之间还有一层HEL，如果显卡不支硬件顶一点运算，就需要利用HEL的软件运算来模拟硬件定点运算。
	在获取设备性能时，我们需要判断主显卡是否支持该运算。
	返回定点运算类型
	*/
	int checkHardware(IDirect3D9* d3d9);
	/*
	初始化d3d结构体通过结构体变量指定即将创建的接口IDirect3DDevice9的特性
	*/
	void D3DSWAPEFFECTInit(D3DPRESENT_PARAMETERS &d3dpp, HWND hwnd);

private:

};

