#include "stdafx.h"
#include "packets/client_packets.h"
#include <tools/proc_mgr.h>

using namespace std;
using namespace quasar::packets;

get_processes_response_packet::get_processes_response_packet() :
		quasar_client_packet(PACKET_GET_PROCESSES_RESPONSE) {
}

vector<unsigned char> get_processes_response_packet::serialize_packet() {
	begin_serialization();
	m_serializer.write_primitive_array(m_pids);
	m_serializer.write_primitive_array(m_proc_names);
	m_serializer.write_primitive_array(m_wnd_titles);

	return m_serializer.get_serializer_data();
}

void get_processes_response_packet::add_pid(uint32_t pid) {
	m_pids.push_back(pid);
}

void get_processes_response_packet::add_proc_name(string name) {
	m_proc_names.push_back(name);
}

void get_processes_response_packet::add_wnd_title(string title) {
	m_wnd_titles.push_back(title);
}

std::shared_ptr<get_processes_response_packet> get_processes_response_packet::create() {
	auto packet = std::make_shared<get_processes_response_packet>();
	vector<tools::process_info> procInfos = tools::proc_mgr::get_proc_infos();
	for (auto const pinf : procInfos) {
		packet->add_pid(pinf.pid);
		packet->add_proc_name(pinf.proc_name);
		packet->add_wnd_title(pinf.main_wnd_title);
	}
	return packet;
}
