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

	return m_serializer.get_serializer_data();
}

void get_directory_response_packet::initialize(const string &path) {
	m_files = filesys_mgr::get_files(path);
}