# ifndef BYTECODE_HPP
#define BYTECODE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

using Opcode = uint8_t; //type Instruct []byte
using Instruct = std::vector<Opcode>; // type Opcode byte

enum class command : uint8_t {
	OpConstant = 0, 
};

struct definition { // 정의
	std::string name;
	std::vector<int> operandWidth; //operand 피연산자 너비
};

std::map<command, definition*> commandTable = { // 유니폼 초기화 방식
	{command::OpConstant, new definition{"OpConstant", {2}}} // 동적 할당 고려 (스마트 포인터 사용?) <- 알아봐야함
};

std::pair<definition*, bool> lookUp (command op) {
	std::map<command, definition*>::iterator it = commandTable.find(op);
	if (it == commandTable.end())
	{
		std::cerr << "Error: command not found. Opcode [" << static_cast<int>(op) << "]" << std::endl;
		return {nullptr, false};
	}

	return {it->second, true};
}

#endif