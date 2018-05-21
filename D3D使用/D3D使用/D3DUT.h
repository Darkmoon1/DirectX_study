#pragma once
#ifndef __D3DUT_H__
#define __D3DUT_H__
#include <d3d9.h>


HWND _hwnd;

IDirect3D9 * createIDirect3D9Object(int _d3dSdkVersion);

int checkHardware(IDirect3D9 * d3d9);

void D3DSWAPEFFECTInit(D3DPRESENT_PARAMETERS & d3dpp
	, HWND hwnd, int width, 
	int height, 
	bool windowed);

bool InitWindow(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed
);

bool InitD3D(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9 ** device
);

LRESULT  D3DWndProc(
	HWND hWnd, 
	UINT message, 
	WPARAM wParam, 
	LPARAM lParam
);


#endif