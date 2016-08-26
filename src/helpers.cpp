#include "helpers.h"

using namespace std;
using namespace boost::asio;

namespace quasar {
	namespace helpers {

		void trim_string(string &str, const char trimChar) {
			trim_string_left(str, trimChar);
			trim_string_right(str, trimChar);
		}

		void trim_string_left(string &str, const char trimChar) {
			str.erase(str.begin(), std::find_if(str.begin(), str.end(),
																					[&trimChar](char c) {
																						return trimChar != c;
																					}));
		}

		void trim_string_right(string &str, const char trimChar) {
			str.erase(std::find_if(str.rbegin(), str.rend(),
														 [&trimChar](char c) {
															 return trimChar != c;
														 }).base(), str.end());
		}

		bool string_startswith(const string &str, const string &str2) {
			if (str.size() < str2.size()) {
				return false;
			}
			for (int i = 0; i < str2.size(); i++) {
				if (str[i] != str2[i]) {
					return false;
				}
			}
			return true;
		}

		bool is_number(const string &s) {
			return !s.empty() && find_if(s.begin(),
																	 s.end(), [](char c) { return !isdigit(c); }) == s.end();
		}

		vector<string> tokenize_string(string str, char delimiter) {
			vector<string> internal;
			stringstream ss(str);
			string tok;

			while (getline(ss, tok, delimiter)) {
				internal.push_back(tok);
			}

			return internal;
		}

		map<string, string> shallow_json_parse(string str) {
			if (str[0] != '{' || str.back() != '}') {
				throw 0;
			}
			trim_string_left(str, '{');
			trim_string_right(str, '}');
			trim_string(str, '\"');

			vector<string> tokens = tokenize_string(str, ',');
			if (tokens.size() % 2 != 0) {
				throw 0;
			}

			map<string, string> parsedVals;
			for (auto const tok : tokens) {
				size_t pos;
				if ((pos = tok.find(':')) == string::npos) {
					continue;
				} else {
					string key(tok.substr(0, pos));
					string val(tok.substr(pos + 1, tok.size() - pos - 1));
					trim_string(key, '\"');
					trim_string(val, '\"');
					if (parsedVals.count(key) != 0) {
						continue;
					} else {
						parsedVals[key] = val;
					}
				}
			}

			return parsedVals;
		}

		bool download_webpage(string server, string path, string &data) {
			boost::system::error_code ec;
			io_service svc;
			ip::tcp::resolver resolver(svc);
			ip::tcp::resolver::query query(server, "80");
			ip::tcp::resolver::iterator endpoint_iterator;
			try {
				endpoint_iterator = resolver.resolve(query);
			} catch (...) {
				return false;
			}
			ip::tcp::socket sock(svc);
			boost::asio::connect(sock, endpoint_iterator); // http://localhost:8087 for test

			// send request
			stringstream request;
			request << "GET " + path + " HTTP/1.1\r\n";
			request << "Host: " + server + "\r\n\r\n";
			sock.send(boost::asio::buffer(request.str()));

			// read response
			string response;

			do {
				char buf[1024];
				size_t bytes_transferred = sock.receive(boost::asio::buffer(buf), {}, ec);
				if (!ec) response.append(buf, buf + bytes_transferred);
			} while (!ec);

			if (response.find("\r\n\r\n") == string::npos) {
				return false;
			}

			vector<string> toks;
			boost::split(toks, response, boost::is_any_of("\r\n\r\n"));
			data = toks.back();
			return true;
		}
	}
}