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
  - [override \& final](#override--final)
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
auto Add(T1 a, T2 b) -> decltype(a + b) {
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
프로그램이 실행되는 도중에 문제가 생기면 예외가 발생한다. 때로는 예외를 잡아서 다른 곳으로 가져가야 할 때가 있는데 이런 상황을 다루기 위해 `std::current_exception()`과 `std::rethrow_exceptiron(...)`을 사용할 수 있다.

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
우측값 참조 개념이 도입되면서 추가되었다. 이동 생성자는 임시 객체나 rvalue의 내용을 이동하여 새로운 객체를 생성하는 역할을 한다. 복사 생성자는 같은 클래스의 다른 객체를 복사하여 새로운 객체를 생성하는 역할을 한다.

```
MyClass(const MyClass&)            // 복사 생성자
MyClass& operator=(const MyClass&) // 복사 대입 연산자
MyClass(MyClass&&);                // 이동 생성자
MyClass& operator=(MyClass&&)      // 이동 대입 연산자
```

```
Dog dog1;               // 기본 생성자
Dog dog2 = dog1;        // 복사 생성자
Dog dog3 = Dog();       // 이동 생성자
Dog dog4 = dog1 + dog2; // 이동 생성자
```

Dog 클래스에 `+` 연산자가 정의되어 있으면 연산의 결과로 객체가 반환된다. 이 객체는 rvalue가 되며 이동이 일어나게 된다.

|  멤버함수   |                 컴파일러 자동 생성                 |        내용        |
| :---------: | :------------------------------------------------: | :----------------: |
| 기본 생성자 |             생성자가 하나도 없는 경우              | 아무것도 하지 않음 |
|   소멸자    |                 소멸자가 없는 경우                 | 아무것도 하지 않음 |
| 복사 생성자 |        이동 생성자나 이동 배정이 없는 경우         |  모든 멤버를 복사  |
|  복사 할당  |        이동 생성자나 이동 배정이 없는 경우         |  모든 멤버를 복사  |
| 이동 생성자 | 소멸자, 복사 생성자, 복사 및 이동 배정이 없는 경우 |  모든 멤버를 이동  |
|  이동 할당  | 소멸자, 복사 생성자, 복사 및 이동 배정이 없는 경우 |  모든 멤버를 이동  |

## 대리 생성자
하나의 생성자가 다른 생성자를 호출하여 초기화하는 기능으로 초기화 과정을 중복 없이 효율적으로 관리하는데 도움을 준다.

## 클래스 내부에서의 멤버 초기화
이전에는 클래스 내부에서 static const 멤버만 초기화가 가능했지만, C++11부터는 static이 아닌 멤버들도 선언과 함께 초기화가 가능하다. 이는 코드의 가독성을 향상시키고 초기화와 관련된 문제를 줄인다.

```
class MyHero {
    int mHP;
    int mMP;
    std::string mClass;

public:
    MyHero() : mClass{ "Warrior } { mHP = 0; mMP = 0; }
    MyHero(int hp) : mClass{ "Warrior" } { mHP = hp; mMP = 0; }
    MyHero(int hp, int mp) : mClass{ "Warrior" } { mHP = hp; mMP = mp; }
};

class MyHero { // 선언과 동시에 초기화
    int mHP{};
    int mMP{};
    std::string mClass{ "Warrior" };

public:
    MyHero() {}
    MyHero(int hp) { mHP = hp; }
    MyHero(int hp, int mp) { mHP = hp; mMP = mp; }
};
```

주의할 점은 멤버 초기화와 생성자의 초기화가 겹치면 생성자를 우선시한다는 것이다.

## override & final
override 키워드를 사용해 파생 클래스에서 부모 클래스의 가상 함수를 정확하게 오버라이딩하는 것임을 명시할 수 있다. 만약 오타나 실수로 함수 시그니처를 변경하여 오버라이딩되지 않는다면 컴파일 에러가 발생한다.

final 키워드는 클래스, 함수, 가상 함수 등을 정의할 때 사용하며 해당 클래스에 더 이상 상속될 수 없음을 명시한다.

## 상속 생성자
파생 클래스에서 기본 클래스의 생성자를 그대로 상속받아 사용할 수 있게 한다. 

```
class Derived : public Base {
public:
    using Base::Base;
};
```

## = default, = delete
`= default`는 컴파일러에게 생성자, 복사 생성자, 이동 생성자, 복사 대입 연산자, 이동 대입 연산자와 같은 특정 함수를 자동 생성하도록 지시한다. 

`= delete`는 특정 함수를 삭제하여 컴파일러가 해당 함수를 호출하려고 하면 에러를 발생시키도록 한다. 

```
class MyClass {
public:
    MyClass() = default;              // 기본 생성자를 자동 생성하도록 지시
    MyClass(const MyClass&) = delete; // 복사 생성자를 삭제하여 복사를 금지      
};
```

## 명시적 형변환 연산자
생성자에서만 사용이 가능하던 explicit 키워드가 연산자에도 사용이 가능하다.

```
class MyClass {
public:
    explicit operator int() { return 100; };
};

int main() {
    MyClass c;

    int val1 = c;                   // 암시적 변환 불가로 컴파일 에러
    int val2 = static_cast<int>(c); // 성공
}
```

# C++11 언어 - 타입
## enum class
enum의 완벽한 상위호환이다. 이름 충돌과 형변환 관련 문제를 예방하면서 타입 안전성을 높일 수 있다.

```
enum class Color {
    red, 
    blue
};

enum class TrafficLight : char { // char로 한정하여 공간 절약
    red,
    yellow,
    green
};
```

## long long
최소 64비트를 보장하는 타입이 추가되었다. `LL` 접미사를 사용한다.

# C++11 언어 - 기타
## 반환형 접미사
우선 반환형을 auto로 지정하고 매개변수 이후로 미루는 방식이다.

```
template<typename T1, typename T2>
auto Add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}
```

## 원시 문자열 리터럴
이스케이프 시퀀스를 해석하지 않고 문자열 그대로의 형태로 사용할 수 있다.

```
#include <iostream>

int main() {
    std::string file = "C:\\MyDocument\\Hello\\World"; 
    // 일반 문자열 리터럴

    std::string str1 = R"(C:\MyDocume
nt\Hell	o\World)"; 
    // 원시 문자열 리터럴

    std::cout << str1 << std::endl;
}
```

## std::static_assert
기존의 assert는 주로 런타임에 프로그램의 논리적인 조건을 체크하고 조건이 거짓인 경우 프로그램을 종료하였다. 반면에 std::static_assert는 컴파일 타임에 조건을 검사하여 조건이 거짓이면 컴파일러가 해당 위치에서 컴파일을 중단하고 에러 메시지를 출력한다. 이는 프로그램이 컴파일되는 동안에 발생할 수 있는 오류를 미리 방지하는데 사용한다. 이때 조건은 상수 표현식이다.

## 메모리 정렬
객체 안의 변수들이 메모리에서 어떻게 배치되는지를 지정하는 방법이다. 이를 통해 변수들이 메모리 상에서 특정 크기의 배수로 정렬되도록 할 수 있다.

메모리 정렬은 성능과 이식성 측면에서 중요한 역할을 한다. 데이터는 정렬된 주소에서 더 빨리 접근할 수 있고 데이터가 정렬되어야 최적화된 계산이 가능하기 때문이다.

alignas 키워드를 사용해 메모리 정렬을 지정할 수 있다. 아래 예시에서 실제로 myInt가 차지하는 크기가 4바이트라 하더라도 16바이트로 지정되어 해당 크기만큼의 메모리 공간을 차지하게 된다.

```
struct alignas(16) MyStruct {
    int myInt;
};
```

# C++11 언어 - 템플릿
## 가변 인자 템플릿
템플릿 인자를 가변형으로 받는 것이다.

```
#include <iostream>

template<typename T> // base case
T Sum(T first) {
    return first;
}

template<typename T, typename ... Args>
T Sum(T first, Args... args) {
    return first + Sum(args...);
}

using namespace std::string_literals;

int main() {
    std::cout << Sum(1, 2, 3) << std::endl;          // 출력: 6
    std::cout << Sum(1) << std::endl;                // 출력: 1
    std::cout << Sum(1, 2, 3, 4, 5) << std::endl;    // 출력: 15
    std::cout << Sum("a"s, "b"s, "c"s) << std::endl; // 출력: "abc"
}
```

C++17에서 추가된 fold expression을 활용한다면 아래와 같이 구현된다.

```
#include <iostream>

template<typename T, typename ... Args>
T Sum(T first, Args...) {
    return (first + ...);
}

using namespace std::string_literals;

int main() {
    std::cout << Sum(1, 2, 3) << std::endl;        
    std::cout << Sum(1) << std::endl;              
    std::cout << Sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << Sum("a"s, "b"s, "c"s) << std::endl;
}
```

아래 코드에서 템플릿 함수인 Make는 다양한 타입과 개수의 인자를 받아 해당 타입의 객체를 동적으로 생성하고 초기화하는 포인터를 반환한다. 이와 같은 가변 인자 템플릿과 perfect forwarding을 활용한 코드는 여러 개의 다양한 타입을 다루거나 유연한 팩토리 함수를 구현할 때 유용하게 사용된다. 

여기서 팩토리 함수란 객체 생성과 초기화를 추상화하여 객체를 생성하는데 필요한 복잡한 과정을 알 필요 없이 쉽게 사용할 수 있도록 해주는 함수를 말한다.

```
template<class T, class... Types>
T* Make(Types&& ... args)
{
    return new T(std::forward<Types>(args)...);
}
```

## extern 템플릿
템플릿은 인스턴스화 될 때마다 코드가 생성되는 방식이다. 여러 소스 파일에서 해당 템플릿 함수를 사용하면 매번 코드를 생성하므로 중복으로 생성/컴파일된다. 이러한 중복을 피하기 위해 extern 템플릿을 사용한다.

```
template <typename T>
void MyFunction() {
    // 수백 줄 코드
}

extern template void MyFunction<int>();

void Func2() {
    MyFunction<int>(); // 다른 파일에서 생성한 인스턴스 사용
}
```

## 템플릿 별명
using을 통해 템플릿 별명을 지정할 수 있다.

```
template <class T>
using Vector = std::vector<T>; // std::vector를 Vector로 별칭 지정

int main() {
    Vector<int> vector{ 1,2,3 }; 
}
```

## 지역 타입 템플릿 인자
이전에는 템플릿 인자로 전역으로 선언된 타입만 사용할 수 있었다. 지역 타입 템플릿 인자를 통해 특정 함수나 클래스 내에서만 사용되는 지역 객체를 템플릿 인자로 사용할 수 있게 되었다.

```
{
    struct Less {
        bool operator()(const X& a, const X& b) {
            return true;
        }
    };

    sort(v.begin(), v.end(), Less());
}
```

## > 표기 개선
`>>` 시프트 연산자와의 구분을 하지 못해 제한적이었던 사용이 해결되었다.

```
std::list<std::list<int> > list;  // 이중 시프트 사용
std::list<std::list<int>> list2;  // C++11에서 도입된 구문
```

# C++11 STL 일반
## std::unique_ptr
스마트 포인터라는 개념이 도입되었다. 포인터를 생성하고 아무런 관리를 해주지 않아도 컴파일러가 자동적으로 해제한다는 것이 핵심이다.

std::unique_ptr은 1:1 관계를 가지는 스마트 포인터다.

- 포인터를 저장하고 있는 객체를 소유한다.
- 소유권 문제를 방지하기 위해 복사 생성자, 복사 배정은 지원하지 않는다. 이동 생성자, 이동 배정은 가능하다.
- 다음과 같이 구성된다.
  - 포인터 : 생성자를 통해 포인터 지정이 가능하다. 다음 멤버 함수로 접근이 가능하다.
    - unique_ptr::reset() : 새로운 포인터를 지정한다.
    - unique_ptr::get() : 현재 포인터를 반환한다.
    - unique_ptr::release() : 현재 포인터를 해제한다.
  - 제거자 : 객체가 소멸될 때 처리하는 방식을 관리하기 위한 deleter를 지정할 수 있다.

```
int main() {
    std::unique_ptr<int> p{ new int };
    std::unique_ptr<int> p2{ std::make_unique<int>() }; // C++14

    *p = 1;
    std::cout << *p << std::endl;
} // p는 자동 해제
```

```
class MySong {
public:
    int mTackNo;
    std::string mName;
    MySong(int no, std::string name) : mTackNo{ no }, mName{ name }  {}
};

int main() {
    std::unique_ptr<MySong> spSong = std::make_unique<MySong>(1, "BattleBGM");

    // 포인터에 접근
    std::cout << spSong->mTackNo << " : " << spSong->mName << std::endl;

    // unique_ptr 객체의 멤버 함수에 접근
    spSong.release(); // delete p;
    spSong.reset();   // delete p; p = nullptr;

    MySong* ptr = spSong.get(); 
    // ptr은 일반 포인터
    // get()을 사용한 명시적 변환을 권장
}
```

## std::shared_ptr
1:n 관계를 가지는 스마트 포인터다. 내부에 참조 카운트라는 것이 존재하여 사용될 때마다 카운트가 증가하고 파괴될 때마다 카운트가 감소한다. 카운트가 0이 되면 메모리를 해제한다.

```
class Image {};

class Demon {
    int mHealth;
    int mAttack;
    std::shared_ptr<Image> mspImage;

public:
    Demon(int h, int a, std::shared_ptr<Image> spImage) : mHealth(h), mAttack(a), mspImage(spImage) {}
};

int main() {
    std::shared_ptr<Image> spImage = std::make_shared<Image>();
    // mspImage : 1
    {
        std::unique_ptr<Demon> spDemon = std::make_unique<Demon>(100, 10, spImage);
        // mspImage : 2
        {
            std::unique_ptr<Demon> spDemon2 = std::make_unique<Demon>(100, 10, spImage);
            // mspImage : 3
        }
        // mspImage : 2
    }
    // mspImage : 1
}
```

## std::weak_ptr
소유권을 가지지 않는 스마트 포인터다. shared_ptr을 가르키는 용도로 추가되었다. 가장 큰 특징은 shared_ptr의 참조 카운트를 증가시키지 않으면서 해당 포인터가 여전히 유효한지 추적할 수 있다는 것이다. 몬스터 파티와 같이 관리용이 아닌 단순 참고용에 유용하다.

## std::tuple
std::pair의 조금 더 일반화된 버전이다. 

```
#include <iostream>
#include <tuple>

int main() {
    std::tuple<int, std::string, std::string> song;

    song = std::make_tuple(1, "helloween", "Dr.Stein"); 

    std::cout << "TrackNO : " << std::get<0>(song) << std::endl; 
    std::cout << "Artist : " << std::get<1>(song) << std::endl; 
    std::cout << "Title : " << std::get<2>(song) << std::endl;
}
```

C++17에서 추가된 구조 분해 선언을 사용해 아래와 같이 구현이 가능하다.

```
#include <iostream>
#include <tuple>

int main() {
    std::tuple<int, double, std::string> myTuple(42, 3.14, "Hello");

    auto [value1, value2, value3] = myTuple;

    std::cout << value1 << std::endl;
    std::cout << value2 << std::endl;
    std::cout << value3 << std::endl;
}
```

## std::function과 std::bind
std::function은 호출 가능한 객체를 저장하고 호출하는데 사용한다. 호출 가능한 객체에는 함수 포인터, 함수 객체, 람다식 등이 포함될 수 있다. 이를 통해 서로 다른 타입의 호출 가능한 객체들을 하나의 일관된 방식으로 다룰 수 있다. 함수 포인터에 비해 사용이 편리하다.

```
#include <iostream>
#include <functinal>

void MyFunction(const int arg1) {}

struct MyStruct {
    void operator()() {}
};

int main() {
    // 함수
    std::function<void(const int)> functor1 = MyFunction; 
    functor1(42);

    // 구조체 연산자
    std::function<void()> functor2 = MyStruct(); 
    functor2();
    
    // 람다식
    std::function<void()> functor3 = []() {};
    functor3();
}
```

std::bind는 함수 호출을 좀 더 유연하게 다루기 위한 도구다. 인자를 부분적으로 고정하거나 원하는 순서로 조작할 수 있도록 한다.

```
#include <iostream>
#include <functional>

void F(int arg1, char arg2) {
    std::cout << arg1 << ", " << arg2 << std::endl;
}

using namespace std::placeholders;

int main() {
    auto functor1 = std::bind(F, _1, _2); // 매개변수 2개를 받도록 바인딩
    functor1(1, 'a');

    auto functor2 = std::bind(F, _2, _1); // 매개변수들의 순서를 뒤집음
    functor2('a', 1);

    auto functor3 = std::bind(F, 10, _1); // 첫 번째 인자 10으로 고정
    functor3('a');
}
```

## 정규표현식
특정한 문자 패턴을 표현하기 위해 사용되는 문자열이다. 텍스트에서 원하는 부분을 찾거나 대체하는 등의 작업에 유용하다. 정규표현식은 다양한 프로그래밍 언어와 텍스트 편집기에서 지원되며 문자열 처리 작업을 간단하게 만들어준다. 퇴근을 빨라지게 할 수 있는 고마운 친구다.

```
#include <iostream>
#include <regex>

int main() {
    std::cout << "이메일 : ";
    std::string email;
    std::cin >> email;

    //std::regex pattern("(\\w+[\\w\\.]*)@(\\w+[\\w\\.]*)\\.([A-Za-z]+)");
    std::regex pattern(R"((\w+[\w\.]*)@(\w+[\w\.]*)\.([A-Za-z]+))");

    if (std::regex_match(email, pattern)) {
        std::cout << "올바른 이메일 주소" << std::endl;
    } else {
        std::cout << "잘못된 이메일 주소" << std::endl;
    }
}
```

## 타입 특성
주어진 타입에 대한 정보를 컴파일 타임에 알려준다. 프로그램이 실행 중일 때가 아닌 컴파일 과정에서 객체의 특성과 속성을 파악할 수 있게 해준다. `<type_traits>` 헤더에 정의된 is_array, is_class, is_base_of 등 다양한 함수들을 활용해 타입 관련 작업을 보다 쉽게 처리할 수 있다.

## 시간 유틸리티
정밀한 시간을 다룰 수 있는 도구들을 제공하는 기능이다. 프로그램 실행 시간 측정, 시간 간격 계산, 시간 표시 등의 작업에서 활용될 수 있다.

## 난수 생성
컴퓨터는 기본적으로 미리 정해진 규칙을 따라 작동하기 때문에 실제로 무작위한 것을 만들어내기는 어렵다. 난수 생성은 마치 무작위인 것처럼 보이는 숫자들의 시퀀스를 생성한다. 이를 통해 프로그램은 다양한 상황에서 예측 불가능한 값들을 사용할 수 있다.

# C++11 STL 컨테이너 및 알고리즘
## std::array
일반 배열과 동일한 컨테이너가 추가되었다.

## std::forward_list
단일 연결 리스트가 추가되었다.

## unordered_ 계열 컨테이너
map, set에서 정렬이 빠진 unordered_map, unordered_set이 추가되었다.

# C++11 STL 동시성
## std::thread

## 상호 배제

## std::lock

## std::async