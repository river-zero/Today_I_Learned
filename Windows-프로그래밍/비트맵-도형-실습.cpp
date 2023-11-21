// BitmapExample.h - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH     = 1024;
const int BITMAP_HEIGHT    = 768;
const int BITMAP_BYTECOUNT = 4; // rgba로 구성

class BitmapExample : public D2DFramework {
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBitmap{};
	std::unique_ptr<UINT8[]> mspBackBuffer;
	// 백 버퍼를 위한 배열
	// 한 픽셀은 rgba 4바이트가 한 묶음
	// 따라서 배열의 크기는 가로 * 세로 * 바이트수
	// UINT8은 unsigned char 타입

protected:
	virtual HRESULT CreateDeviceResources() override;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"BitmapExample", UINT width = 1024, UINT height = 768) override;
	virtual void Render() override;

	void DrawCircle(int x, int y, int r, D2D1::ColorF color);
	void DrawLine(int x1, int y1, int x2, int y2, D2D1::ColorF color);
	void DrawRect(int x, int y, int width, int height, D2D1::ColorF color);
	void DrawPixel(int x, int y, D2D1::ColorF color);
	void ClearBuffer(D2D1::ColorF color);
	// 백 버퍼를 단일한 색상으로 지움
	void PresentBuffer(); 
	// 백 버퍼를 프레임 버퍼로 이동
};

// D2DFramework.h - - - - - - - - - - - - - - - - - - - - - - - -
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

// BitmapExample.cpp - - - - - - - - - - - - - - - - - - - - - -
#include "BitmapExample.h"

HRESULT BitmapExample::CreateDeviceResources() {
	D2DFramework::CreateDeviceResources();

	HRESULT hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(BITMAP_WIDTH, BITMAP_HEIGHT),
		D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
		mspFrameBitmap.ReleaseAndGetAddressOf()
	);
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT BitmapExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h) {
	D2DFramework::Initialize(hInstance, title, w, h);

	mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH * BITMAP_HEIGHT * BITMAP_BYTECOUNT);

	return S_OK;
}

void BitmapExample::Render() {
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	ClearBuffer(D2D1::ColorF(D2D1::ColorF(D2D1::ColorF::DarkOliveGreen)));

	DrawPixel(1, 1, D2D1::ColorF::Black);
	DrawRect(0, 0, 100, 100, D2D1::ColorF::White);
	DrawRect(50, 50, 100, 100, D2D1::ColorF(D2D1::ColorF::Black, 0.8f));

	DrawLine(0, 0, BITMAP_WIDTH - 1, BITMAP_HEIGHT - 1, D2D1::ColorF::Black);
	DrawLine(200, 10, 50, 400, D2D1::ColorF::Black);
	DrawLine(20, 30, 150, 30, D2D1::ColorF::Red);
	DrawLine(150, 50, 20, 50, D2D1::ColorF::Red);
	DrawLine(100, 50, 100, 200, D2D1::ColorF::Black);
	DrawLine(110, 200, 110, 50, D2D1::ColorF::Black);
	DrawCircle(200, 100, 50, D2D1::ColorF::Blue);

	PresentBuffer();
	mspRenderTarget->DrawBitmap(mspFrameBitmap.Get());

	HRESULT hr = mspRenderTarget->EndDraw();

	// 렌더 타겟이 다시 만들어져야 할 경우
	if (hr == D2DERR_RECREATE_TARGET) {
		CreateDeviceResources();
	}
}

void BitmapExample::DrawCircle(int x, int y, int r, D2D1::ColorF color) {
	const float PI = 3.14159265358979323846;
	for (float theta = 0; theta < 2 * PI; theta += 0.01) {
		for (int radius = 0; radius < r; radius++) {
			int circleX = static_cast<int>(x + radius * cos(theta));
			int circleY = static_cast<int>(y + radius * sin(theta));
			DrawPixel(circleX, circleY, color);
		}
	}
}

