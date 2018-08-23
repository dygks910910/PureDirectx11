//***************************************************************************************
// d3dApp.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Simple Direct3D demo application class.  
// Make sure you link: d3d11.lib d3dx11d.lib D3DCompiler.lib D3DX11EffectsD.lib 
//                     dxerr.lib dxgi.lib dxguid.lib.
// Link d3dx11.lib and D3DX11Effects.lib for release mode builds instead
//   of d3dx11d.lib and D3DX11EffectsD.lib.
//***************************************************************************************

#ifndef D3DAPP_H
#define D3DAPP_H
#define FULL_SCREEN false

#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>
#include<iostream>
#include"..\InterfaceInput.h"

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;
	int Run()
	{
		MSG msg = { 0 };
		float temp = 0;
		mTimer.Reset();
		while (msg.message != WM_QUIT)
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// Otherwise, do animation/game stuff.
			else
 			{
				mTimer.Tick();

				temp += mTimer.DeltaTime();
				if(temp >= 1.0f/60.0f)
  				{
					CalculateFrameStats();
					//Listener

					//Update
					UpdateScene(temp, msg);
					//Draw
					DrawScene();
					temp = 0;
  				}
				else
				{
					Sleep(1.0f / 60.f - temp);
				}
	
			}
		}

		return (int)msg.wParam;
	}

	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	bool Init();
	void OnResize();
	void UpdateScene(const float& dt,const MSG& msg) {};
	void DrawScene() {

	};
	virtual void OnKeyboardButtonDown(const HWND& hwnd, const UINT& msg,
		const WPARAM& wParam,const LPARAM& lParam) {};

	virtual void OnMouseDown(const WPARAM& wParam, const int& x, const int& y) {};

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse input.

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameStats();

protected:

	HINSTANCE mhAppInst;
	HWND      mhMainWnd;
	bool      mAppPaused;
	bool      mMinimized;
	bool      mMaximized;
	bool      mResizing;
	UINT      m4xMsaaQuality;

	GameTimer mTimer;
// 	GameTimer mTimerForFPS;
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mScreenViewport;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	D3D_DRIVER_TYPE md3dDriverType;
	int mClientWidth;
	int mClientHeight;
	bool mEnable4xMsaa;
};
#endif // D3DAPP_H