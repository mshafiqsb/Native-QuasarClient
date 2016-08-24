#include "stdafx.h"
#include "packets/server_packets.h"

using namespace std;
using namespace quasar::packets;

get_directory_packet::get_directory_packet() :
		quasar_server_packet(PACKET_GET_DIRECTORY) {
}

void get_directory_packet::deserialize_packet(mem_istream &stream) {
	m_remote_path = m_deserializer.read_primitive<string>(stream);
}

void get_directory_packet::execute(quasar::quasar_client &client) {
	auto lol = new get_directory_response_packet(m_remote_path);
	client.send(std::shared_ptr<get_directory_response_packet>(new get_directory_response_packet(m_remote_path)));
}