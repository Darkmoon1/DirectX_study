#pragma once
#include <d3d9.h>
class  myDirectX
{
public:
	 myDirectX();
	~ myDirectX();
	/*
	����IDirect3D9�ӿ�ָ�����������ʾ3dͼ�ε�����Ӳ���豸����
	*/
	IDirect3D9* createIDirect3D9Object(int _d3dSdkVersion);
	/*
	�豸���ܼ�飬 ͨ��GetDeviceCaps������������ȡ����Ӳ���豸��Ϣ���浽һ��D3DCAPS9�ṹ��ʵ�ֵġ�
	��Direct3D��HAL֮�仹��һ��HEL������Կ���֧Ӳ����һ�����㣬����Ҫ����HEL�����������ģ��Ӳ���������㡣
	�ڻ�ȡ�豸����ʱ��������Ҫ�ж����Կ��Ƿ�֧�ָ����㡣
	���ض�����������
	*/
	int checkHardware(IDirect3D9* d3d9);
	/*
	��ʼ��d3d�ṹ��ͨ���ṹ�����ָ�����������Ľӿ�IDirect3DDevice9������
	*/
	void D3DSWAPEFFECTInit(D3DPRESENT_PARAMETERS &d3dpp, HWND hwnd);

private:

};

