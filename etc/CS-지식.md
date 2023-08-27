- [컴퓨터 기초](#컴퓨터-기초)
- [CPU](#cpu)
- [Memory](#memory)
- [프로그래밍 언어](#프로그래밍-언어)
- [2의 보수](#2의-보수)
- [정적 라이브러리와 동적 라이브러리](#정적-라이브러리와-동적-라이브러리)
- [POD(Plain Old Data)](#podplain-old-data)
- [무명 객체(Anonymous Object)](#무명-객체anonymous-object)
- [Relationship](#relationship)

# 컴퓨터 기초
컴퓨터는 껐다 키는 스위치에서 출발한다. 컴퓨터가 0과 1로 이루어졌다고 하는 이유도 여기에 있다.

최초의 컴퓨터라고 하는 에니악만 해도 크기가 운동장만하다. 진공관 ⊂ 트랜지스터 ⊂ 집적회로(IC)로 발전하면서 이 모든걸 압축한게 지금의 컴퓨터로, 결국 컴퓨터의 역사는 집적의 역사라고 할 수 있다.

# CPU
컴퓨터의 핵심이다. Central Processing Unit(중앙처리장치)를 줄여서 부른다.

CPU는 연산, 제어, 기억 이렇게 세 가지 요소를 담당하고 있다.

CPU는 레지스터라고 하는 아주 빠른 저장 공간을 쓴다. 마구잡이로 명령들을 처리하면 안되니까 이 명령들을 나열해서 기억할 공간이 필요한 것이다. 이 레지스터 크기에 따라서 32비트 컴퓨터냐 64비트 컴퓨터냐 하는 것이 정해진다. 어떤 프로그램을 설치할 때 x86인지 x64인지로 나뉘는 이유기도 하다.

# Memory
ROM(Read Only Memory)이니 RAM(Random Access Memory)이니 하는 것들이다.

레지스터로는 크기가 작으니까 밖에 더 저장할 수 있는 공간을 만들었다.

ROM은 이름에서 알 수 있듯이 오로지 읽기만 한다. 컴퓨터를 구동할 때 필요한 정보가 들어있어서 전원을 꺼도 정보가 그대로 있다. RAM은 우리가 흔히 컴퓨터 조립이나 업그레이드할 때 부르는 그 램이 맞다.

# 프로그래밍 언어
0과 1로 이뤄져서 컴퓨터가 바로 알아듣는 언어가 기계어다. 이걸 사람이 쓰기엔 너무 불편해서 그래도 최소한 의미가 있는 걸로 바꾼게 어셈블리어다. 두 언어 모두 저수준 언어로 컴퓨터친화적이라고 볼 수 있다.

여기서 더 나아가서 만든게 고수준 언어로 우리가 많이 쓰는 C, C++, Java와 같은 언어가 여기에 속한다. 인간친화적인 언어라서 중간에 통역이 필요하다.

# 2의 보수
컴퓨터는 양수와 음수를 구분하기 위해서 가장 앞의 비트를 사용한다. 그리고 음수를 더하기로 계산하기 위해서 2의 보수를 사용한다. `0101`의 2의 보수는 비트를 반전시키고 1을 더한 `1011`이 되는 식이다.

# 정적 라이브러리와 동적 라이브러리
|                           정적 라이브러리                           |                       동적 라이브러리                        |
| :-----------------------------------------------------------------: | :----------------------------------------------------------: |
|                              lib 파일                               |                           dll 파일                           |
|                         실행파일만으로 실행                         |             실행파일과 별도의 dll을 이용해 실행              |
|               외부 정보를 참조하지 않기 때문에 빠르다               |         실행 시간에 dll 파일을 뒤져야 하므로 느리다          |
|                 라이브러리 기능을 수정하기가 어렵다                 |            라이브러리를 쉽게 업그레이드 가능하다             |
| 서로 다른 프로젝트에서 사용하려면 각각 라이브러리를 링크해야만 한다 | 서로 다른 프로젝트에서도 하나의 dll만 있으면 사용이 가능하다 |

동적 라이브러리는 기능이 변경되어도 다시 빌드할 필요 없이 간단히 라이브러리만 배포하면 된다.

# POD(Plain Old Data)
C언어에서 제공되는 타입들이 여기에 해당하는데 단순한 메로리 구조를 가지는 객체를 뜻한다. 원본 메모리에서 다른 메모리로 복사나 이동이 매우 쉬워 컴퓨터 성능에 유리하다는 장점이 있다.

C++에서 POD는 Standard Layout Type, Trivial Type 이렇게 두 가지 조건이 충족되어야 한다고 본다. 이는 성능에 관련이 있는데 사용자가 클래스에 생성자를 붙이면 Trivial Type이 아니게 된다.

```
#include <iostream>

class ClassA {
public:
    ClassA() {}
};

class ClassB {
public:
    ClassB() = default;
};

int main() {
    std::cout << std::is_trivial<ClassA>::vlaue << std::is_pod<ClassA>::value <<std::endl;

     std::cout << std::is_trivial<ClassB>::vlaue << std::is_pod<ClassB>::value <<std::endl;
}
```

위 코드를 출력해보면 ClassA는 Trivial Type, POD가 아니고 ClassB는 Trivial Type, POD가 맞다는 결과를 알 수 있다. 그러니까 POD가 되기 위해서는 default 키워드로 암시적 기본 생성자를 명시해야 한다.

# 무명 객체(Anonymous Object)
이름이 없는 임시 객체로 주로 한 번만 사용되거나 함수의 반환값, 특정 표현식의 결과로 생성되는 객체로 rvalue를 가리킨다.

```
class MyClass {
public:
    int mValue;
    MyClass(int value) : mValue(value) {
        std::cout << "[ MyClass() ] : " << mValue << std::endl;
    }

    MyClass operator+(const MyClass& c) {
        return MyClass{ mValue + c.mValue };
    }
};

int Square(MyClass c) {
    return c.mValue * c.mValue;
}

int main() {
    MyClass c1{ 1 }, c2 { 2 };

    std::cout << "-----" << std::endl;
    Square(c1 + c2);

    std::cout << "-----" << std::endl;
    std::cout << (c1 + c2).mValue << std::endl;

    std::cout << "-----" << std::endl;
    MyClass c3{ c1 + c2 };
}
```

위 코드의 출력은 아래와 같다. c1, c2를 생성할 때 외에도 3번 생성자가 불리는 것을 알 수 있는데, 이들이 무명객체이다.

```
[ MyClass() ] : 1
[ MyClass() ] : 2
-----
[ MyClass() ] : 3
-----
[ MyClass() ] : 3
3
-----
[ MyClass() ] : 3
```

조금 더 효율적인 프로그램을 만들기 위해 Square 함수에 매개변수를 참조형인 `MyClass& c`로 받는다면 오류가 발생한다. 무명객체는 rvalue이기 때문에 당연히 참조형을 사용할 수 없다. 따라서 `const MyClass& c`로 사용하면 오류가 발생하지 않는다.

# Relationship
|    용어    |                        개념                        |
| :--------: | :------------------------------------------------: |
| is-part-of |                 Composition(결합)                  |
|   has-a    |                Aggregation(집단화)                 |
|   use-a    |                Association(연관화)                 |
|    is-a    | Generalization(일반화) 또는 Specialication(특수화) |

A is-part-of B 관계는 예를 들면 엔진 is-part-of 자동차라고 할 수 있다.
- A는 B의 일부 구성 요소이다.
- A는 한 번에 하나의 객체에만 존재한다.
- A는 B에 의해 관리된다.
- A는 B의 존재를 알지 못한다.

```
class Status {
public:
    int mHP;
    int mMP;
};

class Player {
    Status mStatus;
};
```

위 코드에서 A는 Status에 해당하고 B는 Player에 해당함을 알 수 있다.

A has-a B 관계는 예를 들면 자동차 has-a 타이어라고 할 수 있다.
- B는 A의 일부 구성 요소이다.
- B는 한 번에 여러 오브젝트에 소속된다.
- B는 A에 의해 관리되지 않는다.
- B는 A의 존재를 알지 못한다.

```
class Player {
};

class Auction {
    Player* mPlayers;
};
```

위 코드에서 A는 Auction에 해당하고 B는 Player에 해당한다.

A use-a B 관계는 예를 들면 운전자 use-a 자동차라고 할 수 있다.
- B는 A와 관련이 없다.
- B는 한 번에 여러 오브젝트에 소속된다.
- B가 A에 의해 관리되지 않는다. 
- B는 A의 존재를 알 수도 있고 모를 수도 있다.

```
class Potion {
public:
    int mCount;
    int mRecovery;
};

class Player {
    Potion* pPotion;
};
```

위 코드에서 A는 Plyaer에 해당하고 B는 Potion에 해당한다.

A is-a B 관계는 예를 들면 경찰차 is-a 자동차라고 할 수 있다. 핵심은 공통된 개념을 묶어서 일반화하는 것과 여기서 추가 정보를 포함하여 객체를 생성하는 특수화이다. 그러니까 파생, 다른 말로는 상속을 말한다.