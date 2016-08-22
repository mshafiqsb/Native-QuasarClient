#include "stdafx.h"
#include "packets/server_packets.h"

using namespace quasar::packets;

get_authentication_packet::get_authentication_packet() :
		quasar_server_packet(PACKET_GET_AUTHENTICATION) {

}

void get_authentication_packet::deserialize_packet(mem_istream &stream) {

}

void get_authentication_packet::execute(quasar_client &client) {
	auto response = std::make_shared<get_authentication_response_packet>();
	client.send(response);
}