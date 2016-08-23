#include "stdafx.h"
#include "packets/server_packets.h"

using namespace quasar::packets;

get_drives_packet::get_drives_packet() :
		quasar_server_packet(PACKET_GET_DRIVES) {
}

void get_drives_packet::deserialize_packet(mem_istream &stream) {

}

void get_drives_packet::execute(quasar::quasar_client &client) {

}