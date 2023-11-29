// Input.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

#include <array>

namespace MyUtil {
	class Input {
	private:
		std::array<bool, 256> mKeys;
		// 윈도우에서 처리하는 가상 키 코드는 0부터 255
		int mCursorX;
		int mCursorY;

	public:
		void Initialize();

		void SetKeyDown(unsigned int key);
		void SetKeyUp(unsigned int key);
		void SetCursor(int x, int y);

		bool IsKeyDown(unsigned int key);
		void GetCursor(int& x, int& y); // 혹은 반환을 pair로
	};
}

// Timer.h - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma once

namespace MyUtil {
	class Timer {
	public:
		Timer();

	public:
		void		Start();               // 시작
		void		Stop();                // 멈춤
		void		Resume();              // 재시작
		void		Update();              // 매 프레임마다 호출
		float		TotalTime() const;     // 프로그램 총 경과 시간
		float		DeltaTime() const;     // 이전 프레임과 현재 프레임의 차이
		void		SetScale(float scale); // 배속 기능

	private:
		double		mdDeltaTime;           // 현재 호출 시간과 이전 호출 시간의 차이
		double		mdSecondsPerCount;     // 시간 점검 기능이 작동하는 시간 간격
		float		mfScale;               // 시간 비율

		long long	mllBaseTime;           // 기준 시간으로 처음 구동되었을 때 시간
		long long	mllPausedTime;         // 멈춰있었던 시간
		long long	mllStopTime;           // 멈춘 시간
		long long	mllPrevTime;           // 이전 시간
		long long	mllCurrTime;           // 현재 시간

		bool		mbStopped;             // 타이머가 중지되었는지에 대한 플래그
	};
}

// DrawTriangle.h - - - - - - - - - - - - - - - - - - - - - 
#pragma once

#include "D3DFramework.h"
#include <d3dcompiler.h> // HLSL 컴파일을 위해 필요
#include <DirectXMath.h>

#pragma comment (lib, "d3dcompiler.lib")

class DrawTriangle : public D3DFramework {
	struct VERTEX {
		FLOAT x, y, z;
		FLOAT U, V;
	};

	// 셰이더에 상수 버퍼로 넘겨줄 자료 형식
	// 이를 ID3D11Buffer 형태로 변환해 셰이더로 넘겨줌
	struct MatrixBuffer {
		DirectX::XMMATRIX world;
	};

	Microsoft::WRL::ComPtr<ID3D11InputLayout> mspInputLayout;
	// 정점 데이터가 GPU에 전달되기 전에 어떻게 구성되어 있는지를 지정
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspVertexBuffer;
	// 실제 정점 정보를 담고 있는 버퍼
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mspVertexShader;
	// 정점 셰이더에 대한 인터페이스
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mspPixelShader;
	// 픽셀 셰이더에 대한 인터페이스
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspTexture;
	// 텍스처 인터페이스
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mspTextureView;
	// 셰이더 리소스 뷰에 대한 인터페이스
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mspSamplerState;
	// 샘플러 상태를 나타내는 인터페이스
	Microsoft::WRL::ComPtr<ID3D11BlendState> mspBlendState;
	// 블렌딩 상태를 나타내는 인터페이스
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspConstantBuffer;
	// 셰이더에 전달한 버퍼 인터페이스

	// 위치 및 회전을 추적할 변수들
	float mX;
	float mY;
	float mRotationZ;

	// 현재까지의 변환 정보를 저장할 행렬 멤버
	DirectX::XMMATRIX mWorld;

public:
	void Initialize(HINSTANCE hInstance, int width = 800, int height = 600) override;
	void Destroy() override;

private:
	void InitTriangle();
	void InitPipeline();

	HRESULT CreateTextureFromBMP();

protected:
	void Update(float delta) override;
	void Render() override;
}; 

// D3DFramework.h - - - - - - - - - - - - - - - - - - - - - 
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <wrl/client.h> // ComPtr을 위한 헤더
#include <d3d11.h>      // Direct3D 11에 대한 헤더
#include <string>
#include "Timer.h"
#include "Input.h"

