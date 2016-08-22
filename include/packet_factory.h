#pragma once

#include "packet.h"
#include <vector>
#include <packets/server_packets.h>

namespace quasar {
	namespace packets {

		class packet_factory {
		public:
			static std::shared_ptr<quasar_server_packet> create_packet(std::vector<unsigned char> &payload);
		};
	}
}
