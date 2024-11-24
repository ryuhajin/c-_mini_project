# ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

namespace utils {
	bool is_little_endian() {
		uint16_t value = 1;
		uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);
		
		return (*ptr == 0x1);
	}

	//instruction에 빅 엔디안 형식으로 길이width 만큼 넣어주기
	std::vector<uint8_t> to_big_endian(int value, int width)
	{
		uint8_t* offset = reinterpret_cast<uint8_t*>(&value);

		std::vector<uint8_t> toBig(width);

		offset += width -1;
		
		for (size_t i = 0; i < width; i++)
		{
			toBig[i] = *offset;
			offset--;
		}

		return (toBig);
	}

	std::vector<uint8_t> to_instruct(int value, int width)
	{
		uint8_t* offset = reinterpret_cast<uint8_t*>(&value);

		std::vector<uint8_t> ins(width);

		offset += sizeof(value) - width;

		for (size_t i = 0; i < width; i++)
		{
			ins[i] = *offset;
			offset++;
		}

		return (ins);
	}
}

#endif