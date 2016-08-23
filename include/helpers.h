#pragma once

#include "boost/asio.hpp"
#include "boost/asio/buffer.hpp"
#include "boost/algorithm/string.hpp"

#include <locale>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

#ifdef WIN32

#include <cctype>
#include <wininet.h>

#endif

namespace quasar {
		namespace helpers {

				template<typename T>
				void prefix_vector_length(std::vector<T> &vector) {
						throw std::runtime_error("Vector must be of char/unsigned char type");
				}

				template<>
				inline void prefix_vector_length<char>(std::vector<char> &vector) {
						int32_t payloadSize = vector.size();
						char *chars = reinterpret_cast<char *>(&payloadSize);
						vector.insert(vector.begin(), chars, chars + sizeof(int32_t));
				}

				template<>
				inline void prefix_vector_length<unsigned char>(std::vector<unsigned char> &vector) {
						int32_t payloadSize = vector.size();
						char *chars = reinterpret_cast<char *>(&payloadSize);
						vector.insert(vector.begin(), chars, chars + sizeof(int32_t));
				}

				bool string_startswith(const std::string &str, const std::string &str2);

				bool is_number(const std::string &s);

				std::vector<std::string> tokenize_string(std::string str, char delimiter);

				std::map<std::string, std::string> shallow_json_parse(std::string str);

				/* Max page size 1024 bytes */
				bool download_webpage(std::string server, std::string path, std::string &data);

		}
}