// ImageExample.h - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include "D2DFramework.h"
#include <wincodec.h>

class ImageExample : public D2DFramework {
private:
	Microsoft::WRL::ComPtr<IWICImagingFactory> mspWICFactory;
	// WIC 역시 팩토리 패턴이라 팩토리를 위한 스마트 포인터 선언
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspBitmap;

private:
	HRESULT LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
	// 일반 변수를 매개변수로 받아 값을 수정하려면 변수의 주소값(포인터)이 필요한 것처럼
	// 포인터 변수를 매개변수로 받아 값을 수정하려면 포인터 변수의 주소값(포인터의 포인터) 필요
	HRESULT LoadWIC(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
	// 이 방식은 여러 포멧을 해석 가능

protected:
	virtual HRESULT CreateDeviceResources() override;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"ImageExample", UINT w = 1024, UINT h = 768) override;
	void Render() override;
	void Release() override;
	// 개별적인 해제가 필요하므로 Release 오버라이딩
};

// ImageExample.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include "ImageExample.h"
#include <fstream>
#include <vector>

#pragma comment (lib, "WindowsCodecs.lib")

HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap) {
	// 1. 파일 열기
	std::ifstream file;
	file.open(filename, std::ios::binary);
	// ifstream을 사용해 binary 모드로 오픈

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	// 2. BITMAPFILEHEADER 읽기
	file.read(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
	// ifstream.read()는 char*를 매개변수로
	// 따라서 BITMAPFILEHEADER 구조체를 형변환
	
	// 3. BITMAPINFOHEADER 읽기
	file.read(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));
	if (bfh.bfType != 0x4D42) { // 리틀 엔디안임에 주의
		return E_FAIL;
	}
	// 비트맵 파일의 헤더를 검사하여 파일이 실제로 비트맵 파일인지 확인
	// bfh.bfType은 비트맵 파일의 매직 넘버로 비트맵 파일의 경우 이 값은 항상 0x4D42
	if (bih.biBitCount != 32) { // 압축이라면 못 읽음
		return E_FAIL;
	}
	// 비트맵 이미지가 32비트 색상을 사용하는지 확인

	std::vector<char> pixels(bih.biSizeImage);
	// 비트맵을 저장할 공간

	// 4. 픽셀로 건너뛰기
	file.seekg(bfh.bfOffBits); 
	// 이미지 데이터 있는 곳까지 스킵
	// ifstream.seek()을 사용하면 바이트 단위로 이동 가능
	// 헤더의 bfOffBits에 실제 픽셀에 대한 위치가 저장되어 있음

	// 5. 비트맵 읽기
	// file.read(&pixels[0], bih.biSizeImage);
	// 첫번째 원소의 주소를 얻어오면 char*형이 됨
	// 이렇게 하면 이미지가 거꾸로 출력됨
	// 기본적으로 BMP 파일은 bottom-up 방식
	// 가끔 헤더에 biHeight가 음수인 경우가 top-down 방식

	// pitch 단위로 읽어서 역순으로 저장하면 이미지 제대로 출력
	int pitch = bih.biWidth * (bih.biBitCount / 8);
	// biBitCount는 비트를 바이트로 변환하기 위해 8로 나눔
	for (int y = bih.biHeight - 1; y >= 0; y--) {
		file.read(&pixels[y * pitch], pitch);

		// 이미지 누끼 따기
		for (int x = 0; x < bih.biWidth; x++) {
			int index = (y * pitch) + (x * bih.biBitCount / 8);

			unsigned char b = pixels[index];
			unsigned char g = pixels[index + 1];
			unsigned char r = pixels[index + 2];
			unsigned char a = pixels[index + 3];

			if (r == 30 && g == 199 && b == 250) { // 배경색이 이렇다면 투명도 조절
				pixels[index] = 0;
				pixels[index + 1] = 0;
				pixels[index + 2] = 0;
				pixels[index + 3] = 0;
			}
		}
	}

	file.close();

	// 6. 비트맵 생성
	HRESULT hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(bih.biWidth, bih.biHeight),
		D2D1::BitmapProperties(
			D2D1::PixelFormat(
				DXGI_FORMAT_B8G8R8A8_UNORM,      // 엔디안 문제로 ARGB -> BGRA
				D2D1_ALPHA_MODE_PREMULTIPLIED)), // 투명도 설정
		ppBitmap
	);
	ThrowIfFailed(hr);

	(*ppBitmap)->CopyFromMemory(nullptr, &pixels[0], pitch);

	return S_OK;
}

HRESULT ImageExample::LoadWIC(LPCWSTR filename, ID2D1Bitmap** ppBitmap) {
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	HRESULT hr;

	// 1. 디코더 생성
	hr = mspWICFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		decoder.GetAddressOf()
	);
	ThrowIfFailed(hr);

	// 2. 프레임 획득
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	hr = decoder->GetFrame(0, frame.GetAddressOf());
	// 이미지의 특성에 따라 프레임은 여러 장일 수 있지만
	// 여기서는 단순한 이미지를 불러오므로 0번 프레임만 가져옴
	ThrowIfFailed(hr);

	// 3. 컨버터를 사용해 데이터를 변환
	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	hr = mspWICFactory->CreateFormatConverter(converter.GetAddressOf());
	ThrowIfFailed(hr);

	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0,
		WICBitmapPaletteTypeCustom
	);
	ThrowIfFailed(hr);

	// 4. 변환된 데이터에서 비트맵 생성
	hr = mspRenderTarget->CreateBitmapFromWicBitmap(
		converter.Get(),
		ppBitmap
	);
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT ImageExample::CreateDeviceResources() {
	D2DFramework::CreateDeviceResources();

	HRESULT hr = LoadBMP(L"Data/32.bmp", mspBitmap.ReleaseAndGetAddressOf());
	ThrowIfFailed(hr);
	/*HRESULT hr = LoadWIC(L"Data/32.bmp", mspBitmap.ReleaseAndGetAddressOf());
	ThrowIfFailed(hr);*/

	return S_OK;
}

HRESULT ImageExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h) {
	HRESULT hr = CoInitialize(nullptr); 
	ThrowIfFailed(hr);

	// COM 객체의 인스턴스를 만들어내고
	// 해당 객체의 인터페이스에 대한 포인터를 반환함으로써 
	// 다른 코드에서 이 객체와 상호 작용할 수 있도록 함
	hr = ::CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(mspWICFactory.GetAddressOf())
	);
	ThrowIfFailed(hr);

	D2DFramework::Initialize(hInstance, title, w, h);

	return S_OK;
}

void ImageExample::Render() {
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mspRenderTarget->DrawBitmap(mspBitmap.Get());

	HRESULT hr = mspRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET) {
		CreateDeviceResources();
	}
}

void ImageExample::Release() {
	D2DFramework::Release();

	mspBitmap.Reset();
	mspWICFactory.Reset();

	CoUninitialize(); // CoInitialize 함수와 한 쌍
}

// D2DFramework.h - - - - - - - - - - - - - - - - - - - - - - - - - -
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

// D2DFramework.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
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

// WinMain.cpp- - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <windows.h>
#include "ImageExample.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) 
{
	try {
		ImageExample myFramework;
		myFramework.Initialize(hInstance, L"ImageExample", 1024, 768);
		int ret = myFramework.GameLoop();
		myFramework.Release();
		return ret;
	} catch (const com_exception& e) {
		OutputDebugStringA(e.what());
		MessageBoxA(nullptr, e.what(), "Error", MB_OK);
	}

	return 0;
}