#pragma once
#ifndef __D3DUT_H__
#define __D3DUT_H__
#include <d3d9.h>
#endif

#include <d3dx9math.h>  

class MyD3D
{
public:
	MyD3D();
	~MyD3D();
	bool CreateDevice(HINSTANCE hInstance, int width, int height);
	bool Initialize();
	void FrameMove(float deltaTime);
	bool Render();
	void Release();
	IDirect3DDevice9 *getDevice();

private:
	IDirect3DDevice9 *_p_Device;
	D3DXMATRIX _m_y;
	float _f_rot_y;
	//Teapot Mesh:provided by D3D sdk
	ID3DXMesh *Teapot;
	int _width;
	int _height;

};

