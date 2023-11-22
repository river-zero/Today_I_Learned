- [Windows Imaging Component](#windows-imaging-component)
- [COM Initialize](#com-initialize)
- [WIC Decoder](#wic-decoder)
- [WIC Frame](#wic-frame)
- [WIC Converter](#wic-converter)

# Windows Imaging Component
통칭 WIC는 디지털 이미지 처리를 위한 Microsoft의 저수준 API이다. 이 API는 이미지 형식에 대한 독립적인 코드를 작성할 수 있게 해주며 JPEG, TIFF, PNG, GIF, BMP 등 다양한 이미지 형식을 지원한다다. 또한, 메타데이터 처리, 고해상도 이미지 처리, 픽셀 형식 변환 등의 기능도 제공한다. 이를 통해 개발자들은 이미지 처리와 관련된 다양한 작업을 보다 효율적으로 수행할 수 있다.

# COM Initialize
WIC는 윈도우 전용이므로 순혈 COM을 적용하기 위해 꼭 필요하다. COM을 사용하기 위해서는 먼저 COM 라이브러리를 초기화해야 한다. 이를 위해 CoInitialize 또는 CoInitializeEx 함수를 호출하고, WIC의 다양한 기능을 사용할 수 있게 된다.

# WIC Decoder
디코딩은 이미지 파일이나 다른 형태의 이미지 데이터를 읽어들여서 컴퓨터에서 이해할 수 있는 형태로 변환하는 작업이다. JPG, PNG, GIF와 같은 형식의 규칙에 따라 데이터를 해석하고 원본 이미지로 복원하는 과정을 포함한다.

WIC Decoder는 Microsoft Windows 플랫폼에서 이미지를 디코딩하기 위한 컴포넌트 중 하나다. JPG, PNG, GIF, BMP, TIFF 등 다양한 포맷의 이미지를 디코딩할 수 있다. 

# WIC Frame
Frame은 이미지나 비트맵 데이터를 나타내는 단위다. WIC에서는 이미지를 여러 프레임으로 나누어 처리할 수 있다. 각 프레임은 일반적으로 복합 이미지에 대한 한 부분이나 하위 이미지를 나타낸다. 예를 들어, GIF 이미지는 여러 프레임으로 구성된 애니메이션을 표현할 수 있다. 

WIC Frame은 주로 IWICBitmapFrameDecode 인터페이스를 통해 다룰 수 있다. 이 인터페이스는 개별 이미지 프레임에 대한 디코딩과 관련된 작업을 수행할 수 있는 메서드를 제공한다.

# WIC Converter
이미지 형식을 변환하는 데 사용되는 컴포넌트다. 다양한 이미지 형식 간에 변환을 수행하거나, 특정 형식의 이미지를 다른 형식으로 바꾸는 데 사용된다.

WIC Converter는 IWICFormatConverter 인터페이스를 통해 제공된다. 이 인터페이스는 이미지 형식을 변환하고, 디코딩된 이미지를 원하는 형식으로 적절하게 변환할 수 있도록 하는 메서드를 제공한다.