#include "stdafx.h"
#include "packets/server_packets.h"
#include <helpers.h>

#ifdef WIN32

#include <psapi.h>
#include <TlHelp32.h>

#endif

#include <tools/proc_mgr.h>

using namespace quasar::packets;

get_processes_packet::get_processes_packet() :
		quasar_server_packet(PACKET_GET_PROCESSES) {
}

void get_processes_packet::deserialize_packet(mem_istream &stream) {

}

void get_processes_packet::execute(quasar::quasar_client &client) {
	client.send(get_processes_response_packet::create());
}