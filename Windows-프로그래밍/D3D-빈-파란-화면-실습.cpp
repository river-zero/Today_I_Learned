// D3DFramework.h - - - - - - - - - - - - - - - -  - - - - - - -
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <wrl/client.h> // ComPtr을 위한 헤더
#include <d3d11.h>      // Direct3D 11에 대한 헤더
#include <string>

#pragma comment (lib, "d3d11.lib") // Direct3D 11 라이브러리 연결

class D3DFramework {
	const std::wstring CLASSNAME{ L"D3DWindowClass" };
	const std::wstring TITLE{ L"D3DExample" };

protected:
	int mScreenWidth{ 800 };
	int mScreenHeight{ 600 };

	bool mMinimized{ false }; // 최소화
	bool mMaximized{ false }; // 최대화
	bool mResizing{ false };  // 사이즈 변경 중

	HWND mHwnd{};
	HINSTANCE mInstance{};

	Microsoft::WRL::ComPtr<IDXGISwapChain> mspSwapChain{};
	Microsoft::WRL::ComPtr<ID3D11Device> mspDevice{};
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mspDeviceContext{};
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspRenderTarget{};
	// 렌더링할 대상으로 2차원 텍스처를 지정
	// 백 버퍼에만 그리지 않는 이유는 렌더링을 다른 곳에도 사용하는 경우 있기 때문
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mspRenderTargetView{};
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspDepthStencil{};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mspDepthStencilView{};

private:
	void InitWindow(HINSTANCE hInstance);
	void InitD3D();

protected:
	void OnResize();
	void RenderFrame();
	virtual void Render() {};
	// 나중에 오버라이딩해 그리기에만 집중 가능

public:
	virtual void Initialize(HINSTANCE hInstance, int width = 800, int height = 600);
	virtual void Destroy();
	void GameLoop();
	
public:
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
// 메시지 프로시저에서 클래스 내부에 접근할 경우가 많은 경우에 이렇게 사용
// static을 대체할 수 있음

// D3DFramework.cpp - - - - - - - - - - - - - - - -  - - - - - -
#include "D3DFramework.h"

void D3DFramework::InitWindow(HINSTANCE hInstance) {
	WNDCLASSEX wc{};

	mInstance = hInstance;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASSNAME.c_str();
	wc.hInstance = mInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Failed to Register Window Class", L"Error", MB_OK);
		return;
	}

	RECT wr{ 0,0,mScreenWidth, mScreenHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	mHwnd = CreateWindowEx(
		NULL,
		CLASSNAME.c_str(),
		TITLE.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (mHwnd == NULL) {
		MessageBox(NULL, L"Failed to Create Window Class", L"Error", MB_OK);
		return;
	}

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	// 윈도우에 유저 데이터 추가

	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd); // 게임을 실행하면 즉시 바로 앞으로 가져옴
	SetFocus(mHwnd);            // 포커스를 지정된 창으로 설정
	UpdateWindow(mHwnd);
}

void D3DFramework::InitD3D() {
	DXGI_SWAP_CHAIN_DESC scd{};
	// ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));와 동일

	scd.BufferCount = 1;
	// front buffer는 필수이므로 back buffer 개수를 설정
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = mHwnd;
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;
	scd.BufferDesc.Width = mScreenWidth;
	scd.BufferDesc.Height = mScreenHeight;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// 창 모드와 전체 화면 모드 스위치 가능

	// 1. 디바이스 컨텍스트 포함해 디바이스 생성
	// 2. 스왑 체인 생성
	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		mspSwapChain.ReleaseAndGetAddressOf(),
		mspDevice.ReleaseAndGetAddressOf(),
		NULL,
		mspDeviceContext.ReleaseAndGetAddressOf());

	OnResize();
}

