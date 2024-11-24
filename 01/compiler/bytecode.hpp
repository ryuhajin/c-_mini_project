# ifndef BYTECODE_HPP
#define BYTECODE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

#include "utils.hpp"

using Opcode = uint8_t; //type Instruct []byte
using Instruct = std::vector<Opcode>; //지시하다 type Opcode byte

enum class command : uint8_t {
	OpConstant = 0, 
};

struct definition { // 정의
	std::string name;
	std::vector<int> operandWidth;
	//vecotor의 size == 해당 명령어에 쓰이는 피연산자 개수
	//vector의 값 == 피연산자의 크기
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

Instruct Make(command op, const std::vector<int>operands)
{
	std::map<command, definition*>::iterator it = commandTable.find(op);
	if (it == commandTable.end())
		return {};
	
	int instructionLen = 1; //cmd byte
	definition* def = it->second;

	for (int byte : def->operandWidth)
	{
		instructionLen += byte;
	}

	Instruct instruction(instructionLen); //vector constructor
	instruction[0] = static_cast<Opcode>(op); // 가독성 생각해보기 Opcode란 명칭을 굳이 고집해야하나?
	
	bool endian = utils::is_little_endian();

	int offset = 1;
	for (size_t i = 0; i < operands.size(); i++)
	{
		int width = def->operandWidth[i]; // 해당 커맨드의 operand 길이
		switch (width)
		{
			case 2: { 
				if (endian)
					instruction[offset] = utils::to_big_endian(operands[i], width);
				else
					instruction[offset] = utils::to_instruct(operands[i], width);
				break;
			}
			default: //error code?
				break;
		}
		offset += width;
	}
	
	
}

#endif