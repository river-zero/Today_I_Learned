// DrawTriangle.h - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include "D3DFramework.h"
#include <d3dcompiler.h> // HLSL 컴파일을 위해 필요

#pragma comment (lib, "d3dcompiler.lib")

class DrawTriangle : public D3DFramework {
	struct VERTEX {
		FLOAT x, y, z;
		FLOAT color[4];
	};

	Microsoft::WRL::ComPtr<ID3D11InputLayout> mspInputLayout;
	// 정점 데이터가 GPU에 전달되기 전에 어떻게 구성되어 있는지를 지정
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspVertexBuffer;
	// 실제 정점 정보를 담고 있는 버퍼
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mspVertexShader;
	// 정점 셰이더에 대한 인터페이스
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mspPixelShader;
	// 픽셀 셰이더에 대한 인터페이스

public:
	void Initialize(HINSTANCE hInstance, int width = 800, int height = 600) override;
	void Destroy() override;

private:
	void InitTriangle();
	void InitPipeline();

protected:
	void Render() override;
};

// DrawTriangle.cpp - - - - - - - - - - - - - - - - - - - - - - -
#include "DrawTriangle.h"

void DrawTriangle::Initialize(HINSTANCE hInstance, int width, int height) {
	D3DFramework::Initialize(hInstance, width, height);

	InitTriangle();
	InitPipeline();
}

void DrawTriangle::Destroy() {
	mspVertexBuffer.Reset();
	mspInputLayout.Reset();
	mspPixelShader.Reset();
	mspVertexShader.Reset();

	D3DFramework::Destroy();
}

