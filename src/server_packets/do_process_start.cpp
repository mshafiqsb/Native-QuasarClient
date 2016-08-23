#include "stdafx.h"
#include "packets/server_packets.h"
#include <helpers.h>
#include <tools/proc_mgr.h>

using namespace std;
using namespace quasar::packets;
#ifdef _MSC_VER
using namespace quasar;
#endif

do_process_start_packet::do_process_start_packet() :
				quasar_server_packet(PACKET_DO_PROCESS_START),
				m_file() {
}

void do_process_start_packet::deserialize_packet(mem_istream &stream) {
		m_file = m_deserializer.read_primitive<string>(stream);
}

void do_process_start_packet::execute(quasar_client &client) {
		if (!tools::proc_mgr::start_process(m_file)) {
				client.send(std::make_shared<set_status_packet>("Process could not be started!"));
		} else {
				client.send(get_processes_response_packet::create());
		}
}
