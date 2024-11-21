# compiler in c++

## 1일차

```go
//go의 예시

package code // c++에서 헤더 선언과 같음

type Instruct []byte // type == typedef

type Opcode byte // go의 byte = 부호없는 8비트 정수
```

## using 키워드 사용
```c++
//typedef의 경우 원형 - 별칭
typedef std::classPtr<myClass> myClassPtr;


// using의 경우 별칭 = 원형 할당
using myClassPtr = std::classPtr<myClass>;
```

- using은 c++11에서 추가된 문법이다.
- 기존의 typedef와 동일한 역할을 한다.
- typedef의 경우 template 에서 사용 불가능하다.
- using의 경우 template 에서 사용 가능하다.

```c++
// using template 사용 예시
template <typename T>
using my_vector = std::vector<T>;
```

## enum VS enum class
```go
//go의 예시

const (
 OpConstant Opcode = iota
)
//  iota는 Go 언어에서 상수 정의 블록(const) 내부에서 사용할 수 있는 특별한 식별자로 c++의 enum과 유사한 기능을 제공한다.
```

- enum은 상수의 집합으로 간주된다.
- enum의 값들은 컴파일 타임에 결정되며 변경할 수 없기 때문이다.

`enum`: 단순하고 빠르게 정의된 상수들을 전역에서 사용할 때 편리. 그러나 이름 충돌이 생길 수 있다. (다른 enum 영역이더라도 변수명이 같으면 안된다.)

`enum class`: 타입 안정성과 스코프 제어가 중요한 경우에 사용하는 것이 좋다. 특히 모던 C++ 프로그래밍에서는 enum class 사용을 권장한다.

|특성|enum|enum class|
|---|---|---|
스코프|전역|강력한 스코프 (`enum class Color; Color::red`)
형변환|정수형으로 암묵적 변환 가능|암묵적 변환 불가능. 명시적 변환 필요(`int value = static_cast<int>(Color::Green);`)
충돌위험|있음 (변수명이 같으면 안됨)|없음
기본 타입 지정|불가능|가능(`enum class : uint8_t`)

## 명령 필드 정의
```go
//go
import "fmt"

type Definition struct { //구조체 선언
	Name string 
	OperandWidths []int // 가변 길이 배열 (c++ std::vector<int>와 비슷하다)
}

var definitions = map[Opcode]*Definition
// map의 키는 Opcode로 값은 Definition 구조체의 포인터로 정의
{
	OpConstant: {"Opconstant", []int{2}},
	//OpConstant 키에 "Opconstant" 라는 문자열과 2개짜리 int 배열을 가진 definition 구조체 포인터 저장
} 

// go는 두개의 리턴값을 가질수 있다. ((*Definition, error) 리턴값이 두개라는 정의)
func Lookup(op byte) (*Definition, error) {
	def, ok := definitions[Opcode(op)] //:=는 짧은 선언 연산자로, 변수의 선언과 초기화를 동시에 수행함. (c++의 auto 키워드와 비슷한 기능)

	//여기서 def는 찾은 결과, ok는 값이 존재하는지 여부를 나타내는 bool 타입.
	if !ok {
		return nil, fmt.Errorf("opcode %d undefined", op)
	} // nil 은 NULL와 같은 기능을 가진다. (zero value)

	return def, nil
}
```

go 언어를 해석하고 내가 이해한 바
> - Definition struct : Opcode에 해당하는 명령어의 이름, 크기를 저장해놓을 데이터 구조체
> - var definitions: Opcode에 해당하는 명령어를 키, Definition 구조체의 포인터를 값으로 갖는 명령어 테이블
> - fun Lookup: 명령어 테이블을 이용해 Opcode를 키로 찾고 해당하는 데이터 구조체가 있으면 그것을 리턴, 없으면 에러를 뱉는 함수