#pragma comment (lib, "d3d11.lib") // Direct3D 11 라이브러리 연결

class D3DFramework {
	const std::wstring CLASSNAME{ L"D3DWindowClass" };
	const std::wstring TITLE{ L"D3DExample" };

protected:
	int mScreenWidth{ 800 };
	int mScreenHeight{ 600 };

	bool mMinimized{ false };  // 최소화
	bool mMaximized{ false };  // 최대화
	bool mResizing{ false };   // 사이즈 변경 중

	bool mPaused{ false };     // 앱이 멈췄는지 여부

	HWND mHwnd{};
	HINSTANCE mInstance{};

	MyUtil::Timer mTimer;      // 타이머 인스턴스
	std::wstring mTitleText{}; // 타이틀 텍스트

	MyUtil::Input mInput;      // 입력 추적 위한 인스턴스

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
	void CalculateFPS(); 
	// FPS를 계산해 타이틀 바에 출력

protected:
	void OnResize();
	void RenderFrame();
	virtual void Render() {};
	// 나중에 오버라이딩해 그리기에만 집중 가능
	virtual void Update(float delta) {};
	// 로직과 그리기를 분리하기 위해 추가한 함수

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

// PixelShader.hlsl - - - - - - - - - - - - - - - - - - - - 
Texture2D ShaderTexture;
SamplerState Sampler;

// 아래와 같이 픽셀 셰이더에서 샘플러를 정의해도 되지만
// 텍스처 매핑 방식이나 필터링은 상황에 따라 수정이 필요함
// 따라서 제어하기 쉽게 직접 제어할 수 있도록 코드 수정

// 텍스처의 텍셀이 도형에 어떻게 씌여지는지 지정
// SamplerState Sampler {
//     AddressU = Wrap;             // u 좌표가 0 ~ 1 밖에 있을 때의 매핑 방법
//     AddressV = Wrap;             // v 좌표가 0 ~ 1 밖에 있을 때의 매핑 방법
//     Filter = MIN_MAG_MIP_LINEAR; // 텍스처 필터링 설정으로 여기서는 선형 보간 사용
// };

float4 main(float4 position : SV_Position, float2 tex : TEXTCOORD0) : SV_Target {
    // 넘겨받은 버텍스의 텍스처 좌표를 샘플러를 적용해 최종 색상을 결정
    float4 result = ShaderTexture.Sample(Sampler, tex);
    
    // 셀로판지 효과 가능
    // result[0] += 1.0f;
    // result[1] += 1.0f;
    
    // RGB 값을 평균화하여 흑백 이미지로 변환
    // float grayscale = (result.r + result.g + result.b) / 3.0f;
    // result.rgb = float3(grayscale, grayscale, grayscale);
    
    // 완전 모노톤으로 변환
    // if (result[0] > 0.6) {
    //     result[0] = result[1] = result[2] = 1.0f;
    // } else {
    //     result[0] = result[1] = result[2] = 0.0f;
    // }
    
    return result;
}

// VertexShader.hlsl - - - - - - - - - - - - - - - - - - - - 
// 상수 버퍼를 정의
cbuffer MatrixBuffer {
    matrix matWorld;
};

struct VOut {
    float4 position : SV_Position;
    // 4개의 flaot으로 구성된 자료형
    // SV_POSITION은 위치 정보를 담고 있다는 의미
    float2 tex : TEXCOORD0;
    // 텍스처 좌표로 사용하기 위함
};

VOut main(float4 pos : POSITION, float2 tex : TEXCOORD0) {
    VOut output;
    
    output.position = mul(pos, matWorld);
    // HLSL에서 사용되는 행렬 곱셈 연산
    // 입력된 버텍스의 로컬 좌표를 세계 좌표계로 변환
    output.tex = tex;
    
	return output;
}

// Input.cpp - - - - - - - - - - - - - - - - - - - - - - - -
#include "Input.h"

namespace MyUtil {
	void Input::Initialize() {
		mKeys.fill(false);
		mCursorX = mCursorY = 0;
	}

	void Input::SetKeyDown(unsigned int key) {
		mKeys[key] = true;
	}

