- [DirectX Toolkit](#directx-toolkit)
- [NuGet](#nuget)
- [Pre-Compiled Header](#pre-compiled-header)
- [Unnamed namespace](#unnamed-namespace)
- [\_DEBUG \& NDEBUG](#_debug--ndebug)
- [D3D11CreateDevice()](#d3d11createdevice)
- [ComPtr::As()](#comptras)
- [IDXGIFactory5::CheckFeatureSupport()](#idxgifactory5checkfeaturesupport)
- [IDXGIFactory2::CreateSwapChainForHwnd()](#idxgifactory2createswapchainforhwnd)
- [IDXGIFactory::MakeWindowAssociation()](#idxgifactorymakewindowassociation)
- [IDXGIFactory1::IsCurrent()](#idxgifactory1iscurrent)
- [IDXGIFactory6::EnumAdapterByGpuPreference()](#idxgifactory6enumadapterbygpupreference)
- [IDXGIAdapter1::GetDesc1()](#idxgiadapter1getdesc1)
- [IDXGIFactory1::EnumAdapters1()](#idxgifactory1enumadapters1)
- [ComPtr::Detach()](#comptrdetach)
- [IDXGISwapChain::GetContainingOutput()](#idxgiswapchaingetcontainingoutput)
- [IDXGISwapChain3::CheckColorSpaceSupport()](#idxgiswapchain3checkcolorspacesupport)
- [IDXGISwapChain3::SetColorSpace1()](#idxgiswapchain3setcolorspace1)
- [SetWindowPos()](#setwindowpos)
- [Batching](#batching)
- [Draw Calls](#draw-calls)
- [Straight vs Premultiplied](#straight-vs-premultiplied)
- [Sprite Sheet](#sprite-sheet)
- [Texture Atlas](#texture-atlas)

# DirectX Toolkit
DirectXTK는 Microsoft가 개발한 DirectX 기반의 게임 및 그래픽 애플리케이션을 개발하기 위한 헬퍼 라이브러리다. 이 라이브러리는 DirectX를 사용하는 개발자들에게 어려운 부분과 복잡한 기능들을 단순화하고 편리하게 사용할 수 있도록 도와주는 도구와 유틸리티를 제공한다.

# NuGet
.NET 개발 환경에서 패키지 관리를 위한 오픈 소스 패키지 관리자다. NuGet을 사용하면 프로젝트에 필요한 서드파티 라이브러리, 도구, 프레임워크 등을 손쉽게 추가, 업데이트, 제거할 수 있다.

# Pre-Compiled Header
미리 컴파일된 헤더는 컴파일 속도를 향상시키는 기법 중 하나다. #include 및 inline 등의 기능은 컴파일 시 복사/붙여넣기와 비슷한 작업들이 매번 발생하게 되고 프로젝트가 커지면 커질수록 점점 더 많아진다. 미리 컴파일된 헤더는 이런 헤더들을 한 곳에 모아 한 번 컴파일 해놓고 다음 번에는 컴파일된 내용을 직접 사용하는 방식이다. 주로 시스템 헤더 및 자주 사용되지만 드물게 변경되는 프로젝트 포함 파일들을 모아 놓는다.

주의할 점은 미리 컴파일된 항목을 사용하는 경우 앞으로 작성할 모든 소스 코드는 pch.h를 포함시켜야 정상적으로 컴파일된다. 또한, pch.h의 내용을 변경하거나 pch에 포함된 헤더를 수정하게 되면 pch가 전체적으로 다시 재생성된다.

# Unnamed namespace
C++에서 이름 충돌을 방지하고 정보 은닉을 위해 사용된다. 각각의 소스 파일이 컴파일될 때 그 소스 파일 내에서만 유효한 이름 공간을 만들 수 있다.

# _DEBUG & NDEBUG
_DEBUG 매크로는 주로 디버그 빌드일 때 특정 코드 블록을 활성화하기 위해 사용한다. 

NDEBUG 매크로는 표준 라이브러리의 assert 기능을 막아주는 역할을 하는데, 디버그 모드에서 예외가 발생할 경우 aseert 경고창을 표시하고 프로그램이 종료되는데 해당 매크로가 켜져 있다면 예외는 발생하지만 프로그램이 종료되지 않는다. 주로 배포용 릴리스 구성으로 빌드할 때 사용한다.

# D3D11CreateDevice()
그래픽 디바이스를 생성하는 데 사용하는 함수다. 해당 함수를 호출하면 그래픽 애플리케이션을 개발할 수 있는 디바이스와 디바이스에 대한 컨텍스트가 만들어진다. 이를 통해 3D 그래픽 리소스를 생성하고 조작할 수 있게 된다.

# ComPtr::As()
as-a 관계를 의미한다. 호출한 인스턴스가 다형성 등의 성질로 변환될 수 있는지를 체크한다. 변환이 성공하면 S_OK를 반환하고 그렇지 않으면 에러 코드를 반환한다. 

# IDXGIFactory5::CheckFeatureSupport()
특정 기능이 현재 하드웨어에서 지원되는지 여부를 확인할 수 있다.

# IDXGIFactory2::CreateSwapChainForHwnd()
주로 윈도우 핸들을 기반으로 하는 윈도우에 대한 스왑 체인을 생성한다. 애플리케이션이 렌더링한 이미지를 화면에 표시하도록 한다.

# IDXGIFactory::MakeWindowAssociation()
보통 DXGI는 윈도우와 연관되면서 윈도우 이벤트와 그래픽 상태를 관리한다. 이 메서드는 이러한 연관성을 설정하거나 제거할 수 있도록 해준다.

# IDXGIFactory1::IsCurrent()
현재 컴퓨터의 그래픽 드라이버가 현재 DXGI 버전을 지원하는지 여부를 확인하는 데 사용한다. 주로 그래픽 드라이버 업데이트 후에 DXGI 팩토리의 상태가 변할 수 있으므로, 팩토리의 현재 상태를 확인하여 필요한 업데이트를 수행하는 데 사용된다.

# IDXGIFactory6::EnumAdapterByGpuPreference()
특정 GPU 선호도에 따라 어댑터를 열거하는 데 사용한다.

# IDXGIAdapter1::GetDesc1()
어댑터 인터페이스에서 어댑터의 세부 정보를 얻기 위해 사용한다.

# IDXGIFactory1::EnumAdapters1()
모니터가 연결된 여부와 상관없이 모든 어댑터를 열거한다.

# ComPtr::Detach()
인터페이스의 소유권을 없애고 해당 인터페이스의 포인터를 넘겨준다. 이 값을 다른 변수로 대입하면 안전하게 소유권을 이동할 수 있다.

# IDXGISwapChain::GetContainingOutput()
대상 윈도우의 클라이언트 영역이 가장 많이 존재하는 모니터를 가져온다.

# IDXGISwapChain3::CheckColorSpaceSupport()
스왑 체인이 색상 공간을 지원하는지 확인한다.

# IDXGISwapChain3::SetColorSpace1()
스왑 체인에서 사용할 색상 공간을 지정한다.

# SetWindowPos()
주로 윈도우를 이동하거나 크기를 조절할 때 또는 최상위 윈도우로 만들거나, 최상위 윈도우에서 해제할 때 사용한다.

# Batching
여러 작업을 모아서 일괄적으로 처리하는 것을 의미한다. 게임에서 여러 개의 이미지나 객체를 동시에 렌더링할 때, 배칭을 사용하여 이들을 효율적으로 처리할 수 있다.

# Draw Calls
GPU에게 화면에 그릴 그래픽 요소를 그리도록 지시하는 명령이다. 많은 드로우 콜은 성능에 부정적인 영향을 미칠 수 있으므로, 이를 최적화하기 위해 배칭 등의 기술을 사용한다.

# Straight vs Premultiplied
알파를 처리하기 위한 두 가지 방식이다. PNG를 생성하는 툴에서 결정한다.

> Straight
>
> RGBA 형태로 알파가 분리되어 저장된다. 프로그램에서 직접 알파 처리를 수행해야 한다. 외곽선이 뚜렷해지는 특징이 있다. 

> Premultiplied
>
> 이미지의 투명도 정보가 이미지의 RGB 값에 이미 합성되어 저장되는 방식이다. 외곽선이 흐릿해지는 특징이 있다. 투명하게 표현하기 위해서는 배경색 지정 등의 추가 작업이 필요하다.

# Sprite Sheet
스프라이트 시트는 여러 이미지를 한 장의 이미지로 결합한 것을 말한다. 주로 2D 게임에서 많이 사용되며, 여러 애니메이션 프레임이나 게임 오브젝트의 다양한 상태들을 하나의 이미지 파일로 효율적으로 관리할 수 있다.

# Texture Atlas
여러 작은 텍스처들을 하나의 큰 텍스처로 결합한 것을 의미한다. 이는 배칭과 함께 사용되어 여러 작은 텍스처들을 한 번에 로드하고 렌더링하여 성능을 향상시키는 데 도움이 된다. 주로 게임 엔진이나 3D 그래픽스에서 사용한다.