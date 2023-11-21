// D2DFramework.h - - - - - - - - - - - - - - - - - - - -
#pragma once

#include <d2d1.h>
#include <wrl/client.h>
#include <exception>
#include <stdio.h>

// COM Exception으로 오류 코드 간소화
class com_exception : public std::exception {
private:
	HRESULT result;

public:
	com_exception(HRESULT hr) : result(hr) {}
	virtual const char* what() const override {
		static char str[64]{};
		sprintf_s(str, "Failed with HRESULT : %08X\n", result);
		return str;
	}
};

inline void ThrowIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		throw com_exception(hr);
	}
}

class D2DFramework {
private:
	const LPCWSTR gClassName{ L"MyWindowClass" };

protected:
	HWND mHwnd{};

protected:
	Microsoft::WRL::ComPtr<ID2D1Factory> mspD2DFactory{};
	Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mspRenderTarget{};

protected:
	HRESULT InitWindow(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT w = 1024, UINT h = 768);
	virtual HRESULT InitD2D(HWND hwnd);

	// Device Lost 대비 코드
	virtual HRESULT CreateDeviceResources();

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT w = 1024, UINT h = 768);

	virtual void Release();
	virtual int GameLoop();
	virtual void Render();

	void ShowError(LPCWSTR msg, LPCWSTR title = L"Error");

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

// D2DFramework.cpp - - - - - - - - - - - - - - - - - - -
#include "D2DFramework.h"

#pragma comment (lib, "d2d1.lib")

HRESULT D2DFramework::InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h) {
	HWND hwnd;
	WNDCLASSEX wc{};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = D2DFramework::WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);
	if (!RegisterClassEx(&wc)) {
		return E_FAIL;
	}

	RECT wr = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	hwnd = CreateWindowEx(
		NULL,
		gClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (hwnd == nullptr) {
		return E_FAIL;
	}

	mHwnd = hwnd;

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	// 현재 클래스의 포인터를 윈도우 클래스의 사용자 데이터 영역에 저장
	// 윈도우와 연결된 클래스의 인스턴스를 추후에 윈도우 프로시저나 다른 함수에서 사용 가능
	// 정적 멤버 함수는 클래스에 접근할 수 없기 때문

	return S_OK;
}

HRESULT D2DFramework::InitD2D(HWND hwnd) {
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		mspD2DFactory.GetAddressOf());
	ThrowIfFailed(hr);

	/*RECT wr;
	GetClientRect(hwnd, &wr);
	hr = mspD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
		mspRenderTarget.GetAddressOf());
	ThrowIfFailed(hr);*/

	// return S_OK;

	// Device Lost 대비 코드
	// 장치 의존 리소스들은 모두 모아서 한 번에 관리하고 해제하고
	// 손실되면 복구해야 함
	// 현재는 렌더 타겟만이 장치 의존적
	hr = CreateDeviceResources();
	return hr;
}

HRESULT D2DFramework::CreateDeviceResources() {
	RECT wr;
	GetClientRect(mHwnd, &wr);
	HRESULT hr = mspD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(mHwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
		mspRenderTarget.ReleaseAndGetAddressOf());
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT D2DFramework::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h) {
	ThrowIfFailed(InitWindow(hInstance, title, w, h));
	ThrowIfFailed(InitD2D(mHwnd));

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	return S_OK;
}

void D2DFramework::Release() {
	mspRenderTarget.Reset();
	mspD2DFactory.Reset();
}

int D2DFramework::GameLoop() {
	MSG msg;
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		} else {
			Render();
		}
	}

	return static_cast<int>(msg.wParam);
}

void D2DFramework::Render() {
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
	HRESULT hr = mspRenderTarget->EndDraw();

	// Device Lost 대비 코드
	if (hr == D2DERR_RECREATE_TARGET) {
		CreateDeviceResources();
	}
}

void D2DFramework::ShowError(LPCWSTR msg, LPCWSTR title) {
	MessageBox(nullptr, msg, title, MB_OK);
}

LRESULT D2DFramework::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	D2DFramework* pFramework = reinterpret_cast<D2DFramework*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

// WinMain.cpp - - - - - - - - - - - - - - - - - - - - -
#include <windows.h>
#include "D2DFramework.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) 
{
	try {
		D2DFramework myFramework;
		myFramework.Initialize(hInstance, L"D2DFramework", 1024, 768);
		int ret = myFramework.GameLoop();
		myFramework.Release();
		return ret;
	} catch (const com_exception& e) {
		OutputDebugStringA(e.what());
		MessageBoxA(nullptr, e.what(), "Error", MB_OK);
	}

	return 0;
}