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

## 유니폼 초기화
- c++11부터 도입되었음
- 중괄호 `{}` 를 사용하여 통일된 형식으로 초기화 할 수 있는 기능이다.

### 유니폼 초기화 예시
```c++
#include <vector>
#include <map>

std::vector<int> numbers{1, 2, 3, 4, 5};

std::map<int, std::string> students{
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}
    };
```

### c++98과 c++11 초기화 차이
|특징|c++98 초기화|c++11 유니폼 초기화|
|---|---|---|
벡터 초기화|std::vector<int> vec; vec.push_back(1); vec.push_back(2);|std::vector<int> vec{1,2};|
배열 초기화|int arr[3] = {1,2,3}; | int arr[] = {1,2,3};|
맵 초기화|std::map<int, std::string> m; m.insert(std::make_pair(1, "Alice"));|std::map<int, std::string> m{ {1, "Alice"}, {2, "Bob"} };|

### 클래스 맴버 초기화 차이점
```c++
//c++98
class MyClass {
    int a;
    int b;

public:
    // 생성자를 이용해 멤버 변수 초기화
    MyClass(int x, int y) : a(x), b(y) {
    }
};


//c++11
class MyClass {
    int a{10};  // 멤버 변수 a를 10으로 초기화
    int b{20};  // 멤버 변수 b를 20으로 초기화

public:
    // 생성자 없이도 기본 초기값을 사용할 수 있음
    MyClass() = default;  // 기본 생성자
};
```

## nullptr
C++98과 C++03에서는 널 포인터(null pointer)를 나타내기 위해 NULL을 사용했다.

하지만 **NULL은 실제로는 단순히 0으로 정의된 매크로 상수**이기 때문에 **정수와 혼동 문제**가 있었다.

특히 함수 오버로드를 할 때 문제가 되곤했다.

```c++
void foo(int);
void foo(char*);

foo(NULL); // 이 경우, 'foo(int)'가 호출될 수 있다.
```

이를 해결하기 위해 c++11부터 오직 포인터 리터럴 타입인 `nullptr`이 도입됐다.

### nullptr 사용 예시
```c++
void foo(int) {
    std::cout << "정수 버전 foo(int) 호출" << std::endl;
}

void foo(char*) {
    std::cout << "포인터 버전 foo(char*) 호출" << std::endl;
}

int main() {
    foo(NULL);    // 정수 버전 foo(int)가 호출될 가능성이 있음
    foo(nullptr); // 포인터 버전 foo(char*)가 호출됨

    return 0;
}
```

### NULL VS nullptr
특성|NULL|nullptr|
|---|---|---|
타입|정수(0)로 정의된 매크로|std::nullptr_t
안정성|정수와 혼동 가능|오직 포인터 타입
함수 오버로드|정수 오버로드 호출 가능성이 있음|포인터 타입 오버로드로 명확하게 매칭

## 명령어 생성

```go
// code/code_test.go
package code

import "testing"

func TestMake(t *test.T) {
	tests := []struct {
		op Opcode
		operands []int
		expected []byte
	}{
		{OpConstant, []int{65534}, []byte{byte(OpConstant), 255, 254}},
	}

	for _, tt := range tests {
		instruction := Make(tt.op, tt.operands...)

		if len(instruction) != len(tt.expected) {
			t.Errorf("instruction has wrong length. want=%d, got=%d", len(tt.expected), len(instruction))
		}
		

		for i, b := range tt.expected {
			if instruction[i] != tt.expected[i] {
				t.Errorf(
					"wrong byte at pos %d. want=%d, got=%d", t, b, instruction[i])
			}
		}
	}
}

//code/code.go

import {
	"encoding/binary"
	"fmt"
}

//Make 함수는 주어진 명령어(Opcode)와 피연산자(operands)를 사용하여 바이트 코드 형태의 명령어를 생성하는 함수

// ...int 가변인자 사용 (어떤 명령어는 피연산자가 없을 수도 있고, 어떤 명령어는 하나 이상의 피연산자가 필요할 수 있다.)
func Make(op Opcode, operands ...int) []byte {
	def, ok :=definitions[op]
	if !ok{
		return []byte{}
	}

	instructionLen := 1
	// for _, w := range == for-each 반복문
	for _, w := range  def,OperandWidths {
		instructionLen += w
	}

	instruction := make([]byte, instructionLen) // make는 go의 내장함수 바이트 슬라이스 생성 후 초기화.
	instruction[0] = byte(op)

	offset := 1
	for i, o := range operands {
		width := def.OperandWidths[i]
		switch width {
			case 2:
				binary.Bigndian.PutUint16(instruction[offset:], uint16(o))
		}
		offset += width
	}
	
	return instruction
}

```

