#pragma once

#include <vector>
#include <string>
#include "packet.h"
#include "tools/aes_crypt.h"
#include "packets/client_packets.h"

#include "boost/array.hpp"
#include "boost/asio.hpp"

namespace quasar {
	class quasar_client {
	public:
		quasar_client(boost::asio::io_service &io_srvc);
		~quasar_client();

		void connect(std::string hostname, std::string port);
		void send(std::shared_ptr<packets::quasar_client_packet> packet);

		bool is_connected() const;
		bool get_compress() const;

		void set_compress(const bool value);

		/* events */
		//boost::signals2::signal<void()> msig_on_disconnected;
	private:
		boost::asio::ip::tcp::socket m_sock;
		boost::asio::ip::tcp::resolver m_resolver;
		/* use a statically sized buffer for header size since it's always sizeof(int)==4 */
		boost::array<unsigned char, 4> m_hdr_buf;
		std::vector<unsigned char> m_payload_buf;
		bool m_connected;
		bool m_compress;
		bool m_encrypt;
		aes_crypt m_aes;

		void connect_handler(const boost::system::error_code &ec);
		void read_header();
		void read_payload();
	};
}