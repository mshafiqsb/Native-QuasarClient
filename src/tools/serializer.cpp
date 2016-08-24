#include "stdafx.h"
#include "serializer.h"

using namespace std;
using namespace quasar::tools;

serializer::serializer() :
		m_stream(std::vector<unsigned char>()) {
}

vector<unsigned char> *serializer::get_serializer_instance() {
	return &m_stream;
}

vector<unsigned char> serializer::get_serializer_data() const {
	return m_stream;
}

void serializer::write_primitive_array(const std::vector<std::string> &val) {
	write_primitive(static_cast<uint32_t>(val.size() + 1));
	for (auto const str : val) {
		write_primitive(str);
	}
}

void serializer::write_primitive_array(const std::vector<int32_t> &val) {
	write_primitive(static_cast<uint32_t>(val.size() + 1));
	for (auto const curVal : val) {
		write_primitive(curVal);
	}
}

void serializer::write_primitive_array(const std::vector<uint32_t> &val) {
	write_primitive(static_cast<uint32_t>(val.size() + 1));
	for (auto const curVal : val) {
		write_primitive(curVal);
	}
}

void serializer::write_primitive_array(const std::vector<int64_t> &val) {
	write_primitive(static_cast<uint32_t>(val.size() + 1));
	for (auto const curVal : val) {
		write_primitive(curVal);
	}
}

void serializer::write_primitive(const std::string &val) {
	primitives::write_string(m_stream, val);
}

void serializer::write_primitive(const int32_t &val) {
	primitives::write_int32(m_stream, val);
}

void serializer::write_primitive(const uint32_t &val) {
	primitives::write_varint32(m_stream, val);
}

void serializer::write_primitive(const int64_t &val) {
	primitives::write_varint64(m_stream, val);
}