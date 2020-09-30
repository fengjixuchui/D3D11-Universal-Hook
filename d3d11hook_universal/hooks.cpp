#include "framework.h"

Present hooks::oPresent;
WNDPROC hooks::oWndProc;
EndScene hooks::oEndScene;

HWND hwnd = NULL;
WNDPROC wndProc;
ID3D11DeviceContext* pContext;
ID3D11RenderTargetView* mainRenderTargetView;
ID3D11Device* pDevice;
bool initialize = false;

LRESULT __stdcall hooks::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true)
		return true;

	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);
}

long __stdcall hooks::hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	/* render your shit here */

	return oEndScene(pDevice);
}

HRESULT __stdcall hooks::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!initialize)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			hwnd = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			wndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
			initialize = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	return oPresent(pSwapChain, SyncInterval, Flags);
}