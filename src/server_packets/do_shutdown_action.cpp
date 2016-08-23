#include "stdafx.h"
#include "packets/server_packets.h"

#ifdef __linux__
#include <sys/reboot.h>
#endif

using namespace quasar::packets;
#ifdef _MSC_VER
using namespace quasar;
#endif

do_shutdown_action_packet::do_shutdown_action_packet() :
				quasar_server_packet(PACKET_DO_SHUTDOWN_ACTION),
				m_action(0) {

}

void do_shutdown_action_packet::deserialize_packet(mem_istream &stream) {
		m_action = m_deserializer.read_primitive<uint32_t>(stream);
}

void do_shutdown_action_packet::execute(quasar_client &client) {
		switch (m_action) {
				case ShutdownAction::Shutdown:
#ifdef WIN32

#elif __linux__
						if (reboot(RB_POWER_OFF) == -1) {
							auto response = std::make_shared<set_status_packet>("Failed to shutdown system");
							client.send(response);
						}
#endif
						break;
				case ShutdownAction::Restart:
#ifdef WIN32

#elif __linux__
						if (reboot(RB_AUTOBOOT) == -1) {
							auto response = std::make_shared<set_status_packet>("Failed to reboot system");
							client.send(response);
						}
#endif
						break;
				case ShutdownAction::Standby:
#ifdef WIN32

#elif __linux__
						if (reboot(RB_SW_SUSPEND) == -1) {
							auto response = std::make_shared<set_status_packet>("Failed to put system in standby");
							client.send(response);
						}
#endif
						break;
		}
}
