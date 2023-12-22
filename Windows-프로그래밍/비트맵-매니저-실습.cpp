// Actor.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include "D2DFramework.h"

class Actor {
protected:
	D2DFramework* mpFramework;
	ID2D1Bitmap* mpBitmap;

	float mX;
	float mY;
	float mOpacity;

public:
	Actor() = delete;
	Actor(D2DFramework* pFramework, LPCWSTR filename);
	Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity = 1.0f);

	virtual ~Actor();

private:
	void Draw(float x, float y, float opacity = 1.0f);

public:
	virtual void Draw();
};

// Actor.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include "Actor.h"

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename) :
	mpFramework(pFramework),
	mpBitmap(),
	mX(),
	mY(),
	mOpacity(1.0f) {
	mpBitmap = BitmapManager::Instance().LoadBitmap(filename);
}

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity) :
	Actor(pFramework, filename) {
	mX = x;
	mY = y;
	mOpacity = opacity;
}

Actor::~Actor() {
}

void Actor::Draw(float x, float y, float opacity) {
	auto pRT = mpFramework->GetRenderTarget();
	if (pRT == nullptr) {
		return;
	}

	auto size{ mpBitmap->GetPixelSize() };
	D2D1_RECT_F rect{ x, y,
		static_cast<float>(x + size.width),
		static_cast<float>(y + size.height) };

	pRT->DrawBitmap(mpBitmap, rect, opacity);
}

void Actor::Draw() {
	Draw(mX, mY, mOpacity);
}

// ActorExample.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include "D2DFramework.h"
#include "Actor.h"
#include <memory>

class ActorExample : public D2DFramework {
private:
    std::unique_ptr<Actor> mspBackground;
    std::unique_ptr<Actor> mspBug;

public:
    virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"ActorExample", UINT width = 1024, UINT height = 768) override;
    virtual void Release() override;
    virtual void Render() override;
};

// ActorExample.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include "ActorExample.h"

HRESULT ActorExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height) {
	HRESULT hr;

	hr = D2DFramework::Initialize(hInstance, title, width, height);
	ThrowIfFailed(hr);

	mspBackground = std::make_unique<Actor>(this, L"Images/Back.png", 0, 0, 1.0f);
	mspBug = std::make_unique<Actor>(this, L"Images/Bug.png", 100, 100);

	return S_OK;
}

void ActorExample::Release() {
	mspBug.reset();
	mspBackground.reset();

	D2DFramework::Release();
}

void ActorExample::Render() {
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mspBackground->Draw();
	mspBug->Draw();

	HRESULT hr = mspRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET) {
		CreateDeviceResources();
	}
}

// BitmapManager.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

// 실제 게임은 수백에서 수천의 이미지를 사용하기 때문에
// 어떤 그림 파일이 중복으로 로딩되는지 확인하기 어려움
// 따라서 이런 과정을 관리해주는 관리자를 두면 편함
// 관리자의 위치는 D2DFramework 내부가 적절

#include "com_exception.h"
#include <wrl/client.h>
#include <d2d1.h>
#include <wincodec.h>
#include <map>
#include <string>

// 싱글턴 패턴 적용
class BitmapManager final {
public:
	static BitmapManager& Instance() {
		static BitmapManager instance;
		return instance;
	}

private:
	BitmapManager() {}
	BitmapManager(const BitmapManager&) {}
	void operator=(const BitmapManager&) {}

public:
	~BitmapManager() {}

private:
	ID2D1HwndRenderTarget* mpRenderTarget{};
	Microsoft::WRL::ComPtr<IWICImagingFactory> mspWICFactory{};

	std::map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap>> mBitmapResources;
	// 이미지를 관리하기 위해서 <파일명, 비트맵> 형태의 쌍이 필요

private:
	HRESULT LoadWICBitmap(std::wstring filename, ID2D1Bitmap** ppBitmap);

public:
	// 싱글턴 패턴에서는 생성자와 소멸자에 의지하기 어려우니 
	// 명시적인 초기화 및 해제 함수가 있으면 좋음
	HRESULT Initialize(ID2D1HwndRenderTarget* pRT);
	void Release();

	ID2D1Bitmap* LoadBitmap(std::wstring filename);
	// 관리자의 핵심 함수
	// 맵에 데이터의 존재를 확인하고 관리하는 기능
};

// BitmapManager.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include "BitmapManager.h"

#pragma comment (lib, "WindowsCodecs.lib")

using namespace std;
using namespace Microsoft::WRL;

HRESULT BitmapManager::LoadWICBitmap(std::wstring filename, ID2D1Bitmap** ppBitmap) {
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	HRESULT hr;

	auto pWICFactory = mspWICFactory.Get();
	if (pWICFactory == nullptr) {
		return E_FAIL;
	}

	hr = pWICFactory->CreateDecoderFromFilename(
		filename.c_str(), 
		nullptr, 
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad, 
		decoder.GetAddressOf());
	ThrowIfFailed(hr);

	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	ThrowIfFailed(pWICFactory->CreateFormatConverter(converter.GetAddressOf()));

	hr = converter->Initialize(
		frame.Get(), 
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, 
		nullptr,
		0, 
		WICBitmapPaletteTypeCustom);
	ThrowIfFailed(hr);

	auto pRT = mpRenderTarget;
	if (pRT == nullptr) {
		return E_FAIL;
	}
	hr = pRT->CreateBitmapFromWicBitmap(converter.Get(), ppBitmap);
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT BitmapManager::Initialize(ID2D1HwndRenderTarget* pRT) {
	if (!pRT) {
		return E_FAIL;
	}

	mpRenderTarget = pRT;

	HRESULT hr = ::CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(mspWICFactory.GetAddressOf()));
	ThrowIfFailed(hr, "WICFactory Creation Failed");

	return S_OK;
}