	void Input::SetKeyUp(unsigned int key) {
		mKeys[key] = false;
	}

	void Input::SetCursor(int x, int y) {
		mCursorX = x;
		mCursorY = y;
	}

	bool Input::IsKeyDown(unsigned int key) {
		return mKeys[key];
	}

	void Input::GetCursor(int& x, int& y) {
		x = mCursorX;
		y = mCursorY;
	}
}

// Timer.cpp - - - - - - - - - - - - - - - - - - - - - - - -
#include <windows.h>
#include "Timer.h"

using namespace MyUtil;

Timer::Timer() :
	mdDeltaTime{ -1.0 },
	mfScale{ 1.0f },
	mbStopped{ false },
	mdSecondsPerCount{ 0.0 },
	mllBaseTime{ 0 },
	mllPausedTime{ 0 },
	mllStopTime{ 0 },
	mllPrevTime{ 0 },
	mllCurrTime{ 0 } 
{
	// 타이머에서 사용되는 시간의 단위를 초 단위로 변환
	long long countsPerSec;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
	mdSecondsPerCount = 1.0 / static_cast<double>(countsPerSec);
}

// 현재 시간을 기준으로 타이머의 상태 및 카운터 값을 초기화
void Timer::Start() {
	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mllBaseTime = currTime;
	mllPrevTime = currTime;
	mllStopTime = 0;
	mbStopped = false;
}

void Timer::Stop() {
	// 중복 정지 방지
	if (!mbStopped) {
		long long currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mllStopTime = currTime;
		mbStopped = true;
	}
}

void Timer::Resume() {
	if (mbStopped) {
		long long currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		// 정지했었던 시간 누적
		mllPausedTime += (currTime - mllStopTime);
		mllPrevTime = currTime;
		mllStopTime = 0;
		mbStopped = false;
	}
}

void Timer::Update() {
	// 타이머가 멈춘 상태면 시간의 변화가 없으므로 
	// 델타 타임을 0으로 지정하고 종료 
	if (mbStopped) {
		mdDeltaTime = 0.0;
		return;
	}

	// 델타 타임을 초 단위로 변환해 저장
	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mllCurrTime = currTime;
	mdDeltaTime = (mllCurrTime - mllPrevTime) * mdSecondsPerCount;

	// 이전 시간을 저장
	mllPrevTime = mllCurrTime;

	// 특히 해킹 방어 코드
	if (mdDeltaTime < 0.0) {
		mdDeltaTime = 0.0;
	}
}

float Timer::TotalTime() const {
	if (mbStopped) {
		// 전체 시간 = Pause가 시작된 시간과 앱이 구동된 시간의 차이 - 멈춰 있던 시간
		return static_cast<float>((mllStopTime - mllBaseTime - mllPausedTime) * mdSecondsPerCount);
	} else {
		// 전체 시간 = 현 시간과 시작 시간의 차이 - 멈춰 있던 시간
		return static_cast<float>((mllCurrTime - mllPausedTime - mllBaseTime) * mdSecondsPerCount);
	}
}

float Timer::DeltaTime() const {
	// 스케일 값을 곱해서 보정
	return static_cast<float>(mdDeltaTime * mfScale);
}

void Timer::SetScale(float scale) {
	mfScale = scale;
}

// DrawTriangle.cpp - - - - - - - - - - - - - - - - - - - - - 
#include "DrawTriangle.h"
#include <fstream>
#include <vector>

void DrawTriangle::Initialize(HINSTANCE hInstance, int width, int height) {
	D3DFramework::Initialize(hInstance, width, height);

	InitTriangle();
	InitPipeline();

	CreateTextureFromBMP();
}

void DrawTriangle::Destroy() {
	mspBlendState.Reset();
	mspSamplerState.Reset();
	mspTextureView.Reset();
	mspTexture.Reset();
	mspVertexBuffer.Reset();
	mspInputLayout.Reset();
	mspPixelShader.Reset();
	mspVertexShader.Reset();

	D3DFramework::Destroy();
}

void DrawTriangle::InitTriangle() {
	// 정점 데이터 초기화
	VERTEX vertices[]{
		{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f, 1.0f }
	};

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

	// 직접 제어를 위한 샘플러 상태 설정 및 생성
	float border[4]{ 0.0f, 0.0f, 0.0f, 0.0f };
	CD3D11_SAMPLER_DESC sd(
		D3D11_FILTER_MIN_MAG_MIP_POINT, // 샘플링에 사용할 필터의 종류
		D3D11_TEXTURE_ADDRESS_CLAMP,    // U 좌표가 0 ~ 1 밖에 있을 때의 매핑 방법
		D3D11_TEXTURE_ADDRESS_CLAMP,    // V 좌표가 0 ~ 1 밖에 있을 때의 매핑 방법
		D3D11_TEXTURE_ADDRESS_CLAMP,    // W 좌표가 0 ~ 1 밖에 있을 때의 매핑 방법
		0.0f,                           // Mip 레벨의 오프셋
		1,                              // 비등방성 필터링에 사용되는 최대 샘플링 수
		D3D11_COMPARISON_ALWAYS,        // 샘플링 시에 사용되는 비교 함수
		border,                         // 외곽선의 색상
		0,                              // 가장 저화질 이미지의 하한값
		1);                             // 가장 고화질 이미지의 상한값
	mspDevice->CreateSamplerState(&sd, mspSamplerState.ReleaseAndGetAddressOf());

	// 블렌딩 상태를 생성
	// Src(RGB) * 1 + Dest(RGB) * (1 - Src(Alpha))
	// Src(Alpha) * 1 + Dest(Alpha) * 0
	D3D11_BLEND_DESC blendDesc{};
	// ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	mspDevice->CreateBlendState(&blendDesc, mspBlendState.ReleaseAndGetAddressOf());

	// 상수 버퍼 생성 및 초기화
	bd = CD3D11_BUFFER_DESC(
		sizeof(MatrixBuffer),
		D3D11_BIND_CONSTANT_BUFFER, // 상수 버퍼로 연결
		D3D11_USAGE_DEFAULT);       // GPU만 읽고 쓰기
	mspDevice->CreateBuffer(&bd, NULL, mspConstantBuffer.ReleaseAndGetAddressOf());

	mX = mY = 0.0f;
	mRotationZ = 0.0f;
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
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	mspDevice->CreateInputLayout(
		ied,                                      // 입력 값 구조체 배열
		2,                                        // 입력 값의 개수
		spVS->GetBufferPointer(),                 // 컴파일된 셰이더의 포인터
		spVS->GetBufferSize(),                    // 컴파일된 셰이더의 크기
		mspInputLayout.ReleaseAndGetAddressOf()); // 생성된 입력 레이아웃의 인터페이스의 포인터
	mspDeviceContext->IASetInputLayout(mspInputLayout.Get());

	// 버텍스 셰이더 스테이지에서 사용할 상수 버퍼 지정
	mspDeviceContext->VSSetConstantBuffers(0, 1, mspConstantBuffer.GetAddressOf());
}

HRESULT DrawTriangle::CreateTextureFromBMP() {
	// 파일 열기
	std::ifstream ifs;
	ifs.open("Textures/32.bmp", std::ifstream::binary);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	// BITMAPFILEHEADER 읽기
	ifs.read(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
	// BITMAPINFOHEADER 읽기
	ifs.read(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

	if (bfh.bfType != 0x4D42) return E_FAIL;
	if (bih.biBitCount != 32) return E_FAIL;

	std::vector<char> pixels(bih.biSizeImage);
	
	// 픽셀로 건너뛰기
	ifs.seekg(bfh.bfOffBits);

	// 비트맵 읽기
	int pitch = bih.biWidth * (bih.biBitCount / 8);
	char r{}, g{}, b{}, a{};
	int index{};
	for (int y = bih.biHeight - 1; y >= 0; y--) {
		// ifs.read(&pixels[y * pitch], pitch);

		index = y * pitch;
		for (int x = 0; x < bih.biWidth; x++) {
			ifs.read(&b, 1);
			ifs.read(&g, 1);
			ifs.read(&r, 1);
			ifs.read(&a, 1);

			if (static_cast<unsigned char>(r) == 30 &&
				static_cast<unsigned char>(g) == 199 &&
				static_cast<unsigned char>(b) == 250) {
				pixels[index] = pixels[index + 1] = pixels[index + 2] = pixels[index + 3] = 0;
			} else {
				pixels[index] = b;
				pixels[index + 1] = g;
				pixels[index + 2] = r;
				pixels[index + 3] = a;
			}

			index += 4;
		}
	}

	ifs.close();

	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_B8G8R8A8_UNORM,
		bih.biWidth,
		bih.biHeight,
		1,
		1);

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &pixels[0];
	initData.SysMemPitch = pitch;
	initData.SysMemSlicePitch = 0;

	// 텍스처 생성
	mspDevice->CreateTexture2D(&td, &initData, mspTexture.ReleaseAndGetAddressOf());

	// 텍스처에서 셰이더 리소스 뷰 생성
	CD3D11_SHADER_RESOURCE_VIEW_DESC srvd(
		D3D11_SRV_DIMENSION_TEXTURE2D, // 2차원 텍스처
		td.Format,                     // 텍스처의 포멧과 동일하게 지정
		0,                             // 첫 번째 Mip 레벨 사용
		1);                            // 하나의 Mip 레벨 사용
	mspDevice->CreateShaderResourceView(
		mspTexture.Get(),
		&srvd,
		mspTextureView.ReleaseAndGetAddressOf());

	return S_OK;
}

void DrawTriangle::Update(float delta) {
	/*if (mInput.IsKeyDown(VK_SPACE)) {
		OutputDebugString(L"스페이스\n");
	}*/

	if (mInput.IsKeyDown('Q')) {
		mRotationZ += DirectX::XM_PI * delta;
	} else if (mInput.IsKeyDown('E')) {
		mRotationZ -= DirectX::XM_PI * delta;
	}

	if (mInput.IsKeyDown('W') || mInput.IsKeyDown(VK_UP)) {
		mY += 1.0f * delta;
	} else if (mInput.IsKeyDown('S') || mInput.IsKeyDown(VK_DOWN)) {
		mY -= 1.0f * delta;
	}

	if (mInput.IsKeyDown('A') || mInput.IsKeyDown(VK_LEFT)) {
		mX -= 1.0f * delta;
	} else if (mInput.IsKeyDown('D') || mInput.IsKeyDown(VK_RIGHT)) {
		mX += 1.0f * delta;
	}

	// 속도 조절
	if (mInput.IsKeyDown('1')) {
		mTimer.SetScale(1.0f);
	} else if (mInput.IsKeyDown('2')) {
		mTimer.SetScale(2.0f);
	} else if (mInput.IsKeyDown('3')) {
		mTimer.SetScale(0.5f);
	}

	mWorld = DirectX::XMMatrixIdentity();
	mWorld *= DirectX::XMMatrixRotationZ(mRotationZ);
	mWorld *= DirectX::XMMatrixTranslation(mX, mY, 0.0f);
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
	mspDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 샘플러를 셰이더에 연결
	mspDeviceContext->PSSetSamplers(0, 1, mspSamplerState.GetAddressOf());

	// 셰이더에 텍스처를 넘겨주어 그리기에 텍스처 적용
	mspDeviceContext->PSSetShaderResources(0, 1, mspTextureView.GetAddressOf());

	// Output Merger 스테이지에 블렌딩 상태를 설정
	mspDeviceContext->OMSetBlendState(mspBlendState.Get(), NULL, 0xffffffff);

	// 상수 벼퍼의 데이터 갱신
	MatrixBuffer mb;
	mb.world = DirectX::XMMatrixTranspose(mWorld); 
	mspDeviceContext->UpdateSubresource(mspConstantBuffer.Get(), 0, NULL, &mb, 0, 0);

	// 그리기 명령 수행(Output Merger 스테이지)
	mspDeviceContext->Draw(4, 0);
}

// D3DFramework.cpp - - - - - - - - - - - - - - - - - - - - - 
#include "D3DFramework.h"
#include <sstream>

void D3DFramework::InitWindow(HINSTANCE hInstance) {
	WNDCLASSEX wc{};

	mInstance = hInstance;
	mTitleText = TITLE;

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
		mTitleText.c_str(),
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

void D3DFramework::CalculateFPS() {
	static int frameCount{ 0 };       // 초당 처리된 프레임 수 누적
	static float timeElapsed{ 0.0f }; // 한 프레임에 소요된 시간

	// 함수가 호출될 때마다 프레임 수를 증가
	frameCount++;

	// 이전에 FPS를 계산한 후로 1초가 경과했는지를 확인
	if (mTimer.TotalTime() - timeElapsed >= 1.0f) {
		float fps = (float)frameCount;
		// 프레임 수를 초당 프레임 수(FPS)로 변환
		float mspf = 1000.0f / fps;
		// 다시 밀리초로 변환

		std::wostringstream oss;
		oss.precision(6);
		oss << mTitleText << L" - " << L"FPS " << fps << ", Frame Time " << mspf << L"ms";

		SetWindowText(mHwnd, oss.str().c_str());

		frameCount = 0;
		// FPS 계산이 완료되면 프레임 수를 0으로 초기화
		timeElapsed += 1.0f;
		// FPS를 계산한 기준 시간을 1초 증가
	}
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

	mPaused = false;

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
	mTimer.Start();

	mInput.Initialize();

	MSG msg{};
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		} else {
			// RenderFrame();

			mTimer.Update();

			if (mPaused) {
				Sleep(100);
				// 휴식을 취해 다른 앱들에게 실행 기회를 줌
			} else {
				CalculateFPS();

				// if 컴퓨터가 느리다면 업데이트를 스킵하거나, 그리기를 스킵하거나 선택 

				Update(mTimer.DeltaTime());
				RenderFrame();
			}
		}
	}
}

LRESULT D3DFramework::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	// 자체적으로 그래픽을 그리는 경우에는 창의 배경을 지우는 작업이 불필요
	// 이 경우 메시지를 무시하고 return 1;로 지우지 않음을 나타냄 
	case WM_ERASEBKGND: 
		return 1;
		break;