/*void BitmapExample::DrawLine(int x1, int y1, int x2, int y2, D2D1::ColorF color) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	// 수직선인 경우
	if (dx == 0) {
		for (int y = min(y1, y2); y <= max(y1, y2); y++) {
			DrawPixel(x1, y, color);
		}
		return;
	}

	float m = static_cast<float>(dy) / dx;
	float b = static_cast<float>(y1) - m * x1;

	for (int x = min(x1, x2); x <= max(x1, x2); x++) {
		int y = static_cast<int>(m * x + b);
		DrawPixel(x, y, color);
	}
}*/

void BitmapExample::DrawLine(int x1, int y1, int x2, int y2, D2D1::ColorF color) {
	// Breseham's 알고리즘 사용
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	// 증가 방향 설정
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;

	int err = dx - dy;

	while (x1 != x2 || y1 != y2) {
		DrawPixel(x1, y1, color);
		int e2 = 2 * err;

		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

void BitmapExample::DrawRect(int x, int y, int width, int height, D2D1::ColorF color) {
	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {
			DrawPixel(i, j, color);
		}
	}
}

void BitmapExample::DrawPixel(int x, int y, D2D1::ColorF color) {
	if (x >= 0 && x < BITMAP_WIDTH && y >= 0 && y < BITMAP_HEIGHT) {
		UINT8* p = &mspBackBuffer[(y * BITMAP_WIDTH + x) * BITMAP_BYTECOUNT];
		// 이차원 배열을 일차원 배열로 변환하고
		// 인덱스를 픽셀 크기에 맞게 조정
		// pitch = width * byteCount로 index = x * byteCount +  y * pitch도 가능

		// 투명도 alpha 적용
		// 결과 = 기존 색상 * (1.0ㄹ - alpha) + 신규 색상 * alpha
		float inverse = 1.0f - color.a;
		*p++ = static_cast<UINT8>(p[0] * inverse + color.r * 255 * color.a);
		*p++ = static_cast<UINT8>(p[1] * inverse + color.g * 255 * color.a);
		*p++ = static_cast<UINT8>(p[2] * inverse + color.b * 255 * color.a);
		*p++ = static_cast<UINT8>(p[3] * inverse + color.a * 255 * color.a);
	}
}

void BitmapExample::ClearBuffer(D2D1::ColorF color) {
	// D2D1::ColorF는 0.0f에서 1.0f이지만
	// 백 버퍼는 UINT8 unsigned char형으로 0에서 255로 변환이 필요
	UINT8* p = &mspBackBuffer[0];
	for (int i = 0; i < BITMAP_WIDTH * BITMAP_HEIGHT; i++) {
		*p++ = static_cast<UINT8>(color.r * 255);
		*p++ = static_cast<UINT8>(color.g * 255);
		*p++ = static_cast<UINT8>(color.b * 255);
		*p++ = static_cast<UINT8>(color.a * 255); // 현재 무시됨
	}
}

void BitmapExample::PresentBuffer() {
	// 직접 하드웨어 가속을 구현하기는 어려우니
	// 간략하게 백 버퍼의 내용을 프레임 버퍼로 복사하는 방식으로 구현
	mspFrameBitmap->CopyFromMemory(nullptr, &mspBackBuffer[0], BITMAP_WIDTH * BITMAP_BYTECOUNT);
}

// D2DFramework.cpp - - - - - - - - - - - - - - - - - - - - - - -
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

// WinMain.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include <windows.h>
#include "BitmapExample.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) 
{
	try {
		BitmapExample myFramework;
		myFramework.Initialize(hInstance, L"BitmapExample", 1024, 768);
		int ret = myFramework.GameLoop();
		myFramework.Release();
		return ret;
	} catch (const com_exception& e) {
		OutputDebugStringA(e.what());
		MessageBoxA(nullptr, e.what(), "Error", MB_OK);
	}

	return 0;
}