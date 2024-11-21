# ifndef BYTECODE_HPP
#define BYTECODE_HPP

#include <vector>
#include <cstdint>

using Opcode = uint8_t; //type Instruct []byte
using Instruct = std::vector<Opcode>; // type Opcode byte

enum class command : uint8_t {
	OpConstant = 0, 
};


#endif