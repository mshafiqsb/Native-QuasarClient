#include "stdafx.h"
#include "primitives.h"

using namespace std;
using namespace quasar::tools;

void primitives::write_varint32(vector<unsigned char> &payloadBuf, uint32_t value) {
	for (; value >= 0x80u; value >>= 7) {
		payloadBuf.push_back(static_cast<char>(value | 0x80u));
	}
	payloadBuf.push_back(static_cast<char>(value));
}

uint32_t primitives::read_varint32(mem_istream &stream) {
	int32_t result = 0;
	int32_t offset = 0;

	for (; offset < 32; offset += 7) {
		unsigned char b;
		stream.read(&b, sizeof(char));

		result |= (b & 0x7f) << offset;

		if ((b & 0x80) == 0)
			return static_cast<uint32_t>(result);
	}

	throw 0;
}

void primitives::write_int64(std::vector<unsigned char> &payloadBuf, int64_t value) {
	write_varint64(payloadBuf, encode_zigzag64(value));
}

int64_t primitives::read_int64(mem_istream &stream) {
	return decode_zigzag64(read_varint64(stream));
}

void primitives::write_varint64(std::vector<unsigned char> &payloadBuf, int64_t value) {
	for (; value >= 0x80u; value >>= 7) {
		payloadBuf.push_back(static_cast<char>(value | 0x80u));
	}
	payloadBuf.push_back(static_cast<char>(value));
}

uint64_t primitives::read_varint64(mem_istream &stream) {
	int64_t result = 0;
	int32_t offset = 0;

	for (; offset < 64; offset += 7) {
		unsigned char b;
		stream.read(&b, sizeof(char));

		result |= ((long) (b & 0x7f)) << offset;

		if ((b & 0x80) == 0)
			return static_cast<uint64_t>(result);
	}

	throw 0;
}

void primitives::write_string(vector<unsigned char> &payloadBuf, string value) {
	if (value.empty()) {
		write_varint32(payloadBuf, 1);
		return;
	}

	int32_t totalBytes = value.size();

	write_varint32(payloadBuf, totalBytes + 1);
	write_varint32(payloadBuf, totalBytes);

	for (auto const chr : value) {
		payloadBuf.push_back(chr);
	}
}

string primitives::read_string(mem_istream &stream) {
	uint32_t totalBytes = primitives::read_varint32(stream);

	if (totalBytes == 0 || totalBytes == 1) {
		return nullptr;
	}

	totalBytes--;
// skip totalchars
	primitives::read_varint32(stream);
	int32_t streamBytesLeft = totalBytes;
	std::vector<unsigned char> buf(totalBytes);

	stream.read(&buf[0], totalBytes);
	return std::string(reinterpret_cast<char *>(&buf[0]), buf.size());
}

void primitives::write_int32(vector<unsigned char> &payloadBuf, int32_t value) {
	write_varint32(payloadBuf, encode_zigzag32(value));
}

int32_t primitives::read_int32(mem_istream &stream) {
	return decode_zigzag32(read_varint32(stream));
}

uint32_t primitives::encode_zigzag32(int32_t value) {
	return static_cast<uint32_t>((value << 1) ^ (value >> 31));
}

int32_t primitives::decode_zigzag32(uint32_t value) {
	return static_cast<int32_t>(value >> 1) ^ -static_cast<int32_t>(value & 1);
}

uint64_t primitives::encode_zigzag64(int64_t value) {
	return static_cast<uint64_t>((value << 1) ^ (value >> 63));
}

int64_t primitives::decode_zigzag64(uint64_t value) {
	return static_cast<int64_t>(value >> 1) ^ -static_cast<int64_t>(value & 1);
}