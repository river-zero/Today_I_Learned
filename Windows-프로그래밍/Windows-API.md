- [Windows API](#windows-api)
- [윈도우 클래스(WNDCLASSEX)](#윈도우-클래스wndclassex)
- [HINSTANCE](#hinstance)
- [HWND](#hwnd)
- [이벤트 메시지 시스템(Event Message System)](#이벤트-메시지-시스템event-message-system)
- [윈도우 프로시저(Window Procedure)](#윈도우-프로시저window-procedure)
- [MessageBox()](#messagebox)
- [RegisterClassEx()](#registerclassex)
- [CreateWindowEx()](#createwindowex)
- [ShowWindow()](#showwindow)
- [MSG](#msg)
- [While(GetMessage()) {}](#whilegetmessage-)
- [DefWindowProc()](#defwindowproc)
- [WM\_LBUTTONDOWN](#wm_lbuttondown)
- [OutputDebugString()](#outputdebugstring)

# Windows API
Windows API는 Windows 운영 체제와 상호 작용하고 Windows 환경에서 소프트웨어를 개발하고 제어하기 위한 도구 및 명령을 제공한다. 윈도우 개발의 원조로 Windows 3.1의 탄생부터 함께해 C언어로 되어있다. 동적 링크 라이브러리(DLL) 방식을 사용하며 창 관리, 파일 조작, 네트워크 설정, 그래픽 처리 및 다양한 시스템 작업을 수행할 수 있다. 

```
#include <Windows.h>

int WINAPI WinMain(                 // 윈도우 버전 main()
  _In_ HINSTANCE hInstance,         // 실행시킨 앱의 현재 인스턴스 핸들
  _In_Opt_ HINSTANCE hPrevInstance, // 이전 인스턴스의 핸들
  _In_ LPSTR lpCmdLine,             // 명령줄(추가 명령 가능), char* 타입
  _In_ int nShowCmd                 // 일반, 전체, 최소화 화면으로 표시할지에 대한 사항
)
```

여기서 `_In_`, `_In_Opt_` 등은 용도를 명시하기 위해 사용한다.

윈도우 앱을 만들기 위해서는 아래 4가지 과정을 거친다.

1. 윈도우 클래스 등록 : WNDCLASSEX 구조체에 윈도우 정보를 채우고 RegisterClassEx() 호출
2. 윈도우 생성 : CreateWindowEx() 호출
3. 윈도우 메시지 처리 : GetMessage(), TranslateMessage(), DispatchMessage() 호출
4. 윈도우 프로시저 작성 : LRESULT CALLBACK proc-name (HWND, UINT, WPARAM, LPARAM) 함수 구현 및 WNDCLASSEX에 지정

# 윈도우 클래스(WNDCLASSEX)
윈도우 클래스의 정보를 담고 있는 구조체다. 윈도우 클래스를 정의하고 등록하는 데 필요하다. 다음과 같은 멤버를 포함하고 있다. EX가 붙으면 조금 더 최신 버전으로 추가 정보를 가지고 있다.

> style
>
> 윈도우 클래스의 스타일을 지정한다. 이 스타일은 윈도우의 모양과 동작을 정의한다. CS_HREDRAW | CS_VREDRAW는 가로 또는 세로로 이동되면 윈도우를 다시 그려달라는 의미다.

> lpszClassName 
>
> 윈도우 클래스의 이름을 나타낸다. 이렇게 지정한 윈도우 클래스는 동일한 스타일이라면 해당 클래스 이름으로 여러 개의 윈도우를 만들 수 있다.

> hInstance
>
> 현재 실행 중인 윈도우 앱을 구분하고 식별하는 데 사용되는 값이다. 보통 WinMain에서 인자로 받은 값을 그대로 넘겨준다.

> hCursor
>
> 윈도우의 마우스 커서를 지정한다.

> hbrBackground
>
> 윈도우의 배경색을 칠할 브러시를 지정한다.

> lpfnWndProc
>
> 윈도우의 메시지 처리 함수인 윈도우 프로시저의 포인터다. 

> cbSize
>
> 구조체의 크기를 나타낸다. WNDCLASSEX 구조체 자체의 크기를 나타낸다. Windows 시스템이 이 구조체를 올바르게 인식하기 위해서 꼭 이 값을 설정해주어야 한다.

# HINSTANCE
Handle of Instance를 말한다. 핸들은 포인터이고 인스턴스는 우리가 만드는 앱의 실행 버전이라고 보면 된다. 메모장을 여러 번 실행할 수 있는 것처럼 윈도우 앱들은 하나의 프로그램을 여러 개 실행해 여러 개의 인스턴스를 만들 수 있다. 각 인스턴스는 독립된 실행 환경을 제공한다.

# HWND
Handle of Window를 말한다. 모든 윈도우는 고유한 HWND를 가지고 있어 특정 윈도우를 식별하고 해당 윈도우와 상호 작용할 수 있다. 일반적으로 정수로 표현되며 NULL이라면 윈도우를 식별하지 않는 데 사용된다.

# 이벤트 메시지 시스템(Event Message System)
멀티태스킹 환경에서 윈도우 응용 프로그램이 사용자와 상호 작용하고 시스템과 통신하는 방법에 대한 중요한 개념이다. 

사용자의 입력(마우스 클릭, 키보드 입력 등) 또는 시스템 이벤트(윈도우 크기 조정, 윈도우 닫기 등)와 같은 다양한 이벤트가 발생한다. 이벤트 메시지 시스템은 해당 이벤트를 감지하고, 감지된 이벤트는 메시지로 변환된다. 보낸 메시지에는 특정 이벤트를 설명하는 정보가 포함된다. 메시지 큐라고 불리는 대기열에 메시지들을 순서대로 저장하고 대기시킨다. 윈도우 응용 프로그램은 주로 무한 루프로 이루어진 메시지 루프를 가지고, 이 루프는 메시지 큐에서 메시지를 하나씩 가져와 해당 메시지를 처리한다. 

윈도우도 마찬가지로 GetMessage를 통해 메시지를 가져온다. 그리고 TranslateMessage로 처리하기 쉽게 변환한다. DispatchMessage로 해당 메시지를 윈도우 생성 시 등록한 윈도우 프로시저에 넘겨준다.

# 윈도우 프로시저(Window Procedure)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)으로 DispatchMessage가 호출되면 이 함수가 자동으로 불린다. 각 윈도우 또는 컨트롤의 이벤트 처리를 담당하는 함수로 사용자와 프로그램 간에 상호 작용을 가능하게 한다.

콜백 함수는 함수를 일부러 호출하지 않아도 등록된 함수를 필요에 따라 자동적으로 호출하는 방식이다. 윈도우 프로시저도 콜백 함수의 일종이라 볼 수 있다. 이러한 방식을 이벤트 주도 개발이라고도 부른다.

> WM_CLOSE
>
> 윈도우가 닫힐 때 전달되는 메시지다.

> DestroyWindow(hWnd)
>
> 해당 윈도우를 파괴한다. 윈도우 생성에서 사용한 정보들을 모두 메모리에서 해제한다.

> WM_DESTORY
>
> 윈도우가 파괴될 때 불리는 메시지다. 메모리 해제와 같은 종료 시의 처리를 여기서 한다.

> PostQuitMessage(0)
>
> WM_QUIT이라는 윈도우 메시지를 보낸다. 메시지 루프에서 메인 루프가 종료될 때에만 FALSE를 반환한다고 하였는데, 더 자세하게는 WM_QUIT 메시지를 받으면 종료되는 것이다.

# MessageBox()
간단한 메시지 대화상자를 표시하는 데 사용한다. 사용자에게 메시지, 경고 또는 정보를 표시하고 사용자의 응답을 받을 수 있다.

```
int MessageBox(
  [in, optional] HWND    hWnd,
  [in, optional] LPCTSTR lpText,
  [in, optional] LPCTSTR lpCaption,
  [in]           UINT    uType
);
```

> HWND hWnd
>
> 메시지 박스를 소유할 부모 윈도우를 지정한다. nullptr을 주면 운영체제가 메시지 박스를 제어한다.

> LPCTSTR lpText
>
> 메시지 박스에 표시될 내용을 전달받는다. 확장 문자열 리터럴로 L"" 접두어를 사용한다.

> LPCTSTR lpCaption
>
> 메시지 박스 제목 표시줄에 표시될 내용이다.

> UINT uType
>
> 메시지 박스의 형태를 지정한다. 아주 다양한 형태와 조합이 있기 때문에 자세한 것은 F1을 눌러 MSDN을 참고하자.

# RegisterClassEx()
새로운 윈도우 클래스를 등록하는 데 사용한다. 이 함수를 호출하여 윈도우 클래스를 등록하고 해당 클래스를 기반으로 윈도우를 생성한다. WNDCLASSEX 구조체를 매개변수로 받으며 성공하면 클래스의 ATOM이라는 운영체제에서 고유한 값(정수)를 반환하고 실패하면 0을 반환한다.

# CreateWindowEx()
새로운 윈도우를 생성하는 데 사용한다. 이 함수를 호출해 새로운 윈도우를 만들고, 윈도우를 표시하고 상호 작용할 수 있다. 성공적으로 윈도우가 만들어지면 생성된 윈도우의 핸들인 HWND 값이 반환되고, 실패하면 NULL이 반환된다.

```
HWND CreateWindowExA(
  [in]           DWORD     dwExStyle,
  [in, optional] LPCSTR    lpClassName,
  [in, optional] LPCSTR    lpWindowName,
  [in]           DWORD     dwStyle,
  [in]           int       X,
  [in]           int       Y,
  [in]           int       nWidth,
  [in]           int       nHeight,
  [in, optional] HWND      hWndParent,
  [in, optional] HMENU     hMenu,
  [in, optional] HINSTANCE hInstance,
  [in, optional] LPVOID    lpParam
);
```

> DWORD dwExStyle
>
> 기본 스타일 외에 추가 스타일을 지정할 때 사용한다.

> LPCTSTR lpClassName
>
> 생성할 윈도우의 클래스 이름을 지정한다. RegisterClassEx 함수로 미리 등록되어 있어야 한다.

> LPCTSTR lpWindowName
>
> 윈도우의 제목을 지정한다. 타이틀바가 있다면 표시된다.

> DWORD dwStyle
>
> 윈도우의 스타일을 지정한다. 예를 들어, 윈도우의 크기 조절 가능 여부, 닫기 버튼의 유무 등을 지정할 수 있다.

> int x 및 int y
>
> 윈도우의 화면상 위치를 지정한다. CW_USEDEFAULT는 운영체제가 자동으로 위치를 지정한다.

> int nWidth 및 int Height
>
> 윈도우의 너비와 높이를 지정한다.

> HWND hWndParent
>
> 부모 윈도우를 지정한다. 비주얼스튜디오 IDE처럼 윈도우는 종속 관계로 만들 수 있는데, 부모 윈도우가 없는 경우 NULL을 사용한다.

> HMENU hMenu
>
> 윈도우 상단에 표시되는 메뉴의 핸들을 지정한다.

> HINSTANCE hInstance
>
> 윈도우를 생성하는 응용 프로그램의 인스턴스 핸들을 지정한다.

> LPVOID lpParam
>
> 추가 정보를 넘기기 위해 사용한다. 윈도우 프로시저에서 사용할 수 있다.

# ShowWindow() 
윈도우를 생성하면 ShowWindows(hWnd, nShowCmd)를 호출해야 화면에 표시된다. 첫 번째 인자는 윈도우 핸들이고 두 번째 인자는 화면에 보여질 옵션이다. WinMain 함수를 통해 받은 인자를 지정해준다.

UpdateWindow(hwnd)와 세트로 생각하면 된다. 윈도우의 그리는 영역을 다시 칠한다.

# MSG
윈도우 메시지 정보를 담고 있는 구조체다.

> HWND hwnd
>
> 메시지를 받은 윈도우의 핸들이다.

> UINT message
>
> 메시지 유형을 나타내는 정수다.

> WPARAM wParam
>
> 해당 메시지의 추가 정보를 가지고 있다. WORD 형으로 부호 없는 정수다.

> LPARAM lParam
>
> wParam으로 보내지 못한 추가 정보를 가지고 있다. Long 형으로 부호 있는 정수다.

> DOWRD time
>
> 이벤트 큐에 메시지가 등록된 시간이다.

> POINT pt
>
> 해당 이벤트가 발생할 당시의 마우스 위치다.

# While(GetMessage()) {}
메시지 루프라고도 부르며 응용 프로그램이 메시지를 기다리고 처리하는 데 사용한다. GetMessage 함수는 항상 TRUE를 반환하며 윈도우가 종료될 때에만 FALSE를 반환한다. 따라서 윈도우 프로그램은 이 메시지 루프에서 무한 반복 처리되는 것이다.

> LPMSG lpMsg
>
> MSG 구조체에 대한 포인터이다.

> HWND hWnd
>
> 메시지를 가져올 윈도우 핸들이다. NULL을 지정하면 윈도우 메시지와 스레드 메시지를 모두 가져울 수 있다.

> UINT wMsgFilterMin
>
> 가져올 메시지 필터의 최소값이다.

> UINT wMsgFilterMax
>
> 가져올 메시지 필터의 최대값이다. 최소값에 0, 최대값에 0을 할당하면 전체 메시지를확인한다.

# DefWindowProc()
직접 대응할 메시지를 제외한 메시지들을 기본 메시지 프로시저를 통해 대신 처리하게 한다. 기본 내장이며 거의 대부분의 메시지 처리를 대신 수행할 수 있다.

# WM_LBUTTONDOWN
마우스 이벤트 중 하나를 나타내는 윈도우 메시지로 사용자가 마우스 왼쪽 버튼을 클릭할 때 발생한다.

> wParam
>
> 키가 눌렸는지를 판단한다. 

> lParam
>
> 마우스의 위치다. lParam에 비트 연산으로 y와 x값이 앞(high-order)뒤(low-order)로 묶여서 들어온다. 32비트 환경에서 `WIRD low = ((WORD)lParam)`, `WORD high = ((WORD)((lParam >> 16) & 0xFFFF))`으로 구할 수 있다. Win API에서는 LOWORD(lParam), HIWORD(lParam)으로 정의되어 있다.

# OutputDebugString()
디버깅과 로깅 목적으로 사용되는 함수다. 디버깅 정보나 메시지를 디버그 출력 창에 출력하는 데 사용된다.