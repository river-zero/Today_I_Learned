- [DirectX](#directx)
- [Direct2D](#direct2d)
- [COM](#com)
- [Factory 패턴](#factory-패턴)
- [Render Target](#render-target)
- [GetMessage()](#getmessage)
- [PeekMessage()](#peekmessage)

# DirectX
종합 멀티미디어 라이브러리를 뜻한다. 그러니까, DirectX는 멀티미디어와 게임 프로그래밍에 초점을 맞춘 API의 집합이라 할 수 있다. 하드웨어에 직접 접근하므로 성능을 100% 발휘할 수 있게 해 높은 품질의 3차원 그래픽을 만들 수 있다. 내부적으로 COM 기술이 적용되었다.

가장 유명한 DirectX 버전은 DirectX 9다. 이 버전은 2002년에 출시되었으며 Windows XP 운영 체제에서 널리 사용되었다. 많은 사용자들에게 널리 보급되었고 이로 인해 게임 개발자들이 이 버전을 지원하는 게임을 개발하는 것이 중요하게 여겨졌다.

그러나 이는 옛날 버전으로 더 최신 버전인 DirectX 11로 전반적인 구조를 익히고 DirectX 12로 확장하거나 다른 게임 엔진으로 넘어가면 된다.

# Direct2D
DirectX의 일부로 2D 그래픽을 처리하는 API이다. GDI+를 대체하기 위해 도입되었다. Windows 기반 애플리케이션의 그래픽적인 부분을 효과적으로 다룰 수 있다.

# COM
상속에는 한계가 있다. 부모의 기능을 제거하거나 수정하기 어렵고, 자식 클래스를 예측하기 어렵고, 부모와 자식간의 개념이 충돌할 수 있고, 프로그래머 의존적이다. 이는 노트북에는 맞지 않는 부품을 조립할 수 없는 것과 같다. 

그러나 조립식 PC라면 구성 요소가 마음대로 추가되고 제거가 가능하다. 이러한 방식이 바로 COM(Component Object Model)이다. 객체를 이루는 컴포넌트 중심으로 먼저 각각 독립적으로 개발하고, 필요한 컴포넌트를 선택적으로 조립하여 사용할 수 있다.

COM의 인터페이스 중심 접근 방식은 상속 기반의 객체 지향 프로그래밍과 비교하여 객체 간의 느슨한 결합을 촉진하고 재사용성과 확장성을 개선할 수 있도록 도와준다. 해당 개념은 마이크로스프트에서 발표되어 현재는 언리얼 엔진, 유니티 등 널리 사용되고 있다.

# Factory 패턴
객체 지향 디자인 패턴 중 하나다. 이 패턴은 객체 생성 및 초기화 프로세스를 추상화한다. 이를 통해 클라이언트 코드가 구체적인 클래스를 직접 인스턴스화하는 대신 Factory 클래스를 사용하여 객체를 생성할 수 있도록 한다. 일종의 오브젝트를 찍어내는 공장인 것이다. 여기서 오브젝트 생성을 처리하는 오브젝트가 Factory다. 객체 생성 로직이 중앙화되므로 코드의 중복을 줄이고 객체 생성 프로세스를 일관되게 유지할 수 있다.

# Render Target
말 그대로 그릴 대상을 말한다. 이 대상은 모니터 화면 외에도 메모리나 파일 또는 다른 그래픽 표면을 말하기도 한다. 일반적으로는 그리팩 화면을 가리키며 그림을 그리고 화면에 표시하는 데 사용된다. 메모리나 파일로 설정하면 그래픽을 저장하는 데 사용할 수 있다.

D2D1::RenderTargetProperties()으로 렌더 타겟의 특성을 지정한다. D2D1_RENDER_TARGET_PROPERTIES 구조체를 사용한다.
|            구성요소            |                                                    설명                                                    |
| :----------------------------: | :--------------------------------------------------------------------------------------------------------: |
|  D2D_RENDER_TARGET_TYPE type   |                           D2D1_RENDER_TARGET_TYPE_DEFAULT : 가능하면 GPU를 사용                            |
|                                |                           D2D1_RENDER_TARGET_TYPE_SOFTWARE : CPU를 사용해 렌더링                           |
|                                |                           D2D1_RENDER_TARGET_TYPE_HARDWARE : GPU를 사용해 렌더링                           |
| D2D1_PIXEL_FORMAT pixelFormat  |                화면의 픽셀 하나가 어떤 형태인지를 지정하는 것으로 색상 및 알파를 지정 가능                 |
|           FLOAT dpiX           |                                                  가로 dpi                                                  |
|           FLOAT dpiY           |                                                  세로 dpi                                                  |
| D2D1_RENDER_TARGET_USAGE usage |                               D2D1_RENDER_TARGET_USAGE_NONE : GDI 호환 안됨                                |
|                                | D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING : BITMAP으로 내부에서 그린 후 원격 클라이언트로 보내는 용도 |
|                                |                             D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE : GDI 호환                             |
|  D2D1_FEATURE_LEVEL minLevel   |                               D2D1_FEATURE_LEVEL_DEFAULT : 특별한 제한 없음                                |
|                                |                                   D2D1_FEATURE_LEVEL_9 : DirectX 9 호환                                    |
|                                |                                  D2D1_FEATURE_LEVEL_10 : DirectX 10 호환                                   |

# GetMessage()
Windows API에서 제공되는 함수 중 하나로 Windows 메시지 큐에서 메시지를 얻는 데 사용한다. 메시지를 가져와 처리하고 메시지 큐에서 메시지를 제거한다. 메시지 큐에 대기 중인 메시지가 없을 경우에는 프로그램의 실행이 일시 중단되어 메시지가 도착할 때까지 대기한다.

# PeekMessage()
Windows API에서 사용되는 함수로 Windows 메시지 큐에서 메시지를 가져오는 함수 중 하나다. GetMessage 함수와 달리 메시지를 가져오지 않고 대신 메시지 큐의 상단에 있는 메시지를 슬쩍 확인만 한다. 따라서 메시지를 확인한 후에 선택적으로 메시지를 처리하거나 무시할 수 있다. 메시지 큐에 대기 중인 메시지를 확인하여 대기하지 않고 다른 작업을 수행하도록 해준다. 따라서 게임과 같이 빠른 처리가 필요할 경우에 사용한다.

|   구성요소    |                                    설명                                    |
| :-----------: | :------------------------------------------------------------------------: |
|     lpMsg     |                                멧지 구조체                                 |
|     hWnd      | 윈도우 핸들로 nullptr이면 모든 윈도우 메시지와 스레드의 모든 메시지를 처리 |
| wMsgFilterMin |           가져올 메시지의 시작 범위로 0이면 모든 메시지를 가져옴           |
| wMsgFilterMax |            가져올 메시지의 끝 범위로 0이면 모든 메시지를 가져옴            |
|  wRemoveMsg   |                 메시지를 어떻게 처리할 것인지에 대한 설정                  |
|               |                 PM_NOREMOVE : 처리한 후 큐에서 지우지 않음                 |
|               |                     PM_REMOVE : 처리한 후 큐에서 삭제                      |
|               |              PM_NOYIELD : 다른 스레드로 제어권을 넘기지 않음               |