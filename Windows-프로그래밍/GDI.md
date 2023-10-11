- [GDI](#gdi)
- [Device Context](#device-context)
- [Window Coordinates System](#window-coordinates-system)
- [WM\_PAINT](#wm_paint)
- [WM\_ERASEBKGND](#wm_erasebkgnd)

# GDI
Graphics Device Interface를 말한다. Windows 애플리케이션에서 그래픽 요소를 생성, 표시 및 조작하는 데 사용한다.

인터페이스는 어떠한 장치들 간에서도 잘 작동하는 규칙이나 규약이다. GDI 역시 이러한 특성을 가지고 있어 컴퓨터의 출력을 단순히 모니터로만 보내는 것이 아니라 프린터와 같은 다양한 출력 장치로 동일하게 보낼 수 있다. 따라서 윈도우 프로그래머는 서로 다른 하드웨어에 직접 접근할 필요 없이 GDI를 통해서 동일한 코딩으로 서로 다른 장치에 출력을 할 수 있게 되는 것이다.

# Device Context
줄여서 DC라고 부르기도 한다. 해당 출력 장치에 데이터를 출력하기 위한 정보와 설정들을 담고 있는 개체이다. GDI에서 사용하며 출력할 그래픽 요소의 모양, 색상, 폰트, 위치 등을 정의하고 출력 장치에 전달하는 역할을 한다.

# Window Coordinates System
그래픽 출력을 다룰 때 사용되는 좌표 시스템이다. 화면의 창 또는 클라이언트 영역 내에서 객체의 위치와 크기를 정의하는 데 사용된다. 일반적으로 왼쪽 상단 모서리를 원점(0, 0)으로 가지며 오른쪽(x축)으로 갈수록 증가하고, 아래쪽(y축)으로 갈수록 증가한다. 일반적인 수학에서의 개념과 살짝 다르므로 헷갈리지 않도록 주의하자.

# WM_PAINT
Microst Windows 운영 체제에서 발생하는 윈도우 메시지 중 하나다. 화면에 윈도우 내용을 다시 그리라는 요청을 나타내며, 대부분의 Windows 응용 프로그램에서 그래픽 요소를 업데이트하고 화면에 표시할 때 사용된다.

이 메시지는 UpdateWindow 또는 RedrawWindow 함수가 호출되거나, 애플리케이션이 GetMessage 또는 PeekMessage 함수를 사용하여 WM_PAINT 메시지를 가져올 때 DispatchMessage 함수에 의해 전송된다.

# WM_ERASEBKGND
Microst Windows 운영 체제에서 발생하는 윈도우 메시지 중 하나다. 윈도우의 클라이언트 영역의 배경을 지우고 다시 그리라는 요청을 나타낸다. 주로 윈도우 내의 그리픽 요소를 업데이트하거나 그릴 때 사용된다.