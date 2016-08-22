#pragma once
#ifdef __linux__
#include <sys/utsname.h>
#include <pwd.h>
#endif

#include <string>
#include <map>

namespace quasar {
	namespace tools {

		class system_info {
		public:
			system_info();

			std::string get_account_type();
			std::string get_operating_system();
			std::string get_city();
			std::string get_country();
			std::string get_country_code();
			std::string get_pcname();
			std::string get_region();
			std::string get_username();

		private:
			std::string m_account_type;
			std::string m_os;
			std::string m_city;
			std::string m_country;
			std::string m_country_code;
			std::string m_pcname;
			std::string m_region;
			std::string m_tag;
			std::string m_username;

			void initialize_data();
			void initialize_extended_data();
		};

	}
}