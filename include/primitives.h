#pragma once

#include <cstdint>
#include "membuf.h"
#include <vector>
#include <string>

namespace quasar {
		namespace tools {

				class primitives {
				public:
						static void write_int32(std::vector<unsigned char> &payloadBuf, int32_t value);
						static int32_t read_int32(mem_istream &stream);

						static void write_varint32(std::vector<unsigned char> &payloadBuf, uint32_t value);
						static uint32_t read_varint32(mem_istream &stream);

						static void write_string(std::vector<unsigned char> &payloadBuf, std::string value);
						static std::string read_string(mem_istream &stream);

				private:
						static uint32_t encode_zigzag32(int32_t value);
						static int32_t decode_zigzag32(int32_t value);
				};

		}
}