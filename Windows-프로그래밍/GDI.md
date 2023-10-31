- [GDI](#gdi)
- [Device Context](#device-context)
- [Window Coordinates System](#window-coordinates-system)
- [WM\_PAINT](#wm_paint)
- [WM\_ERASEBKGND](#wm_erasebkgnd)
- [기타 그래픽 개체](#기타-그래픽-개체)

# GDI
Graphics Device Interface를 말한다. 최초 윈도우와 함께 등장한 그래픽 시스템으로 그래픽 요소를 생성, 표시 및 조작하는 데 사용한다.

인터페이스는 어떠한 장치들 간에서도 잘 작동하는 규칙이나 규약이다. GDI 역시 이러한 특성을 가지고 있어 컴퓨터의 출력을 단순히 모니터로만 보내는 것이 아니라 프린터와 같은 다양한 출력 장치로 동일하게 보낼 수 있다. 따라서 윈도우 프로그래머는 서로 다른 하드웨어에 직접 접근할 필요 없이 GDI를 통해서 동일한 코딩으로 서로 다른 장치에 출력을 할 수 있게 되는 것이다.

# Device Context
줄여서 DC라고 부르기도 한다. 해당 출력 장치에 데이터를 출력하기 위한 정보와 설정들을 담고 있다. 윈도우의 모든 그리기 오브젝트는 이러한 DC를 통해 이루어진다.

```
LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
) {
    switch (message) {
    case WM_LBUTTONDOWN:
    {
        HDC hdc = nullptr;               // HDC는 DC에 대한 포인터
        hdc = GetDC(hWnd);               // 해당 윈도우의 DC를 반환
        Rectangle(hdc, 0, 0, 100, 100);  
        ReleaseDC(hWnd, hdc);            // 꼭 사용한 DC를 반환
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WN_DESTROY:
        PstQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```

사용한 DC는 꼭 ReleaseDC로 반환해주어야 한다. 윈도우는 최대 허용 GDI 개체 수가 정해져 있어서 허용치를 넘어가면 더 이상 윈도우가 표시되지 않거나 운영체제가 다운되는 경우도 발생하므로 주의해야 한다.

# Window Coordinates System
그래픽 출력을 다룰 때 사용되는 좌표 시스템이다. 화면의 창 또는 클라이언트 영역 내에서 객체의 위치와 크기를 정의하는 데 사용된다. 일반적으로 왼쪽 상단 모서리를 원점(0, 0)으로 가지며 오른쪽(x축)으로 갈수록 증가하고, 아래쪽(y축)으로 갈수록 증가한다. 일반적인 수학에서의 개념과 살짝 다르므로 헷갈리지 않도록 주의하자.

# WM_PAINT
GDI는 성능을 위해서 화면에 매번 그림을 다시 그리는 것이 아니라 갱신이 필요한 부분만 다시 그리는 방식이다. 시스템이나 다른 응용 프로그램이 윈도우의 일부분에 대해 그리기 요청을 보내면 발생하는 메시지가 바로 WM_PAINT이다.

이 메시지는 UpdateWindow 또는 RedrawWindow 함수가 호출되거나, 애플리케이션이 GetMessage 또는 PeekMessage 함수를 사용하여 WM_PAINT 메시지를 가져올 때 DispatchMessage 함수에 의해 전송된다.

```
```
LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;                   
        // 윈도우의 클라이언트 영역을 칠할 때 사용되는 구조체 정보
        HDC hdc = BeginPaint(hWnd, &ps);  
        // 다시 그릴 윈도우의 핸들, PAINTSTRUCT 구조체의 포인터 전달
        // PAINTSTRUCT 구조체 HDC가 포함되어 GetDC가 자동으로 이뤄짐
        Rectagle(hdc, 0, 0, 100, 100);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WN_DESTROY:
        PstQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```
```

# WM_ERASEBKGND
Microst Windows 운영 체제에서 발생하는 윈도우 메시지 중 하나다. 윈도우의 클라이언트 영역의 배경을 지우고 다시 그리라는 요청을 나타낸다. 주로 윈도우 내의 그래픽 요소를 업데이트하거나 그릴 때 사용된다.

# 기타 그래픽 개체
GDI에서는 그 외에도 브러시, 펜, 기하도형과 같은 기능이 있다.

브러시를 사용할 때는 주의해야 한다. SelectObject 함수를 통해 현재 브러시를 지정해 줘야 하는데 이렇게 되면 계속 새로 만든 브러시가 유지되어 버리므로 아래와 같은 과정을 거친다.

1. SelectObject로 새로운 브러시 지정
2. SelectObject의 반환값인 이전 브러시를 저장
3. 그리기 수행
4. DeleteObject로 새로운 브러시 해제
5. SelectObject로 저장한 원본 브러시 복구

```
void OnPaint(HWND hwnd) {
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(hwnd, &ps);

    HPEN bluePen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
    HPEN oldPen = (HPEN)SelectPbject(hdc, bluePen);
    MoveToEx(hdc, 0, 110, nullptr); // 시작점
    LineTo(hdc, 100, 110);          // 끝점
    DeleteObject(bluePen);
    SelectObject(hdc, oldPen);

    HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hatchBrush);
    Rectagle(hac, 0, 0, 100, 100);
    DeleteObject(hatchBrush);
    SelectObject(hdc, oldBrush);

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
) {
    switch (message) {
    case WM_PAINT:
    {
        OnPaint(hWnd);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WN_DESTROY:
        PstQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```