	case WM_KEYDOWN:
		mInput.SetKeyDown(static_cast<unsigned int>(wParam));
		break;

	case WM_KEYUP:
		mInput.SetKeyUp(static_cast<unsigned int>(wParam));
		break;

	case WM_LBUTTONDOWN:
		mInput.SetKeyDown(VK_LBUTTON);
		break;

	case WM_LBUTTONUP:
		mInput.SetKeyUp(VK_LBUTTON);
		break;

	case WM_MOUSEMOVE:
		mInput.SetCursor(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_ACTIVATE:
		// 앱이 비활성화되면 타이머도 중지
		if (LOWORD(wParam) == WA_INACTIVE) {
			mPaused = true;
			mTimer.Stop();
		} else {
			mPaused = false;
			mTimer.Resume();
		}
		break;

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
			if (!mPaused) {
				mTimer.Stop();
			}
			mPaused = true;

			mMinimized = true;
			mMaximized = false;
		} else if (wParam == SIZE_MAXIMIZED) {
			mTimer.Resume();
			mPaused = false;

			mMinimized = false;
			mMaximized = true;
			OnResize();
		} else if (wParam == SIZE_RESTORED) {
			if (mMinimized) {
				mPaused = false;
				mTimer.Resume();

				mMinimized = false;
				OnResize();
			} else if (mMaximized) {
				mPaused = false;
				mTimer.Resume();

				mMaximized = false;
				OnResize();
			} else if (mResizing) {
				// 아무 작업 안함
			} else {
				mPaused = false;
				mTimer.Resume();

				OnResize();
			}
		}

		break;

	case WM_ENTERSIZEMOVE:
		mPaused = true;
		mResizing = true;
		mTimer.Stop();
		break;

	case WM_EXITSIZEMOVE:
		mPaused = false;
		mResizing = false;
		mTimer.Resume();
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

// WinMain.cpp - - - - - - - - - - - - - - - - - - - - - - - -
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