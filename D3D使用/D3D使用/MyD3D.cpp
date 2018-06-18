#include "MyD3D.h"
#include "D3DUT.h"


MyD3D::MyD3D()
{
}

MyD3D::~MyD3D()
{
}

bool MyD3D::CreateDevice(HINSTANCE  hInstance, int width, int height)
{
	_width = width;
	_height = height;
	if (!InitWindow(hInstance, _width, _height, true))
	{
		MessageBox(0, L"InitD3D()-FAILED", 0, 0);
		return false;
	}
	if (!InitD3D(hInstance,_width,_height,true,D3DDEVTYPE_HAL,&_p_Device))
	{
		MessageBox(0, L"InitD3D()-FAILED", 0, 0);
		return false;
	}
	return true;
}

bool MyD3D::Initialize()
{
	D3DXCreateTeapot(_p_Device, &Teapot, 0);

	//Initialize Virtual Camera.
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	_p_Device->SetTransform(D3DTS_VIEW, &V);

	//Set projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI*0.5f, (float)_width/(float)_height, 1.0f, 1000.0f);
	_p_Device->SetTransform(D3DTS_PROJECTION, &proj);
	//set render state
	_p_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	return true;
}

void MyD3D::FrameMove(float deltaTime)
{
	D3DXMatrixRotationY(& _m_y, _f_rot_y);
	if (GetAsyncKeyState(VK_UP) & 0x8000f)
	{
		
		D3DXMatrixTranslation(&_m_y,)
	}

	//_f_rot_y += deltaTime;
	//if (_f_rot_y >= 6.28f)
	//	_f_rot_y = 0.0f;

}

bool MyD3D::Render()
{
	if (_p_Device)
	{
		_p_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

		_p_Device->BeginScene();
		_p_Device->SetTransform(D3DTS_WORLD, &_m_y);
		Teapot->DrawSubset(0);
		_p_Device->EndScene();

		_p_Device->Present(0, 0, 0, 0);
		return true;
	}
	return false;
}

void MyD3D::Release()
{
	Teapot->Release();
}

IDirect3DDevice9 * MyD3D::getDevice()
{
	return _p_Device;
}
