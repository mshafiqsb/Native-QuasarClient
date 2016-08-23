#pragma once

#include <vector>
#include "primitives.h"
#include <limits>

// ReSharper disable CppExplicitSpecializationInNonNamespaceScope
namespace quasar {
		namespace tools {

				class deserializer {
				public:
						deserializer() {

						}

						template<typename T>
						static T read_primitive(mem_istream &stream) {
								throw 0;
						};

				};

				template<>
				inline int32_t deserializer::read_primitive<int32_t>(mem_istream &stream) {
						return primitives::read_int32(stream);
				}

				template<>
				inline uint32_t deserializer::read_primitive<uint32_t>(mem_istream &stream) {
						return primitives::read_varint32(stream);
				}

				template<>
				inline uint16_t deserializer::read_primitive<uint16_t>(mem_istream &stream) {
						uint32_t val = primitives::read_varint32(stream);
						if (val > std::numeric_limits<uint16_t>::max()) {
								throw 0;
						}
						return static_cast<uint16_t>(primitives::read_varint32(stream));
				}

				template<>
				inline std::string deserializer::read_primitive<std::string>(mem_istream &stream) {
						return primitives::read_string(stream);
				}

		}
}