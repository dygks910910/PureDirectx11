#pragma once

#include<Windows.h>

__interface IGameInterface
{
	virtual void OnMouseDown(const WPARAM& wParam, const int& x, const int& y)  =0 ;
	virtual void OnKeyboardButtonDown(const HWND& hwnd, const UINT& msg,
		const WPARAM& wParam, const LPARAM& lParam) = 0;
};

class MainSceneInterface : public IGameInterface
{
	void OnMouseDown(const WPARAM& wParam, const int& x, const int& y) override;
	void OnKeyboardButtonDown(const HWND& hwnd, const UINT& msg,
		const WPARAM& wParam, const LPARAM& lParam)override;
};