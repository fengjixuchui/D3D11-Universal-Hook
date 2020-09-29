#pragma once
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);


namespace hooks
{
	/* original */
	extern Present oPresent;
	extern WNDPROC oWndProc;
	extern EndScene oEndScene;

	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
}