#include "stdafx.h"
#include "packets/server_packets.h"
#include <tools/proc_mgr.h>

using namespace std;
using namespace quasar::packets;
#ifdef _MSC_VER
using namespace quasar;
#endif

do_process_kill_packet::do_process_kill_packet() :
				quasar_server_packet(PACKET_DO_PROCESS_KILL),
				m_pid(-1) {
}

void do_process_kill_packet::deserialize_packet(mem_istream &stream) {
		m_pid = m_deserializer.read_primitive<int32_t>(stream);
}

void do_process_kill_packet::execute(quasar_client &client) {
		tools::proc_mgr::kill_process(m_pid);
		client.send(get_processes_response_packet::create());
}