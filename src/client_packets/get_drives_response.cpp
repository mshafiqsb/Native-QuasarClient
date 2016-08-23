#include "stdafx.h"
#include "packets/client_packets.h"

using namespace std;
using namespace quasar::packets;
using namespace quasar::tools;

get_drives_response_packet::get_drives_response_packet() :
		quasar_client_packet(PACKET_GET_DRIVES_RESPONSE) {
	initialize();
}

vector<unsigned char> get_drives_response_packet::serialize_packet() {
	begin_serialization();
	vector<string> displayNames, rootDirs;

	for(auto const &driveInf : m_drives) {
		displayNames.push_back(driveInf.m_display_name);
		rootDirs.push_back(driveInf.m_root_dir);
	}
	m_serializer.write_primitive_array(displayNames);
	m_serializer.write_primitive_array(rootDirs);

	return m_serializer.get_serializer_data();
}

void get_drives_response_packet::initialize() {
	m_drives = filesys_mgr::get_drives();
}