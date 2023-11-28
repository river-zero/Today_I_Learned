- [define WIN32\_LEAN\_AND\_MEAN](#define-win32_lean_and_mean)
- [SetForegroundWindow()](#setforegroundwindow)
- [SetFocous()](#setfocous)
- [IDXGISwapChain](#idxgiswapchain)
- [ID3D11Device](#id3d11device)
- [ID3D11DeviceContext](#id3d11devicecontext)
- [DXGI\_SWAP\_CHAIN\_DESC](#dxgi_swap_chain_desc)
- [DXGI\_MODE\_DESC](#dxgi_mode_desc)
- [D3D11CreateDeviceAndSwapChain()](#d3d11createdeviceandswapchain)
- [Resource \& Resource View](#resource--resource-view)
- [ID3D11Texture2D](#id3d11texture2d)
- [ID3D11RenderTargetView](#id3d11rendertargetview)
- [ID3D11DepthStencilView](#id3d11depthstencilview)
- [IDXGISwapChain::GetBuffer()](#idxgiswapchaingetbuffer)
- [ID3D11Device::CreateRenderTargetView()](#id3d11devicecreaterendertargetview)
- [D3D11\_TEXTURE2D\_DESC](#d3d11_texture2d_desc)
- [ID3D11Device::CreateTexture2D()](#id3d11devicecreatetexture2d)
- [ID3D11Device::CreateDepthStencilView()](#id3d11devicecreatedepthstencilview)
- [ID3D11DeviceContext::OMSetRenderTargets()](#id3d11devicecontextomsetrendertargets)
- [ID3D11DeviceContext::RSSetViewports()](#id3d11devicecontextrssetviewports)
- [ID3D11DeviceContext::ClearRenderTargetView()](#id3d11devicecontextclearrendertargetview)
- [ID3D11DeviceContext::ClearDepthStencilView()](#id3d11devicecontextcleardepthstencilview)
- [IDXGISwapChain::Present()](#idxgiswapchainpresent)
- [IDXGISwapChain::SetFullscreenState()](#idxgiswapchainsetfullscreenstate)
- [ID3D11DeviceContext::Flush()](#id3d11devicecontextflush)
- [IDXGISwapChain::ResizeBuffers()](#idxgiswapchainresizebuffers)
- [WM\_SIZE](#wm_size)
- [WM\_ENTERSIZEMOVE](#wm_entersizemove)
- [WM\_EXITSIZEMOVE](#wm_exitsizemove)
- [WM\_MENUCHAR](#wm_menuchar)
- [WM\_GETMINMAXINFO](#wm_getminmaxinfo)
- [ID3D11Device::CreateBuffer()](#id3d11devicecreatebuffer)
- [ID3D11DeviceConstext::Map()](#id3d11deviceconstextmap)
- [D3DCompileFromFile()](#d3dcompilefromfile)
- [ID3D11Device::CreateVertexShader()](#id3d11devicecreatevertexshader)
- [ID3D11Device::CreatePixelShader()](#id3d11devicecreatepixelshader)
- [ID3D11DeviceConstext::VSSetShader()](#id3d11deviceconstextvssetshader)
- [ID3D11DeviceCont4xt::PSSetShader()](#id3d11devicecont4xtpssetshader)
- [D3D11\_INPUT\_ELEMENT\_DESC](#d3d11_input_element_desc)
- [ID3D11Device::CreateInputLayout()](#id3d11devicecreateinputlayout)
- [ID3D11DeviceContext::IASetInputLayout()](#id3d11devicecontextiasetinputlayout)
- [ID3D11DeviceContext::IASetVertexBuffer()](#id3d11devicecontextiasetvertexbuffer)
- [ID3D11DeviceContext::IASetPrimitiveTopology()](#id3d11devicecontextiasetprimitivetopology)
- [ID3D11DeviceContext::Draw()](#id3d11devicecontextdraw)
- [윈도우 생성 과정 정리](#윈도우-생성-과정-정리)
- [Direct3D 생성 및 그리기 과정 정리](#direct3d-생성-및-그리기-과정-정리)
- [파이프 라인과 셰이더 과정 정리](#파이프-라인과-셰이더-과정-정리)

# define WIN32_LEAN_AND_MEAN
Windows.h 헤더 파일을 포함할 때 일부 추가 기능을 비활성화하여 컴파일 시간을 단축한다.

# SetForegroundWindow()
지정된 창을 사용자의 화면에서 가장 앞으로 가져오고 활성화한다.

# SetFocous()
특정 윈도우나 컨트롤에 입력 포커스를 설정하는 데 사용한다. 창은 띄워졌는데 입력은 엉뚱한 곳에서 되는 일들을 방지한다.

# IDXGISwapChain
프론트 버퍼와 백 버퍼를 교환하여 사용자가 렌더링된 이미지를 볼 수 있다. 이 과정을 스왑이라고 한다. 스왑 체인은 버퍼들의 모음으로 이런 스왑을 관리하고 부드러운 애니메이션 및 렌더링을 가능하게 한다.

# ID3D11Device
주로 디바이스를 제어하고 관리하는 데 사용한다. 여기서 디바이스는 그래픽 카드를 말한다.

# ID3D11DeviceContext
이 인터페이스는 ID3D11Device와 함께 사용되며, 그래픽 리소스를 렌더링하는 데 필요한 다양한 작업을 수행하는 데 도움을 준다.

# DXGI_SWAP_CHAIN_DESC
스왑 체인을 생성하기 위한 설정을 담은 구조체다. 

|        형식        |      변수      |                                               설명                                                |
| :----------------: | :------------: | :-----------------------------------------------------------------------------------------------: |
|  `DXGI_MODE_DESC`  |  `BufferDesc`  |                                 백 버퍼의 모드를 지정하는 구조체                                  |
|                    |                |                  다양한 속성을 가지며 너비, 높이, 픽셀 형식 및 주사율 등을 설정                   |
| `DXGI_SAMPLE_DESC` |  `SampleDesc`  |            멀티샘플링을 지원하는 경우 각 픽셀에 적용되는 샘플의 수와 품질 수준을 지정             |
|                    |                |                           `Count`는 샘플의 수를, `Quality`는 품질 수준                            |
|                    |                |                           MSAA를 끄려면 Count를 1, Quality를 0으로 지정                           |
|                    |                |                        이때, 렌더 타겟과 깊이 버퍼는 동일한 설정이어야 함                         |
|    `DXGI_USAGE`    | `BufferUsage`  |                                    백 버퍼의 사용 방법을 지정                                     |
|                    |                |              주로 `DXGI_USAGE_RENDER_TARGET_OUTPUT`으로 설정하여 렌더 타겟으로 사용               |
|       `UINT`       | `BufferCount`  |                            스왑 체인에서 사용할 백 버퍼의 개수를 지정                             |
|                    |                |                  대부분은 1로 설정되며, 더블 버퍼링을 사용하는 경우에는 2로 설정                  |
|       `HWND`       | `OutputWindow` |                               스왑 체인이 출력되는 창의 핸들을 지정                               |
|       `BOOL`       |   `Windowed`   |                                       창 모드 여부를 나타냄                                       |
|                    |                |                   `TRUE`로 설정하면 창 모드, `FALSE`로 설정하면 전체 화면 모드                    |
| `DXGI_SWAP_EFFECT` |  `SwapEffect`  |                                   스왑 체인의 스왑 효과를 지정                                    |
|                    |                | 주로 `DXGI_SWAP_EFFECT_DISCARD`가 사용되며, 백 버퍼를 폐기하고 새로 생성하는 방식으로 스왑을 수행 |
|       `UINT`       |    `Flags`     |                    스왑 체인을 생성하는 동안 적용할 특별한 옵션 플래그를 지정                     |
|                    |                |                                       일반적으로 0으로 설정                                       |

# DXGI_MODE_DESC
DXGI_SWAP_CHAIN_DESC 구조체의 멤버로 활용된다. 디스플레이 모드에 대한 정보를 저장하는 구조체다.

|            형식            |        변수        |                                설명                                |
| :------------------------: | :----------------: | :----------------------------------------------------------------: |
|           `UINT`           |      `Width`       |                         해상도의 가로 크기                         |
|                            |                    | 0으로 지정하면 실행 시간에 출력 윈도우의 가로 크기를 구해와서 지정 |
|           `UINT`           |      `Height`      |                         해상도의 세로 크기                         |
|                            |                    | 0으로 지정하면 실행 시간에 출력 윈도우의 세로 크기를 구해와서 지정 |
|      `DXGI_RATIONAL`       |   `RefreshRate`    |                    갱신율을 헬르츠 단위로 지정                     |
|                            |                    |                         분자와 분모로 구성                         |
|                            |                    |   60Hz는 초당 60번이므로 Numerator는 60, Denominator는 1로 지정    |
|       `DXGI_FORMAT`        |      `Format`      |                          픽셀 형식을 지정                          |
|                            |                    | 자주 사용하는 형태는 DXGI_FORMAT_R8G8B8A8_UNORM의 32비트 색상 포멧 |
| `DXGI_MODE_SCANLINE_ORDER` | `ScanlineOrdering` |                     스캔 라인 정렬 방식을 지정                     |
|    `DXGI_MODE_SCALING`     |     `Scaling`      |                        스케일링 정보를 지정                        |


# D3D11CreateDeviceAndSwapChain()
Direct3D 11 디바이스와 스왑 체인을 생성한다. HRESULT를 반환한다.

|             형식              |         변수         |                                                     설명                                                     |
| :---------------------------: | :------------------: | :----------------------------------------------------------------------------------------------------------: |
|        `IDXGIAdapter*`        |      `pAdapter`      |                사용할 그래픽 어댑터를 나타내는 포인터로 `NULL`을 전달하면 기본 어댑터를 사용                 |
|       `D3D_DRIVER_TYPE`       |     `DriverType`     | 사용할 드라이버 타입을 나타내는 열거형으로 주로 `D3D_DRIVER_TYPE_HARDWARE`를 사용하여 하드웨어 가속을 활성화 |
|           `HMODULE`           |      `Software`      |                  렌더링에 사용할 소프트웨어 드라이버 모듈의 핸들로 일반적으로 `NULL`을 사용                  |
|            `UINT`             |       `Flags`        |                             Direct3D를 어떻게 실행할 것인지에 대한 플래그를 지정                             |
|  `const D3D_FEATURE_LEVEL*`   |   `pFeatureLevels`   |       지원하는 Direct3D 기능 레벨의 배열을 나타내는 포인터로 Direct3D 11을 사용할 경우 그냥 0으로 지정       |
|            `UINT`             |   `FeatureLevels`    |                          배열의 길이로 pFeatureLevels에서 0이라면 여기도 0으로 지정                          |
|            `UINT`             |     `SDKVersion`     |                                          사용할 Direct3D SDK의 버전                                          |
| `const DXGI_SWAP_CHAIN_DESC*` |   `pSwapChainDesc`   |                       스왑 체인을 생성하는 데 필요한 설정을 담고 있는 구조체의 포인터                        |
|      `IDXGISwapChain**`       |    `ppSwapChain`     |                            생성된 스왑 체인에 대한 포인터가 저장될 변수의 포인터                             |
|       `ID3D11Device**`        |      `ppDevice`      |                             생성된 디바이스에 대한 포인터가 저장될 변수의 포인터                             |
|     `D3D_FEATURE_LEVEL*`      |   `pFeatureLevel`    |                              생성된 디바이스의 기능 레벨이 저장될 변수의 포인터                              |
|    `ID3D11DeviceContext**`    | `ppImmediateContext` |                        생성된 디바이스 컨텍스트에 대한 포인터가 저장될 변수의 포인터                         |

# Resource & Resource View
쉽게 말하면 리소스는 데이터 묶음이고 리소스 뷰는 그 데이터 묶음에 대한 설명서다. 리소스는 단순한 메모리의 집합으로 다양한 곳에서 쓸 수 있도록 ID3D11Texture2D와 같이 범용적인 형태가 되어야 한다. 하지만 동일한 텍스처 데이터를 각각 Render Target, Depth Stencil로 사용하고자 한다면 데이터를 해석(형변환과도 같음)할 필요가 있다.

# ID3D11Texture2D
ID3D11Resource 인터페이스를 상속하며, 2D 이미지 데이터를 저장하고 해당 데이터에 대한 접근을 제공한다. 2차원 텍스처는 비트맵과 같은 구조다.

# ID3D11RenderTargetView
렌더 타겟에 대한 뷰를 만들어 그에 대한 그래픽 작업을 수행할 수 있도록 하는 인터페이스다. 예를 들어, 화면에 렌더링된 결과를 텍스처로 저장하거나, 후처리 효과를 적용하고자 할 때 사용한다.

# ID3D11DepthStencilView
깊이 스텐실 버퍼에 대한 뷰를 만들어 깊이 정보 및 스텐실 정보에 대한 그래픽 작업을 수행할 수 있게 하는 인터페이스다. 예를 들어, 깊이 정보를 사용하여 렌더링된 객체의 순서를 정렬하거나, 그림자 매핑을 구현하는 등의 작업에서 사용될 수 있다.

# IDXGISwapChain::GetBuffer()
스왑 체인에서 백 버퍼를 가져온다. 이 함수를 사용하여 백 버퍼에 접근하면, 해당 백 버퍼에 대한 렌더링을 수행하고 IDXGISwapChain::Present를 호출하여 프론트 버퍼로 스왑하여 결과를 화면에 표시할 수 있다.

|  형식  |   변수    |               설명                |
| :----: | :-------: | :-------------------------------: |
|  UINT  |  Buffer   |       버퍼 인덱스로 0 기준        |
| REFIID |   riid    |         인터페이스의 타입         |
| void** | ppSurface | 버퍼로 사용될 인터페이스의 포인터 |

# ID3D11Device::CreateRenderTargetView()
렌더 타겟 뷰를 생성한다. 

|                  형식                  |    변수     |                                설명                                |
| :------------------------------------: | :---------: | :----------------------------------------------------------------: |
|           `ID3D11Texture2D*`           | `pResource` |                      렌더 타겟에 대한 포인터                       |
|                                        |             | 해당 리소스는 D3D11_BIND_RENDER_TARGET 플래그가 설정되어 있어야 함 |
| `const D3D11_RENDER_TARGET_VIEW_DESC*` |   `pDesc`   |           렌더 타겟 뷰의 속성을 지정하는 구조체의 포인터           |
|                                        |             | NULL을 지정하면 밉맵 레벨 0의 모든 리소스에 접근 가능한 뷰가 생성  |
|       `ID3D11RenderTargetView**`       | `ppRTView`  |            생성된 렌더 타겟 뷰 인터페이스에 대한 포인터            |

# D3D11_TEXTURE2D_DESC
2D 텍스처를 설명하는 구조체다. ID3D11Device::CreateTexture2D 함수의 매개변수로 사용된다.

|        형식        |       변수       |                                    설명                                    |
| :----------------: | :--------------: | :------------------------------------------------------------------------: |
|       `UINT`       |     `Width`      |             텍스처의 텍셀 너비 값으로 1 ~ 16384까지 지정 가능              |
|       `UINT`       |     `Height`     |             텍스처의 텍셀 세로 값으로 1 ~ 16384까지 지정 가능              |
|       `UINT`       |   `MipLevels`    |  Mipmap 레벨 수를 나타내는 값으로 0으로 지정하면 모든 단계의 맵맵을 생성   |
|       `UINT`       |   `ArraySize`    |            텍스처 배열의 크기를 지정하며 1 ~ 2048까지 지정 가능            |
|   `DXGI_FORMAT`    |     `Format`     |                             텍셀의 포멧을 지정                             |
| `DXGI_SAMPLE_DESC` |   `SampleDesc`   |                            MSAA 파라미터를 지정                            |
|   `D3D11_USAGE`    |     `Usage`      |                   텍스처 데이터를 읽고 쓰는 권한을 지정                    |
|                    |                  |            기본값은 D3D11_USAGE_DEFAULT로 GPU만 읽고 쓰기 가능             |
|       `UINT`       |   `BindFlags`    |                       어떤 용도로 바인딩 될지를 지정                       |
|       `UINT`       | `CPUAccessFlags` | CPU에서 읽고 쓸 수 있는지를 지정하며 기본값 0은 CPU의 접근을 허용하지 않음 |
|       `UINT`       |   `MiscFlags`    |                  다른 속성에 영향을 주는 여러 가지 플래그                  |

여기서 앞에 C가 붙은 CD3D11_TEXTURE2D_DESC은 클래스처럼 동작하게 만들어주는 헬퍼다. 생성자를 사용이 가능하며 기본값이 할당되어 있어서 편리하게 구조체를 사용할 수 있다. 대부분의 DirectX 구조체는 헬퍼가 준비되어 있으므로 이를 사용하자.

# ID3D11Device::CreateTexture2D()
2D 텍스처를 생성한다.

|              형식               |      변수      |                         설명                         |
| :-----------------------------: | :------------: | :--------------------------------------------------: |
|  `const D3D11_TEXTURE2D_DESC*`  |    `pDesc`     |         텍스처의 설정을 넘겨줄 구조체 포인터         |
| `const D3D11_SUBRESOURCE_DATA*` | `pInitialData` | 초기값을 지정하며 보통 NULL로 성정해 초기화하지 않음 |
|       `ID3D11Texture2D**`       | `ppTexture2D`  |        생성된 텍스처 인터페이스에 대한 포인터        |

# ID3D11Device::CreateDepthStencilView()
깊이 스텐실 뷰를 생성한다.

|                  형식                  |         변수         |                           설명                           |
| :------------------------------------: | :------------------: | :------------------------------------------------------: |
|           `ID3D11Resource*`            |     `pResource`      | 깊이 스텐실 뷰를 생성할 깊이 스텐실 텍스처에 대한 포인터 |
| `const D3D11_DEPTH_STENCIL_VIEW_DESC*` |       `pDesc`        |  깊이 스텐실 뷰의 속성을 지정하는 구조체에 대한 포인터   |
|       `ID3D11DepthStencilView**`       | `ppDepthStencilView` |         생성된 깊이 스텐실 뷰 인터페이스 포인터          |

# ID3D11DeviceContext::OMSetRenderTargets()
렌더 타겟과 깊이 스텐실 버퍼를 바인딩한다. 

|              형식               |         변수          |                                         설명                                         |
| :-----------------------------: | :-------------------: | :----------------------------------------------------------------------------------: |
|             `UINT`              |      `NumViews`       | 렌더 타겟의 개수로 여러개라면 여기에 해당 개수를 넣고 다음 인자에 배열을 넘겨주면 됨 |
| `ID3D11RenderTargetView*const*` | `ppRenderTargetViews` |        렌더 타겟 뷰 배열에 대한 포인터로 1개라면 단순히 해당 뷰의 **를 넘겨줌        |
|    `ID3D11DepthStencilView*`    |  `pDepthStencilView`  |                               깊이 스텐실 뷰의 포인터                                |

# ID3D11DeviceContext::RSSetViewports()
뷰포트를 바인딩합니다. 여기서 RS는 Rasterizer Stage다.

|          형식           |      변수      |                             설명                              |
| :---------------------: | :------------: | :-----------------------------------------------------------: |
|         `UINT`          | `NumBiewports` |                     뷰포트의 개수를 지정                      |
| `const D3D11_VIEWPORT*` |  `pViewports`  |                 뷰포트의 배열 포인터를 넘겨줌                 |
|                         |                | 하나의 뷰포트만 사용하면 뷰포트 구조체의 포인터만 넘겨줘도 됨 |

# ID3D11DeviceContext::ClearRenderTargetView()
렌더 타겟을 지정된 색상을 지운다.

# ID3D11DeviceContext::ClearDepthStencilView()
깊이 스텐실 리소스를 지정된 깊이 값과 스텐실 값으로 지운다.

|           형식            |        변수         |                        설명                         |
| :-----------------------: | :-----------------: | :-------------------------------------------------: |
| `ID3D11DepthStencilView*` | `pDepthStencilView` |        지울 깊이 스텐실 뷰 인터페이스 포인터        |
|          `UINT`           |    `ClearFlags`     |              어떤 리소스를 지울지 지정              |
|          `FLOAT`          |       `Depth`       | 클리어할 깊이 값으로 0.0f에서 1.0f 사이의 값을 가짐 |
|          `UINT8`          |      `Stencil`      |                 클리어할 스텐실 값                  |

# IDXGISwapChain::Present()
백 버퍼와 프론트 버퍼를 교환하여 렌더링된 이미지를 보여준다.

|  형식  |      변수      |                          설명                          |
| :----: | :------------: | :----------------------------------------------------: |
| `UINT` | `SyncInterval` | 수직 동기화의 간격을 지정하는데 0이면 즉히 화면에 표시 |
| `UINT` |    `Flags`     |                프레젠테이션 옵션을 지정                |

# IDXGISwapChain::SetFullscreenState()
전체화면 모드 <-> 창 모드로 전환하고자 할 때 사용한다. TRUE이면 전체화면 모드로 전환되고, FALSE로 설정하면 창 모드로 전환된다. 이때, 비정상 종료가 발생할 가능성이 있으므로 게임 종료 시에는 반드시 전체화면 모드를 해제해야 한다.

# ID3D11DeviceContext::Flush()
현재 그래픽 명령 대기열에서 대기 중인 명령을 즉시 실행하도록 강제한다.

# IDXGISwapChain::ResizeBuffers()
백 버퍼의 크기를 조정하는 데 사용한다.

|     형식      |       변수       |                                     설명                                      |
| :-----------: | :--------------: | :---------------------------------------------------------------------------: |
|    :`UINT`    |  `BufferCount`   | 프론트 버퍼와 모든 백 버퍼의 총 개수로 0으로 지정하면 기존 버퍼 개수를 유지함 |
|    `UINT`     |     `Width`      |                              백 버퍼의 가로 크기                              |
|    `UINT`     |     `Height`     |                              백 버퍼의 세로 크기                              |
| `DXGI_FORMAT` |   `NewFormat`    |    변경할 포멧을 지정하며 SCGI_FORMAT_UNKNOWN으로 설정하면 기존 포멧 유지     |
|    `UINT`     | `SwapChainFlags` |                    스왑 체인의 추가 옵션으로 따로 없다면 0                    |

# WM_SIZE
윈도우의 크기가 변경될 때 발생하는 윈도우 메시지다. 사이즈 변경에는 다음과 같은 특이 사항이 있는데 이 정보가 wParam으로 전달된다.

- SIZE_MINIMIZED : 최소화 되어 트레이로 내려감
- SIZE_MAXIMIZED : 최대화 됨
- SIZE_RESTORED : 최소화나 최대화가 아닌 상태에서 윈도우 크기가 변경됨

# WM_ENTERSIZEMOVE
윈도우 테두리를 드래그해서 사이즈를 조절하려고 할 때 한 번 발생한다.

# WM_EXITSIZEMOVE
사용자가 윈도우 테두리를 놓으면 한 번 발생한다. 이때가 실제로 변경할 윈도우 사이즈가 정해지는 시점이다.

# WM_MENUCHAR
메뉴의 단축키가 눌렸는지를 확인하는 윈도우 메시지다. 여기서는 전체화면 모드에서 창 모드로 전환 시에 들리는 경고음을 없애기 위해 사용한다.

# WM_GETMINMAXINFO
윈도우 사이즈나 위치가 변경되기 직전에 전달되는 윈도우 메시지다. 윈도우가 너무 크거나 작아지지 않도록 예외 처리를 할 수 있다. lParam에 MINMAXINFO 구조체의 포인터가 넘어오는데, 이 구조체의 멤버를 변경해주면 윈도우 기본값을 원하는 값으로 변경이 가능하다.

# ID3D11Device::CreateBuffer()
CD3D11_BUFFER_DESC에서 생성한 버퍼 설명으로 버퍼를 생성한다.

|              형식               |      변수      |                                                        설명                                                         |
| :-----------------------------: | :------------: | :-----------------------------------------------------------------------------------------------------------------: |
|   `const D3D11_BUFFER_DESC*`    |    `pDesc`     |                                        버퍼를 설명하는 구조체에 대한 포인터                                         |
| `const D3D11_SUBRESOURCE_DATA*` | `pInitialData` | 초기 데이터를 저장한 구조체 포인터로 NULL을 넘기면 미정 상태로 남게 되며 사용하기 전에 직접 데이터를 채워 넣어야 함 |
|        `ID3D11Buffer**`         |   `ppBuffer`   |                                           생성한 버퍼 인터페이스의 포인터                                           |

# ID3D11DeviceConstext::Map()
CPU가 값을 쓰고 GPU가 읽어간다고 하였는데 이 과정이 서로 맞지 않으면 값을 쓰는 도중 GPU가 읽어갈 수도 있다. 그러면 이상한 결과가 나온다. 이를 막기 위해서 Map과 Unmap을 사용한다.  CPU에서 GPU 리소스에 직접 접근할 때, GPU가 해당 리소스에 접근하는 것을 방지한다. 그리고 값을 다 쓰고 나면 GPU가 가져갈 수 있도록 Unmap을 한다. 복잡하지만 이런 방식의 설계를 통해 GPU/CPU를 분리해 더욱 안전하게 하드웨어 가속을 처리할 수 있다. 버퍼에 접근할 때는 해당 버퍼가 GPU가 사용하는지를 확인하고 Map/Unmap을 수행한다고 생각하면 된다.

# D3DCompileFromFile()
파일에서 HLSL 코드를 읽어들이고 해당 코드를 컴파일하여 셰이더 바이트 코드를 생성한다.

# ID3D11Device::CreateVertexShader()
버텍스 셰이더를 생성하는 데 사용한다. 생성된 정점 셰이더는 ID3D11VertexShader 인터페이스를 통해 조작된다.

# ID3D11Device::CreatePixelShader()
픽셀 셰이더를 생성하는 데 사용한다. 생성된 픽셀 셰이더는 ID3D11PixelShader 인터페이스를 통해 조작된다.

# ID3D11DeviceConstext::VSSetShader()
파이프 라인에서 버텍스 셰이더 스테이지에 사용할 정점 셰이더를 지정한다.

# ID3D11DeviceCont4xt::PSSetShader()
파이프 라인에서 픽셀 셰이더 스테이지에 사용할 픽셀 셰이더를 지정한다.

# D3D11_INPUT_ELEMENT_DESC
Input-Assenber 스테이지의 입력 값(버텍스 셰이더라면 버텍스, 픽셀 셰이더라면 픽셀) 하나가 어떤 식으로 되어 있는가를 지정한다.

```
typedef struct D3D11_INPUT_ELEMENT_DESC {
  LPCSTR                     SemanticName;         // 의미론적 이름
  UINT                       SemanticIndex;        // 의미론적 인덱스
  DXGI_FORMAT                Format;               // 데이터 형식
  UINT                       InputSlot;            // 입력 슬롯 인덱스
  UINT                       AlignedByteOffset;    // 바이트 오프셋
  D3D11_INPUT_CLASSIFICATION InputSlotClass;       // 입력 슬롯 분류
  UINT                       InstanceDataStepRate; // 인스턴스당 스텝 비율
} D3D11_INPUT_ELEMENT_DESC;
```

# ID3D11Device::CreateInputLayout()
D3D11_INPUT_ELEMENT_DESC 구조체 정보들로 입력 레이아웃을 만든다. 주로 정점 셰이더에 대한 정보만으로 충분하며, 픽셀 셰이더에 대한 정보는 해당 셰이더를 사용할 때 자동으로 처리된다.

# ID3D11DeviceContext::IASetInputLayout()
Input-Assenbler에 입력 레이아웃을 연결(bind)한다.

# ID3D11DeviceContext::IASetVertexBuffer()
Input-Assenbler에 버텍스 버퍼를 연결한다. GPU는 이 버텍스 버퍼를 읽기 시작한다. 버텍스 버퍼를 연결해 줄때는 stride와 offset이 필요하다. Vn = offset + (n - 1) * stride와 같이 1차원 버퍼에 접근하는 방식이다.

# ID3D11DeviceContext::IASetPrimitiveTopology()
Primitive 유형을 설정한다. 그래픽 파이프라인에서 입력 조립 단계는 정점 데이터를 기본 프리미티브로 조립하고, 이를 래스터화(Rasterization) 단계로 전달한다.

# ID3D11DeviceContext::Draw()
실제로 화면에 그리는 함수다. 삼각형 그리기 프로그램을 실행해보면 그라데이션이 보인다. 이는 디바이스가 삼각형을 그릴 때 각 꼭짓점의 색상에 대한 거리를 보간해서 삼각형 내부를 그리기 때문이다.

# 윈도우 생성 과정 정리
1. WNDCLASSEX 구조체에 정보 설정
2. RegisterClass(&wc)로 클래스 등록
3. CreateWindow("class name")으로 해당 클래스에서 윈도우 생성
4. ShowWindow()로 화면에 표시
5. 윈도우 프로시저로 메시지 처리

# Direct3D 생성 및 그리기 과정 정리
1. 스왑 체인 정보 구조체 설정
2. D3D11CreateDeviceAndSwapChain으로 스왑 체인, 디바이스, 디바이스 컨텍스트 생성
3. 후면 버퍼를 얻어와서 렌더 타겟 뷰 생성
4. 깊이 스텐실 버퍼용 텍스처2D 생성
5. 깊이 스텐실 버퍼로부터 깊이 스텐실 뷰 생성
6. 3번, 5번의 뷰를 이용해 렌더 타겟 지정
7. 뷰포트 지정
8. 후면 버퍼 클리어
9. 깊이 스텐실 버퍼 클리어
10. 겡미에서 사용할 그리기 루틴
11. 스왑 체인의 Present()

# 파이프 라인과 셰이더 과정 정리
1. 셰이더 컴파일
2. 버텍스 셰이더, 픽셀 셰이더 생성
3. 입력 레이아웃 구조 바인딩
4. 버텍스 버퍼 생성(Map/Unmap)
5. 그리기

지금까지 작업한 Device와 Device Context에서 사용한 함수를 따로 뽑으면 아래와 같다. 디바이스는 버퍼/텍스처 등의 리소스를 만들고 리소스에 접근하는 뷰를 만든다. 디바이스 컨텍스트는 파이프 라인을 설정하거나 실제로 화면에 그린다.

Device
- CreateBuffer
- CreateVertexShader
- CreatePixelShader
- CreateInputLayout
- CreateRenderTargetView
- CreateTexture2D
- CreateDpthStencilView

Device Context
- Map, Unmap
- VSSetShader, PSSetShader
- IASetInputLayout
- ClearRenderTargetView
- ClearDepthStencilView
- IASetVertexBuffers
- IASetPrimitiveTopology
- Draw
- OMSetRenderTargets
- RSSetViewports