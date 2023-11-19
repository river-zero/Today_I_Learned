#include <windows.h>
#include <d2d1.h>
#include <math.h>

#pragma comment (lib, "d2d1.lib")

const wchar_t gClassName[] = L"MyWindowClass";

ID2D1Factory* gpD2DFactory{};
ID2D1HwndRenderTarget* gpRenderTarget{};

ID2D1SolidColorBrush* gpBrush{};
ID2D1RadialGradientBrush* gpRadialBrush{};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnPaint(HWND hwnd);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) 
{
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&gpD2DFactory);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Failed to Create D2D Factory", L"ERROR", MB_OK);
		return 0;
	}

	HWND hwnd;
	WNDCLASSEX wc{};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Failed to Register Window Class", L"ERROR", MB_OK);
		return 0;
	}

	RECT wr = { 0, 0, 1024, 768 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	hwnd = CreateWindowEx(
		NULL,
		gClassName,
		L"Direct2D",
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
		MessageBox(nullptr, L"Failed to Create Window Class", L"ERROR", MB_OK);
		return 0;
	}

	GetClientRect(hwnd, &wr);
	hr = gpD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
		&gpRenderTarget);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Failed to Create D2D Render Target", L"ERROR", MB_OK);
		return 0;
	}

	// 솔리드 브러시 설정 및 생성
	hr = gpRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &gpBrush);

	// 그라데이션 브러시 설정 및 생성
	D2D1_GRADIENT_STOP stops[2]{
		{ 0.0f, D2D1::ColorF(D2D1::ColorF::Yellow) },
		{ 1.0f, D2D1::ColorF(D2D1::ColorF::Crimson) }
	};
	ID2D1GradientStopCollection* pGradientStops{};
	hr = gpRenderTarget->CreateGradientStopCollection(
		stops,
		2,
		&pGradientStops
	);
	if (SUCCEEDED(hr)) {
		hr = gpRenderTarget->CreateRadialGradientBrush(
			D2D1::RadialGradientBrushProperties(D2D1::Point2F(50.0f, 150.0f), D2D1::Point2F(0.0f, 0.0f), 50, 50),
			// 원형 브러시의 중심점, 시작점, x축 방향의 반지름, y축 방향의 반지름
			pGradientStops,
			&gpRadialBrush
		);
	}

	// 브러시를 생성하기 위한 임시 인터페이스는 삭제해도 무관
	if (pGradientStops != nullptr) {
		pGradientStops->Release();
		pGradientStops = nullptr;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	/*MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		OnPaint(hwnd); // 마우스 움직일때만 작동
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

	// 
	MSG msg;
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// 종료에 대한 사항이 없으므로 추가
			if (msg.message == WM_QUIT) {
				break;
			}
		} else {
			OnPaint(hwnd);
		}
	}
	
	// 소멸은 생성의 역순
	if (gpRadialBrush != nullptr) {
		gpRadialBrush->Release();
		gpRadialBrush = nullptr;
	}
	if (gpBrush != nullptr) {
		gpBrush->Release();
		gpBrush = nullptr;
	}
	if (gpRenderTarget != nullptr) {
		gpRenderTarget->Release();
		gpRenderTarget = nullptr;
	}
	if (!gpD2DFactory) {
		gpD2DFactory->Release();
		gpD2DFactory = nullptr;
	}

	return static_cast<int>(msg.wParam);
}

void OnPaint(HWND hwnd) {
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);

	// 그리는 순서에 영향을 받음에 주의
	gpRenderTarget->BeginDraw();
	gpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	gpBrush->SetOpacity(0.2f); // 투명도 설정
	// gpBrush->SetColor(D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));
	gpBrush->SetColor(D2D1::ColorF(D2D1::ColorF::LimeGreen));
	gpRenderTarget->FillRectangle(
		D2D1::RectF(0.0f, 0.0f, 100.0f, 100.0f),
		gpBrush);
	gpBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
	gpRenderTarget->FillRectangle(
		D2D1::RectF(50.0f, 50.0f, 150.0f, 150.0f),
		gpBrush);

	/*gpRenderTarget->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(50.0f, 150.0f), 50.0f, 50.0f),
		gpRadialBrush
	);*/

	// 원 좌우 이동 애니메이션
	static float angle = 0.0f;
	gpRenderTarget->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(75.0f + sinf(angle) * 25.0f, 150.0f), 50.0f, 50.0f),
		// 삼각함수는 단순히 각도가 증가함에 따라서
		// 주기적으로 -1 ~ 1의 값을 반환하므로 이를 이용 
		gpRadialBrush
	);
	angle += 0.05f; // 라디안이기 때문

	gpRenderTarget->EndDraw();

	EndPaint(hwnd, &ps);
}

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:
		OnPaint(hwnd);
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