#include "stdafx.h"
#include "packets/client_packets.h"

using namespace std;
using namespace quasar::packets;
using namespace quasar::tools;

get_directory_response_packet::get_directory_response_packet() :
		quasar_client_packet(PACKET_GET_DIRECTORY_RESPONSE) {
}

get_directory_response_packet::get_directory_response_packet(const string &path) :
		quasar_client_packet(PACKET_GET_DIRECTORY_RESPONSE) {
	initialize(path);
}

vector<unsigned char> get_directory_response_packet::serialize_packet() {
	begin_serialization();
	vector<string> dirs, regularFiles;
	vector<int64_t> fileSizes;

	for(auto const &file : m_files) {
		if(file.m_is_directory) {
			dirs.push_back(file.m_file_name);
		} else {
			regularFiles.push_back(file.m_file_name);
			fileSizes.push_back(file.m_file_size);
		}
	}

	m_serializer.write_primitive_array(regularFiles);
	m_serializer.write_primitive_array(fileSizes);
	m_serializer.write_primitive_array(dirs);

	return m_serializer.get_serializer_data();
}

void get_directory_response_packet::initialize(const string &path) {
	m_files = filesys_mgr::get_files(path);
}