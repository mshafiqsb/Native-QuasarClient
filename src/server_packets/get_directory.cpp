#include "stdafx.h"
#include "packets/server_packets.h"

using namespace quasar::packets;

get_directory_packet::get_directory_packet() :
		quasar_server_packet(PACKET_GET_DIRECTORY) {
}

void get_directory_packet::deserialize_packet(mem_istream &stream) {

}

void get_directory_packet::execute(quasar::quasar_client &client) {
	client.send(std::make_shared<get_drives_response_packet>());
}