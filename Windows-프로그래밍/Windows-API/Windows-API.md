- [Windows API](#windows-api)
- [윈도우 클래스(WNDCLASSEX)](#윈도우-클래스wndclassex)
- [HINSTANCE](#hinstance)
- [HWND](#hwnd)
- [이벤트 메시지 시스템(Event Message System)](#이벤트-메시지-시스템event-message-system)
- [윈도우 프로시저(Window Procedure)](#윈도우-프로시저window-procedure)
- [MessageBox()](#messagebox)
- [RegisterClassEx()](#registerclassex)
- [CreateWindowEx()](#createwindowex)
- [While(GetMessage()) {}](#whilegetmessage-)
- [DefWindowProc()](#defwindowproc)
- [OutputDebugString()](#outputdebugstring)

# Windows API
Windows API는 Windows 운영 체제와 상호 작용하고 Windows 환경에서 소프트웨어를 개발하고 제어하기 위한 도구 및 명령을 제공한다. 창 관리, 파일 조작, 네트워크 설정, 그래픽 처리 및 다양한 시스템 작업을 수행할 수 있다. 

# 윈도우 클래스(WNDCLASSEX)
윈도우를 생성하고 관리하기 위한 중요한 데이터 구조 중 하나다. 윈도우 클래스를 정의하고 등록하는 데 필요하다. 다음과 같은 멤버를 포함하고 있다. EX가 붙으면 조금 더 최신 버전으로 추가 정보를 가지고 있다.

> style
>
> 윈도우 클래스의 스타일을 지정한다. 이 스타일은 윈도우의 모양과 동작을 정의한다.

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
> 윈도우의 배경색을 칠할 브러시를 지정한다. 윈도우에 대한 이벤트 및 메시지를 처리하는 데 사용한다.

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

# 윈도우 프로시저(Window Procedure)
각 윈도우 또는 컨트롤의 이벤트 처리를 담당하는 함수로 사용자와 프로그램 간에 상호 작용을 가능하게 한다.

콜백 함수는 함수를 일부러 호출하지 않아도 등록된 함수를 필요에 따라 자동적으로 호출하는 방식이다. 윈도우 프로시저도 콜백 함수의 일종이라 볼 수 있다. 이러한 방식을 이벤트 주도 개발이라고도 부른다.

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
새로운 윈도우 클래스를 등록하는 데 사용한다. 이 함수를 호출하여 윈도우 클래스를 등록하고 해당 클래스를 기반으로 윈도우를 생성한다.

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
> 윈도우의 제목을 지정한다. 

> DWORD dwStyle
>
> 윈도우의 스타일을 지정한다. 예를 들어, 윈도우의 크기 조절 가능 여부, 닫기 버튼의 유무 등을 지정할 수 있다.

> int x 및 int y
>
> 윈도우의 화면상 위치를 지정한다.

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

# While(GetMessage()) {}
메시지 루프라고도 부르며 응용 프로그램이 메시지를 기다리고 처리하는 데 사용한다. GetMessage 함수는 항상 TRUE를 반환하며 윈도우가 종료될 때에만 FALSE를 반환한다. 따라서 윈도우 프로그램은 이 메시지 루프에서 무한 반복 처리되는 것이다.

# DefWindowProc()
직접 대응할 메시지를 제외한 메시지들을 기본 메시지 프로시저를 통해 대신 처리하게 한다. 기본 내장이며 거의 대부분의 메시지 처리를 대신 수행할 수 있다.

# OutputDebugString()
디버깅과 로깅 목적으로 사용되는 함수다. 디버깅 정보나 메시지를 디버그 출력 창에 출력하는 데 사용된다.