### instruct와 operandWidth의 단위 제대로 이해하기
- Instruct (`std::vector<uint8_t>`): 명령어와 (Opcode) 피연산자들을 바이트 코드 형태로 저장하는 배열.
	- 기계가 이해할 수 있는 바이트 단위의 데이터를 저장한다.
	- 명령어를 바이트 단위(uint8_t)로 해석하고 실행하는 과정에서 메모리 접근과 저장이 명확해진다.
- operandWidth (`std::vector<int>`): 각 명령어가 필요로 하는 피연산자의 크기 정보를 저장하는 벡터.
	-operandWidth{2}는 OpConstant 명령어가 2바이트 크기의 피연산자 하나를 요구한다는 뜻이다.
	- 여러 개의 피연산자가 있을 경우, 벡터의 각 요소가 각 피연산자의 크기를 나타냅니다.
	- 예: {1, 4}는 첫 번째 피연산자가 1바이트, 두 번째 피연산자가 4바이트임을 의미.
	- operandWidth 벡터는 전체 크기를 합한 값이 아니라, 각각의 피연산자의 개별 크기를 표현하기 위한 것이다.

## 리틀 엔디안과 빅 엔디안
리틀 엔디안와 빅 엔디안의 중요한 점은 비트의 순서가 아니라 바이트의 순서라는 것이다.

- 비트 순서는 리틀 엔디안과 빅 엔디안과 관계없이 항상 내부적으로 동일하게 저장된다.
- 예를 들어, 0x34는 항상 00110100으로 표현되며, 비트 자체의 순서가 바뀌지는 않는다.
- 바이트 순서는 메모리에 여러 바이트를 어떤 순서로 저장할 것인가를 의미한다.
- 리틀 엔디안은 하위 바이트부터 먼저 메모리에 저장하고, 빅 엔디안은 상위 바이트부터 먼저 저장한다.

```c++
// 리틀 엔디안인지 확인하는 함수

bool is_little_endian() {
    uint16_t value = 0x1;
    uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);
    return (*ptr == 0x1);
}
```
1. uint16_t value = 0x1;

여기서 value는 0x0001이라는 값을 가진 16비트 정수이다.
16비트 정수는 두 개의 바이트로 구성된다.
value의 메모리 상 표현 `0x0001 (이진수로는 0000 0000 0000 0001)`

2. uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);:

value의 주소를 uint8_t*로 캐스팅한다.
즉, value의 메모리 주소를 바이트 단위(uint8_t = 8비트)로 접근할 수 있는 포인터로 변경하는 것이다.
이 포인터는 value가 저장된 메모리의 첫 번째 바이트를 가리키게 된다.

3. return (*ptr == 0x1);:

이제 ptr이 가리키는 메모리의 첫 번째 바이트를 확인한다.
만약 리틀 엔디안 시스템이라면, value의 바이트 순서는 **LSB(최하위 바이트)**부터 메모리에 저장됩니다. 즉, 0x0001은 메모리에 01 00으로 저장된다.
리틀 엔디안이라면 *ptr이 가리키는 첫 번째 바이트는 0x01이다.

반대로 빅 엔디안 시스템이라면, 0x0001은 메모리에 00 01로 저장되며, *ptr이 가리키는 첫 번째 바이트는 0x00이 된다.

따라서 (*ptr == 0x1)이 참이면, 시스템은 리틀 엔디안이고, 그렇지 않다면 빅 엔디안이라는 것을 의미한다.

## 범위 기반 for 문 (for-each와 비슷함)
c++11부터 도입된 기능으로 컨테이너나 배열의 모든 요소를 순회할 때 편리하게 사용할 수 있다.

기본적으로 다음과 같은 형태이다.
```c++
for (auto element : container) {
    // element에 대한 작업 수행
}
```

### 범위 기반 for문에서 요소를 받는 방법
1. 값 복사 (기본 동작)
```c++
for (auto element : container) {
    // element의 값은 container의 요소에서 복사됨.
    element += 1;  // 원래의 container 요소는 변경되지 않음.
}
```

2. 참조로 받기 (&)
```c++
for (auto &element : container) {
    // element는 container의 실제 요소를 참조함.
    element += 1;  // 원래의 container 요소가 변경됨.
}
```

3. 상수 참조 (const &)
```c++
for (const auto &element : container) {
    // element는 container의 실제 요소를 상수 참조함.
    // 읽기만 가능하며, 수정할 수 없음.
    std::cout << element << std::endl;
}
```