// 해상도 변경 작업
void D3DFramework::OnResize() {
	// 기존에 생성된 디바이스 리소스들을 모두 해제
	ID3D11RenderTargetView* nullViews[]{ NULL };
	mspDeviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, NULL);

	mspRenderTargetView.Reset();
	mspDepthStencilView.Reset();
	mspRenderTarget.Reset();
	mspDepthStencil.Reset();
	mspDeviceContext->Flush();
	// 명령 큐의 남은 모든 명령을 GPU에 즉시 적용

	mspSwapChain->ResizeBuffers(
		0,
		mScreenWidth,
		mScreenHeight,
		DXGI_FORMAT_UNKNOWN,
		0);

	// 3. 후면 버퍼를 렌더 타겟으로 지정(렌더 타겟 뷰 생성)
	mspSwapChain->GetBuffer(0, IID_PPV_ARGS(mspRenderTarget.ReleaseAndGetAddressOf()));
	// COM 인터페이스를 얻기 위한 매크로
	// 인터페이스의 GUID와 해당 인터페이스 포인터의 주소를 하나로 묶어줌
	mspDevice->CreateRenderTargetView(
		mspRenderTarget.Get(),
		NULL,
		mspRenderTargetView.ReleaseAndGetAddressOf());

	// 4. 깊이-스텐실 버퍼 생성(깊이-버퍼 뷰 생성)
	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_D24_UNORM_S8_UINT, // 24비트 깊이와 8비트 스텐실 포맷
		mScreenWidth,
		mScreenHeight,
		1,                             // 밉맵을 사용하지 않고 하나의 레벨만을 가짐
		1,                             // 배열 텍스처가 아닌 하나의 텍스처만 가짐
		D3D10_BIND_DEPTH_STENCIL);     // 해당 텍스처를 깊이 스텐실 텍스처로 사용
	// 주의할 점은 스왑 체인에서 사용한 MSAA 설정과깊이 스텐실의 설정이 같아야 정상 작동
	mspDevice->CreateTexture2D(&td, NULL, mspDepthStencil.ReleaseAndGetAddressOf());
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvd(D3D11_DSV_DIMENSION_TEXTURE2D);
	// 2D 텍스처에 대한 깊이 스텐실 뷰를 생성
	mspDevice->CreateDepthStencilView(
		mspDepthStencil.Get(),
		&dsvd,
		mspDepthStencilView.ReleaseAndGetAddressOf());

	// 파이프라인의 마지막 단계인 OM 스테이지를 설정
	mspDeviceContext->OMSetRenderTargets(
		1,
		mspRenderTargetView.GetAddressOf(),
		mspDepthStencilView.Get());

	// 5. 뷰포트 지정
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		static_cast<FLOAT>(mScreenWidth),
		static_cast<FLOAT>(mScreenHeight));
	mspDeviceContext->RSSetViewports(1, &viewport);
}

// 6. 화면에 그리기
void D3DFramework::RenderFrame() {
	float bg[4]{ 0.0f, 0.2f, 0.4f, 1.0f };

	// 6-1. 렌더 타겟 지우기
	mspDeviceContext->ClearRenderTargetView(mspRenderTargetView.Get(), bg);
	// 6-2. 깊이 스텐실 지우기
	mspDeviceContext->ClearDepthStencilView(
		mspDepthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// 6-3. 실제 그리기
	Render();

	// 6-4. 스왑(플립)
	mspSwapChain->Present(0, 0);
}

void D3DFramework::Initialize(HINSTANCE hInstance, int width, int height) {
	mScreenWidth = width;
	mScreenHeight = height;

	InitWindow(hInstance);
	InitD3D();
	// ShowWindow 전이면 로딩이 끝나고 윈도우 창 실행
	// 게임에서는 먼저 창을 띄우고 로딩하는게 나음
}

void D3DFramework::Destroy() {
	mspSwapChain->SetFullscreenState(FALSE, NULL);
	// 전부 해제하기 전 창 모드로 전환
	// 창 모드일 경우에는 무조건 NULL
	// Alt + Enter 키로 확인해 볼 수 있음

	mspDepthStencil.Reset();
	mspDepthStencilView.Reset();
	mspRenderTarget.Reset();
	mspRenderTargetView.Reset();
	mspSwapChain.Reset();
	mspDevice.Reset();
	mspDeviceContext.Reset();

	// 프로그램이 종료될 때 자동으로 사라지지만
	// 간혹 삭제가 안되는 경우를 방지
	DestroyWindow(mHwnd);
	UnregisterClass(CLASSNAME.c_str(), mInstance);
}

void D3DFramework::GameLoop() {
	MSG msg{};
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		} else {
			RenderFrame();
		}
	}
}

LRESULT D3DFramework::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:
		// 창 크기 조절 중 거슬리는 검은색 제거
		// 사이즈 변경 중이라면 강제로 화면을 갱신
		if (mResizing) {
			RenderFrame();
		} else { // 그 외는 기본 그리기
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
		}

		break;

	case WM_SIZE:
		mScreenWidth = LOWORD(lParam);
		mScreenHeight = HIWORD(lParam);

		// 그래픽 디바이스가 초기화되지 않은 경우 예외 처리
		if (!mspDevice) {
			break;
		}

		if (wParam == SIZE_MINIMIZED) {
			mMinimized = true;
			mMaximized = false;
		} else if (wParam == SIZE_MAXIMIZED) {
			mMinimized = false;
			mMaximized = true;
			OnResize();
		} else if (wParam == SIZE_RESTORED) {
			if (mMinimized) {
				mMinimized = false;
				OnResize();
			} else if (mMaximized) {
				mMaximized = false;
				OnResize();
			} else if (mResizing) {
				// 아무 작업 안함
			} else {
				OnResize();
			}
		}

		break;

	case WM_ENTERSIZEMOVE:
		mResizing = true;
		break;

	case WM_EXITSIZEMOVE:
		mResizing = false;
		OnResize();
		break;

	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);
		break;

	case WM_GETMINMAXINFO:
		reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = 640;
		reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = 480;
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	auto pFramework = reinterpret_cast<D3DFramework*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	return pFramework->MessageHandler(hwnd, message, wParam, lParam);
}

// WinMain.cpp - - - - - - - - - - - - - - - -  - - - - - - - - -
#include "D3DFramework.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) 
{
	D3DFramework framework;
	framework.Initialize(hInstance);
	framework.GameLoop();
	framework.Destroy();
	return 0;
}