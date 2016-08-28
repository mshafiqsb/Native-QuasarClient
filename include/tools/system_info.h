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

			std::string get_account_type() const;
			std::string get_operating_system() const;
			std::string get_city() const;
			std::string get_country() const;
			std::string get_country_code() const;
			std::string get_pcname() const;
			std::string get_region() const;
			std::string get_username() const;

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
			static bool is_64bit();
		};

	}
}