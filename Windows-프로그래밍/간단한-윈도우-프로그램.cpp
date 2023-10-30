#include <sstream>
#include <Windows.h>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Entry Point
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstace,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) {
	Gdiplus::GdiplusStartupInput gpsi;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gpsi, nullptr);

	// 1. 윈도우클래스 등록
	WNDCLASSEX wc{};
	// 구조체를 만들면 반드시 초기화가 필요
	// 또는 ZeroMemory(&wc, sizeof(WNDCLASS));
	// memset(&wc, 0, sizeof(WNDCLASS));의 기능을 줄인 것
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	// 여기는 필수 요소는 아님
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// 운영체제에 윈도우클래스를 등록
	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
		return 0;
	}

	// 2. 윈도우를 생성
	RECT wr = { 0, 0, 640, 480 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE); // 클라이언트 영역을 만듦

	HWND hwnd;
	hwnd = CreateWindowEx(
		0,
		gClassName,
		L"HelloWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	// 생성 실패한 경우
	if (!hwnd) {
		MessageBox(nullptr, L"Failed to create", L"Error", MB_OK);
		return 0;
	}

	// 여기는 세트로 생각
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	// 3. 윈도우 메시지 처리
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiToken);
	return msg.wParam;
}

void OnPaint(HWND hwnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	/*HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	SelectObject(hdc, hatchBrush);
	SelectObject(hdc, bluePen);
	Rectangle(hdc, 0, 0, 100, 100);

	// 메모리르 차지하므로 꼭 삭제
	DeleteObject(bluePen);
	DeleteObject(hatchBrush);*/

	Gdiplus::Pen bluePen(Gdiplus::Color(255, 0, 0, 255));
	Gdiplus::HatchBrush hatchBrush(Gdiplus::HatchStyle::HatchStyleCross, Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::Image image(L"image.png");

	Gdiplus::Graphics graphics(hdc);
	graphics.DrawRectangle(&bluePen, 0, 0, 100, 100);
	graphics.DrawImage(&image, 0, 0, 640, 480);

	EndPaint(hwnd, &ps);
}

// 4. 윈도우 프로시저 작성 - Event Handler
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT: // 그리기는 모아서
	{
		OnPaint(hWnd);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		std::ostringstream oss;
		oss << "x : " << LOWORD(lParam)
			<< ", y : " << HIWORD(lParam) << std::endl;
		OutputDebugStringA(oss.str().c_str());
		// oss의 내용을 C++ 문자열로 변환하고
		// C 스타일의 문자열로 변환해 해당 문자열의 포인터를 반환
		break;
	}
	case WM_KEYDOWN:
	{
		std::ostringstream oss;
		oss << "Virtual Keycode = " << wParam << std::endl;
		OutputDebugStringA(oss.str().c_str());
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}