void BitmapManager::Release() {
	mBitmapResources.clear();
	mspWICFactory.Reset();
}

ID2D1Bitmap* BitmapManager::LoadBitmap(std::wstring filename) {
	if (!mspWICFactory) {
		ThrowIfFailed(E_FAIL, "WICFactory must not null");
		return nullptr;
	}

	// 이미지 파일 로드 여부를 확인하고 로드되지 않았다면 맵에 추가
	// 이미지 파일에 대한 비트맵이 맵에 이미 있다면 해당 비트맵을 반환
	auto result = mBitmapResources.insert({ filename, nullptr });
	if (result.second == true) { // 키가 새로 추가되었다면 실행해 불필요한 탐색을 줄임
		auto spBitmap = ComPtr<ID2D1Bitmap>();
		LoadWICBitmap(filename, spBitmap.GetAddressOf());
		result.first->second = spBitmap;
	}

	return result.first->second.Get();
}

// com_exception.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include <exception>
#include <string>
#include <winerror.h>
#include <stdio.h>

class com_exception : public std::exception {
private:
	HRESULT result;
	std::string description;

public:
	com_exception(HRESULT hr) : com_exception(hr, "") {}
	// com_exception(HRESULT hr) : result(hr), description() {}
	com_exception(HRESULT hr, std::string msg) : result(hr), description(msg) {}
	virtual const char* what() const override {
		static char str[512]{};
		sprintf_s(str, "Failed with HRESULT : %08X\n%s\n", result, description.c_str());
		return str;
	}
};

inline void ThrowIfFailed(HRESULT hr, std::string msg = "") {
	if (FAILED(hr)) {
		throw com_exception(hr, msg);
	}
}

// D2DFramework.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include <d2d1.h>
#include <wrl/client.h>
#include "com_exception.h"
#include "BitmapManager.h"

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
	virtual HRESULT CreateDeviceResources();

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT w = 1024, UINT h = 768);

	virtual void Release();
	virtual int GameLoop();
	virtual void Render();

	void ShowError(LPCWSTR msg, LPCWSTR title = L"Error");

	static LRESULT CALLBACK WindowProc(
		HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam
	);

public:
	inline ID2D1HwndRenderTarget* GetRenderTarget() {
		return mspRenderTarget.Get();
	}
	inline ID2D1Factory* GetD2DFactory() {
		return mspD2DFactory.Get();
	}
};

// D2DFramework.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include "D2DFramework.h"

#pragma comment (lib, "d2d1.lib")

HRESULT D2DFramework::InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h) {
    HWND hwnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = gClassName;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = D2DFramework::WindowProc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    if (!RegisterClassEx(&wc)) {
        return E_FAIL;
    }

    RECT wr = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    hwnd = CreateWindowEx(NULL,
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

    return S_OK;
}

HRESULT D2DFramework::InitD2D(HWND hwnd) {
    HRESULT hr;

    hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        mspD2DFactory.GetAddressOf());
    ThrowIfFailed(hr);

    hr = CreateDeviceResources();

    return hr;
}

HRESULT D2DFramework::CreateDeviceResources() {
    RECT wr;
    GetClientRect(mHwnd, &wr);
    HRESULT hr = mspD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(mHwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
        mspRenderTarget.ReleaseAndGetAddressOf()
    );
    ThrowIfFailed(hr);

    return S_OK;
}

HRESULT D2DFramework::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h) {
    ThrowIfFailed(CoInitialize(nullptr));

    ThrowIfFailed(InitWindow(hInstance, title, w, h), "Failed To InitWindow");
    ThrowIfFailed(InitD2D(mHwnd), "Failed To InitD2D");

    HRESULT hr = BitmapManager::Instance().Initialize(mspRenderTarget.Get());
    ThrowIfFailed(hr, "Faield To BitmapManager Initialize");

    ShowWindow(mHwnd, SW_SHOW);
    UpdateWindow(mHwnd);

    return S_OK;
}

void D2DFramework::Release() {
    BitmapManager::Instance().Release();

    mspRenderTarget.Reset();
    mspD2DFactory.Reset();

    CoUninitialize();
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

    return LRESULT();
}

// WinMain.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
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
        myFramework.Initialize(hInstance, L"BitmapManager", 1024, 768);
        int ret = myFramework.GameLoop();
        myFramework.Release();
        return ret;
    } catch (const com_exception& e) {
        OutputDebugStringA(e.what());
        MessageBoxA(nullptr, e.what(), "Error", MB_OK);
    }

    return 0;
}