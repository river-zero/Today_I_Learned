- [C++ 표준](#c-표준)
- [C++11 언어 - 일반](#c11-언어---일반)
  - [nullptr](#nullptr)
  - [auto](#auto)
  - [초기화 리스트](#초기화-리스트)
  - [유니폼 초기화](#유니폼-초기화)
  - [범위 기반 반복문](#범위-기반-반복문)
  - [람다식](#람다식)
  - [우측값 참조와 std::move 구문](#우측값-참조와-stdmove-구문)
  - [constexpr](#constexpr)
  - [decltype](#decltype)
  - [noexcept](#noexcept)
  - [예외 복사 및 다시 던지기](#예외-복사-및-다시-던지기)
  - [인라인 이름공간](#인라인-이름공간)
  - [사용자 지정 리터럴](#사용자-지정-리터럴)
- [C++11 언어 - 클래스](#c11-언어---클래스)
  - [기본 이동 생성자 및 복사 생성자](#기본-이동-생성자-및-복사-생성자)
  - [대리 생성자](#대리-생성자)
  - [클래스 내부에서의 멤버 초기화](#클래스-내부에서의-멤버-초기화)
  - [상속 생성자](#상속-생성자)
  - [= default, = delete](#-default--delete)
  - [명시적 형변환 연산자](#명시적-형변환-연산자)
- [C++11 언어 - 타입](#c11-언어---타입)
  - [enum class](#enum-class)
  - [long long](#long-long)
- [C++11 언어 - 기타](#c11-언어---기타)
  - [반환형 접미사](#반환형-접미사)
  - [원시 문자열 리터럴](#원시-문자열-리터럴)
  - [std::static\_assert](#stdstatic_assert)
  - [메모리 정렬](#메모리-정렬)
- [C++11 언어 - 템플릿](#c11-언어---템플릿)
  - [가변 인자 템플릿](#가변-인자-템플릿)
  - [extern 템플릿](#extern-템플릿)
  - [템플릿 별명](#템플릿-별명)
  - [지역 타입 템플릿 인자](#지역-타입-템플릿-인자)
  - [\> 표기 개선](#-표기-개선)
- [C++11 STL 일반](#c11-stl-일반)
  - [std::unique\_ptr](#stdunique_ptr)
  - [std::shared\_ptr](#stdshared_ptr)
  - [std::weak\_ptr](#stdweak_ptr)
  - [std::tuple](#stdtuple)
  - [std::function과 std::bind](#stdfunction과-stdbind)
  - [정규표현식](#정규표현식)
  - [타입 특성](#타입-특성)
  - [시간 유틸리티](#시간-유틸리티)
  - [난수 생성](#난수-생성)
- [C++11 STL 컨테이너 및 알고리즘](#c11-stl-컨테이너-및-알고리즘)
  - [std::array](#stdarray)
  - [std::forward\_list](#stdforward_list)
  - [unordered\_ 계열 컨테이너](#unordered_-계열-컨테이너)
- [C++11 STL 동시성](#c11-stl-동시성)
  - [std::thread](#stdthread)
  - [상호 배제](#상호-배제)
  - [std::lock](#stdlock)
  - [std::async](#stdasync)

# C++ 표준
C++ 언어는 지금까지도 ISO(국제 표준 기구)에서 전세계의 뛰어난 프로그래머들과 전문가들이 모여 C++ 표준을 개선하고 발전시키는 데 기여하고 있다.

| 연도  |   버전    |                                                     설명                                                      |
| :---: | :-------: | :-----------------------------------------------------------------------------------------------------------: |
| 1998  |   C++98   | 최초로 정의된 표준으로 108개의 ISO 표준을 정하고 C++이 자주 사용되는 프로그래밍 언어가 될 수 있는 기초를 다짐 |
| 2003  |   C++03   |                                                거의 버그 수정                                                 |
| 2007  | TR1/C++07 |                                기술보고서로 실제로 컴파일러에 반영된 것은 아님                                |
| 2011  |   C++11   |                                              C++의 대규모 확장팩                                              |
| 2014  |   C++14   |                                               버그 수정 및 개선                                               |
| 2017  |   C++17   |                                           또 한번의 많은 기능 추가                                            |
| 2020  |   C++20   |                                              현재 논의중인 표준                                               |

C++11을 기점으로 Modern C++이라 부른다. 모든 기능을 다루지는 못하겠지만 자주 쓰거나 유용하게 쓸 법한 기능들은 아래에 기재되어 있다.
                                          
# C++11 언어 - 일반
## nullptr
포인터 변수가 어떠한 객체나 주소를 가리키지 않음을 나타낸다.

## auto
컴파일러가 컴파일 타임에 타입을 특정할 수 있을 경우 간략히 선언할 수 있도록 해당 키워드를 사용한다.

## 초기화 리스트
컴파일러가 컴파일 타임에 객체를 초기화하는 데 도움을 준다. 중괄호 `{}` 안에 초기화할 값을 나열하여 사용한다.

이 초기화 리스트의 장점은 형변환에 엄격하다는 것이다. 축소 변환을 허용하지 않기 때문에 잠재적인 버그를 줄이고 명확하고 안전한 초기화가 가능해진다. 아래는 초기화 리스트를 사용하여 함수를 호출하는 예시다.

```
void function(std::initializer_list<int>);

function({ 1, 2 });
```

## 유니폼 초기화
중괄호 `{}`를 사용해 객체를 초기화하는 일관된 문법을 제공한다. 

## 범위 기반 반복문
컨테이너나 범위 내의 요소들을 간편하게 순회하고 처리할 수 있게 해준다. `for (auto x : { 1, 2, 3, 4, 5 }) {}`과 같이 초기화식과 조합해 간단한 배열 순회도 가능하다.

## 람다식
한 번만 사용되거나 간단한 기능을 수행하는 함수를 굳이 별도로 정의하고 선언하지 않아도 되도록 한다.

```
[capture](parameters) mutable exception_specification -> return_type {
    // function body
}
```

> capture
> 
> 기본적으로 람다식은 외부의 변수에 접근이 불가능하다. [&]를 사용하면 외부 변수를 참조형으로 사용(Call by Reference)하고 [=]을 사용하면 외부 변수를 값으로 사용(Call by Value)할 수 있다. [변수1, 변수2, ...]와 같이 특정 변수만 선택하여 캡처할 수도 있다.

> parameters
> 
> 람다식에서 사용할 매개변수를 정의한다. 

> mutable
>
> 람다식 내부에서 캡처한 변수의 값을 변경할 수 있도록 허용하는 키워드이다. 기본적으로 람다식은 캡처한 변수를 읽기 전용으로 취급한다.

> exception_specification
>
> 람다식이 던질 수 있는 예외를 명시한다. throw()는 어떤 예외도 던지지 않는다는 뜻이고 noexcept 키워드는 예외가 발생하지 않음을 뜻한다.

> return_type
>
> 람다식이 값을 반환해야 할 경우 해당 반환값의 타입을 지정한다.

## 우측값 참조와 std::move 구문
우측값 참조는 주로 임시로 생성된 값이나 결과를 효율적으로 처리하는데 사용한다. `int&&`와 같이 임시로 생성된 int 값에 접근할 수 있도록 해 값의 복사 대신 이동을 통해 성능을 개선한다.

std::move는 객체의 소유권을 이동시키는 역할을 한다. 주의할 점은 std::move를 사용하고 나서는 그 객체를 다시 사용하지 말아야 한다는 것이다. 객체의 내용이 이동되어 더 이상 유효하지 않은 상태일 수 있기 때문이다.

우측값 참조를 활용해 할 수 있는 것들 중에는 아래 두 가지가 있다.

> move semantic(이동 의미 체계)
>
> 우측값 참조와 std::move를 활용해 객체의 복사 대신 이동을 수행해 성능을 개선한다. 이사를 가면서 집에서 짐을 옮기듯이 객체의 데이터를 복사하지 않고 다른 객체로 옮기는 개념이다.

```
template<class T>
void Swap(T&& a, T&& b) {
    T tmp = std::move(a);
    a = std::move(b);  
    b = std::move(tmp); 
}
```

> perfect forwarding(완벽한 전달)
>
> 함수나 생성자에 인자를 전달할 때 그 인자의 타입과 값을 그대로 유지하면서 전달하는 개념이다. 따라서 함수에 값을 넘길 때 중간에서 값이 변경되거나 변질되지 않게 보장한다.

```
void function(int&& x) {
    std::cout << x << std::endl;
}

template <typename T>
void templateFunction(T&& x) {
    function(std::forward<T>(x)); // 우측값 참조도 완벽히 전달 가능
}

int main() {
    int i = 100;

    function(i);         
    function(0);            
    function(std::move(i)); 

    std::cout << i << std::endl;
    // 이미 i가 이동되었으므로 사용은 위험
}
```

## constexpr
const(상수)가 컴파일 타임과 런타임에 결정되는 상수라면 상수 표현식(constant expression)은 컴파일 타임에 결정되는 상수다. 상수 정의 용도보다는 변수, 함수, 클래스 멤버 함수 등을 컴파일 타임에 평가하여 상수로 사용할 수 있게 해 최적화에 도움을 준다.

```
enum Flags {
    none = 0;
    slow = 1;
    paralyse = 2;
    bleed = 4;
    poison = 8;
};

constexpr int operator|(Flags f1, Flags f2) {
    return Flags(int(f1) | int(f2));
}

int main() {
    Flags myStatus{ none };
    
    switch (myStatus) {
    case none:
        break;  
    case slow | paralyse :
        break;  
    }
}
```

## decltype
특정 표현식의 결과 타입을 추론하는데 사용한다. 주로 템플릿이나 자동으로 타입을 추론해야 하는 상황에서 유용하게 활용한다.

```
#include <iostream>

template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    auto x = 1;

    decltype(x) y;         // int
    decltype(x + 1.1f) y2; // float
}
```

## noexcept
함수의 선언 또는 정의에서 사용하며 함수가 예외를 던질 가능성이 있는지 없는지를 나타낸다.

## 예외 복사 및 다시 던지기
프로그램이 실행되는 도중에 문제가 생김녀 예외가 발생한다. 때로는 예외를 잡아서 다른 곳으로 가져가야 할 때가 있는데 이런 상황을 다루기 위해 `std::current_exception()`과 `std::rethrow_exceptiron(...)`을 사용할 수 있다.

## 인라인 이름공간
이름 공간 안에 또 다른 이름 공간을 만들어 모듈화에 도움을 준다.

```
namespace outer {
    inline namespace inner {
        void f();
    }
}
```

## 사용자 지정 리터럴
프로그래머가 자신만의 리터럴 형식을 정의하여 사용할 수 있도록 한다. 단위 변환 등의 작업을 더 직관적으로 처리할 수 있다.

```
int operator""km(long double dist) {
    return static_cast<int>(dist);
}

int main() {
    int distance = 1.0km;
}
```

정수형 리터럴, 부동소수점 리터럴, 문자열 리터럴 등과 같은 특정한 종류의 리터럴에만 사용가능한 제약이 있다.

# C++11 언어 - 클래스
## 기본 이동 생성자 및 복사 생성자

## 대리 생성자

## 클래스 내부에서의 멤버 초기화

## 상속 생성자

## = default, = delete

## 명시적 형변환 연산자

# C++11 언어 - 타입
## enum class

## long long

# C++11 언어 - 기타
## 반환형 접미사

## 원시 문자열 리터럴

## std::static_assert

## 메모리 정렬

# C++11 언어 - 템플릿
## 가변 인자 템플릿

## extern 템플릿

## 템플릿 별명

## 지역 타입 템플릿 인자

## > 표기 개선

# C++11 STL 일반
## std::unique_ptr

## std::shared_ptr

## std::weak_ptr

## std::tuple

## std::function과 std::bind

## 정규표현식

## 타입 특성

## 시간 유틸리티

## 난수 생성

# C++11 STL 컨테이너 및 알고리즘
## std::array

## std::forward_list

## unordered_ 계열 컨테이너

# C++11 STL 동시성
## std::thread

## 상호 배제

## std::lock

## std::async