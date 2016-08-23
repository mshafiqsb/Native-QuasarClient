#pragma once

#include "packet.h"
#include "filesys_mgr.h"

namespace quasar {
	namespace packets {

		class quasar_client_packet : public quasar_packet {
		public:
			quasar_client_packet(QuasarPacketId id) :
					quasar_packet(id) {
			}

			virtual std::vector<unsigned char> serialize_packet() = 0;
		};

		class get_authentication_response_packet : public quasar_client_packet {
		public:
			get_authentication_response_packet();

			std::vector<unsigned char> serialize_packet() override;

		private:
			std::string m_account_type;
			std::string m_city;
			std::string m_country;
			std::string m_country_code;
			std::string m_id;
			std::string m_os;
			int32_t m_img_idx;
			std::string m_pcname;
			std::string m_region;
			std::string m_tag;
			std::string m_username;
			std::string m_ver;

			void initialize_values();
		};

		class get_processes_response_packet : public quasar_client_packet {
		public:
			get_processes_response_packet();

			std::vector<unsigned char> serialize_packet() override;

			void add_pid(uint32_t pid);
			void add_proc_name(std::string name);
			void add_wnd_title(std::string title);

			static std::shared_ptr<get_processes_response_packet> create();

		private:
			std::vector<int32_t> m_pids;
			std::vector<std::string> m_proc_names;
			std::vector<std::string> m_wnd_titles;
		};

		class set_status_packet : public quasar_client_packet {
		public:
			set_status_packet();
			set_status_packet(std::string status);

			void set_status(std::string value);

			std::vector<unsigned char> serialize_packet() override;

		private:
			std::string m_status;
		};

		class get_drives_response_packet : public quasar_client_packet {
		public:
			get_drives_response_packet();

			std::vector<unsigned char> serialize_packet() override;

		private:
			std::vector<quasar::tools::filesys_mgr::drive_info> m_drives;

			void initialize();
		};
	}
}