void DrawTriangle::InitTriangle() {
	// 삼각형 정점 데이터 초기화
	VERTEX vertices[]{
		{  0.0f,  0.5f, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{  0.5f, -0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ -0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	// 사각형 그리기
	/*VERTEX vertices[]{
		{ -0.5f,  0.5f, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{  0.5f,  0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ -0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{  0.5f, -0.5f, 0.0f, { 1.0f, 0.0f, 1.0f, 1.0f } }
	};*/

	// 정점 버퍼 생성 및 초기화
	CD3D11_BUFFER_DESC bd(
		sizeof(vertices),         // 생성될 정점 버퍼의 총 바이트 크기
		D3D11_BIND_VERTEX_BUFFER, // 생성되는 버퍼가 정점 버퍼로 사용됨
		D3D11_USAGE_DYNAMIC,      // CPU에서 데이터를 변경하고 GPU에 업로드에 사용
		D3D11_CPU_ACCESS_WRITE);  // CPU에서 버퍼의 데이터에 쓰기 액세스 권한을 부여
	mspDevice->CreateBuffer(&bd, NULL, mspVertexBuffer.ReleaseAndGetAddressOf());

	D3D11_MAPPED_SUBRESOURCE ms;
	mspDeviceContext->Map(
		mspVertexBuffer.Get(),   // 매핑할 리소스
		0,                       // 서브 리소스의 인덱스, 통째로 넘겨주므로 0
		D3D11_MAP_WRITE_DISCARD, // 매핑 방식, 값을 쓰고 이전 값은 버림
		0,                       // 추가 옵션
		&ms);                    // 매핑된 리소스의 구조체를 돌려줌
	memcpy(ms.pData, vertices, sizeof(vertices));
	// 이렇게 해야 복사 하는 와중 그래픽 카드 접근 안함
	mspDeviceContext->Unmap(mspVertexBuffer.Get(), 0);
}

// 셰이더 및 파이프라인의 Input-Assenbler 스테이지에 대한 내용 초기화
void DrawTriangle::InitPipeline() {
	// 임의의 크기를 가진 버퍼
	// 쉽게 버텍스 셰이더 버퍼와 픽셀 셰이더 버퍼라고 보면 됨
	Microsoft::WRL::ComPtr<ID3DBlob> spVS;
	Microsoft::WRL::ComPtr<ID3DBlob> spPS;

	// 정점 셰이더와 픽셀 셰이더 컴파일
	D3DCompileFromFile(
		L"VertexShader.hlsl", // 컴파일할 HLSL 파일 이름
		0,                    // HLSL의 매크로 목록
		0,                    // HLSL 헤더 파일
		"main",               // 엔트리 포인트
		"vs_4_0_level_9_3",   // 셰이더 코드의 버전
		0,                    // 추가 컴파일 옵션
		0,                    // 추가 컴파일 옵션
		spVS.GetAddressOf(),  // 컴파일 성공한 바이너리 코드를 돌려줌
		NULL);                // 에러 메시지를 담고 있는 블롭, 성공하면 NULL 반환
	D3DCompileFromFile(
		L"PixelShader.hlsl",
		0,
		0,
		"main",
		"ps_4_0_level_9_3",
		0,
		0,
		spPS.GetAddressOf(),
		NULL);

	// 정점 셰이더와 픽셀 셰이더 생성
	mspDevice->CreateVertexShader(
		spVS->GetBufferPointer(),                  // 컴파일 된 셰이더 코드
		spVS->GetBufferSize(),                     // 컴파일 된 셰이더 콛의 바이트 크기
		NULL,                                      // #pragma comment (lib, "d3dcompiler.lib")와 같은 기능
		mspVertexShader.ReleaseAndGetAddressOf()); // 생성된 셰이더 인터페이스 반환
	mspDevice->CreatePixelShader(
		spPS->GetBufferPointer(),
		spPS->GetBufferSize(),
		NULL,
		mspPixelShader.ReleaseAndGetAddressOf());

	// 셰이더를 파이프라인에 설정(Vertex Shader와 Pixel Shader 스테이지)
	mspDeviceContext->VSSetShader(
		mspVertexShader.Get(), // 설정할 셰이더 포인터
		NULL,                  // 클래스 인터페이스의 배열
		0);                    // 클래스 인스턴스의 개수
	mspDeviceContext->PSSetShader(
		mspPixelShader.Get(),
		NULL,
		0);

	// 입력 레이아웃 생성 및 설정(Input-Assembler 스테이지)
	// 시멘틱을 구조체로 묘사
	D3D11_INPUT_ELEMENT_DESC ied[]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	mspDevice->CreateInputLayout(
		ied,                                      // 입력 값 구조체 배열
		2,                                        // 입력 값의 개수
		spVS->GetBufferPointer(),                 // 컴파일된 셰이더의 포인터
		spVS->GetBufferSize(),                    // 컴파일된 셰이더의 크기
		mspInputLayout.ReleaseAndGetAddressOf()); // 생성된 입력 레이아웃의 인터페이스의 포인터
	mspDeviceContext->IASetInputLayout(mspInputLayout.Get());
}

void DrawTriangle::Render() {
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	// 정점 버퍼 및 프리미티브 토폴로지 설정(Input-Assembler 스테이지)
	mspDeviceContext->IASetVertexBuffers(
		0,                               // 연결된 슬롯 번호
		1,                               // 버텍스 버퍼 개수
		mspVertexBuffer.GetAddressOf(),  // 버텍스 버퍼 배열의 포인터      
		&stride,                         // stride 값들의 배열 포인터
		&offset);                        // offset 값들의 배열 포인터
	mspDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 그리기 명령 수행(Output Merger 스테이지)
	mspDeviceContext->Draw(3, 0);

	// 사각형 그리기
	// mspDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// mspDeviceContext->Draw(4, 0);
}

// D3DFramework.h - - - - - - - - - - - - - - - - - - - - - - - -
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

// D3DFramework.cpp - - - - - - - - - - - - - - - - - - - - - - -
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

// VertexShader.hlsl - - - - - - - - - - - - - - - - - - - - - - 
struct VOut {
    float4 position : SV_Position;
    // 4개의 flaot으로 구성된 자료형
    // SV_POSITION은 위치 정보를 담고 있다는 의미
    float4 color : COLOR;
    // COLOR는 색상 정보를 의미
};

VOut main(float4 pos : POSITION, float4 color : COLOR) {
    VOut output;
    
    output.position = pos;
    output.color = color;
    
	return output;
}

// PixelShader.hlsl - - - - - - - - - - - - - - - - - - - - - - - 
float4 main(float4 position : SV_Position, float4 color : COLOR) : SV_TARGET {
    // SV_TARGET은 렌더 타겟에 저장된다는 의미
    // 따라서 PixelShader에서만 사용 가능
    
    return color;
}

// WinMain.cpp - - - - - - - - - - - - - - - - - - - - - - - - -
#include "DrawTriangle.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) 
{
	DrawTriangle framework;
	framework.Initialize(hInstance);
	framework.GameLoop();
	framework.Destroy();
	return 0;
}