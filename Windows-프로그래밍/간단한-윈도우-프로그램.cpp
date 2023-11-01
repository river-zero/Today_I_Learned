#include <sstream>
#include <Windows.h> // 윈도우에서 돌아가므로 이것도 꼭 같이 포함
#include <gdiplus.h> // GDI+에 대한 선언이 포함된 헤더

#pragma comment (lib, "Gdiplus.lib") // 정의들은 선언과는 또 별개로 라이브러리 파일을 등록

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Entry Point
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstace,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) {
	Gdiplus::GdiplusStartupInput gpsi;                  // GDI+를 초기화하기 위한 정보를 가진 구조체
	ULONG_PTR gdiToken;                                 // 자격증명번호로 이걸로 GDI+ 기능을 이용 가능
	Gdiplus::GdiplusStartup(&gdiToken, &gpsi, nullptr); // 기본 시스템이 아니어서 직접 구동
	// Gdiplus::Status는 상태를 정의한 열거형으로 정상 처리되었다면 Ok 반환

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
	RECT wr = { 0, 0, 640, 480 };                      // 표현하고자 하는 영역을 지정
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE); // 클라이언트 영역 크기로 테두리 및 캡션을 고려한 전체 윈도우 크기를 계산

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

	Gdiplus::GdiplusShutdown(gdiToken); // GDI+를 종료하고 사용한 모든 리소스를 지움
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

	// 메모리를 차지하므로 꼭 삭제
	DeleteObject(bluePen);
	DeleteObject(hatchBrush);*/

	Gdiplus::Pen bluePen(Gdiplus::Color(255, 0, 0, 255));
	// HPEN과 CreatePen의 클래스 버전
	// Color와 REAL이면 색상과 너비를 지정, Brush와 REAL이면 브러시와 너비를 지정
	// GDI+는 ARGB를 표현할 수 있어 알파 즉, 투명도를 지정 가능
	Gdiplus::HatchBrush hatchBrush(Gdiplus::HatchStyle::HatchStyleCross, Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 255, 0, 255));
	// HBRUSH와 CreateSolidBrush의 GDI+ 객체
	// Color를 지정하는 생성자를 통해 브러시 인스턴스를 만듦
	Gdiplus::Image image(L"image.png");
	// Image 클래스는 파일 이름, 입력 스트림으로 생성 가능
	// 가장 빠르고 원본 그대로 그리는 코드는 graphics.DrawImage(&image, 120, 10, image.GetWidth(), image.GetHeight());

	Gdiplus::Graphics graphics(hdc);
	// 대부분의 그리기 오브젝트 기르기를 담당하는 클래스
	// HDC면 DC에 직접 그리기, HWND와 BOOL이면 윈도우에 직접 그리기, Image*이면 이미지에 그리기, HDC와 HANDLE이면 DC와 특정 장치를 명시해서 그리기
	graphics.DrawRectangle(&bluePen, 0, 0, 100, 100);
	graphics.DrawLine(&bluePen, 0, 0, 100, 100); // 역시 반환값은 Status 열거형
	graphics.DrawImage(&image, 0, 0, 640, 480);
	// 너비와 높이를 지정하면 해당 크기만큼 이미지를 늘려줌

	Gdiplus::FontFamily fontFamily(L"맑은 고딕");
	Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);  
	// 폰트 인스턴스를 생성
	// 매개변수는 폰트 패밀리 객체에 대한 포인터, em 형태로 폰트 크기, 폰트 패밀리 스타일 지정, 폰트 단위
	// UnitPixel이고 em이 1.0이면 폰트 크기는 1 Pixel
	Gdiplus::PointF pointF(0.0f, 110.0f);
	// 2차원 좌표(x, y)를 float으로 표현하는 클래스
	graphics.DrawString(L"이것은 텍스트입니다.", -1, &font, pointF, &solidBrush);
	// 매개변수는 출력할 wchar_t 문자열, 문자열의 문자 개수, 폰트 인스턴스 포인터, 시작 지점, 브러시 인스턴스 포인터
	// -1을 넘겨주면 null 종결자를 찾을 때까지 문자열을 출력
	// 역시 반환형은 Status 열거형

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